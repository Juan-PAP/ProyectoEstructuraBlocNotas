#include "TDAUsuario.cpp"

vector<Usuario> cargarUsuarios();
Usuario iniciarSesion(const vector<Usuario> &usuarios);
void mostrarMenuNotas(Usuario &usuario);

int main() {
    vector<Usuario> usuarios = cargarUsuarios();
    int opcion;

    do {
        cout << "========= MENU PRINCIPAL =========\n";
        cout << "1. Crear usuario\n";
        cout << "2. Iniciar sesion\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cout << endl;

        switch (opcion) {
            case 1: {
                Usuario nuevoUsuario = CrearUsuario();
                usuarios.push_back(nuevoUsuario);
                guardarUsuario(nuevoUsuario);
                cout << "Usuario creado exitosamente.\n\n";
                break;
            }
            case 2: {
                Usuario usuarioLogeado = iniciarSesion(usuarios);
                if (usuarioLogeado.ID != -1) {
                    usuarioLogeado.notas = CargarNotas(usuarioLogeado.ID);
                    mostrarMenuNotas(usuarioLogeado);
                }
                break;
            }
            case 3:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo.\n";
        }

    } while (opcion != 3);

    return 0;
}

vector<Usuario> cargarUsuarios() {
    vector<Usuario> usuarios;
    ifstream archivo("usuarios.txt");
    if (archivo.is_open()) {
        Usuario usuario;
        string linea;

        while (getline(archivo, linea)) {
            if (linea.find("ID: ") != string::npos) {
                usuario.ID = stoi(linea.substr(4));
                getline(archivo, linea);
                usuario.Nombre = linea.substr(8);
                getline(archivo, linea);
                usuario.Contraseña = linea.substr(13);

                usuarios.push_back(usuario);
            }
        }
        archivo.close();
    }
    return usuarios;
}

Usuario iniciarSesion(const vector<Usuario> &usuarios) {
    int id;
    string contrasena;

    cout << "Ingrese su ID: ";
    cin >> id;
    cout << "Ingrese su contraseña: ";
    cin >> contrasena;

    for (const auto &usuario : usuarios) {
        if (usuario.ID == id && usuario.Contraseña == contrasena) {
            cout << "Inicio de sesion exitoso.\n\n";
            return usuario;
        }
    }

    cout << "Credenciales incorrectas. Por favor, intente de nuevo.\n\n";
    return {-1, "", ""};
}

void mostrarMenuNotas(Usuario &usuario) {
    int opcion;

    do {
        cout << "========= MENU DE NOTAS =========\n";
        cout << "1. Crear nota\n";
        cout << "2. Mostrar notas\n";
        cout << "3. Editar nota\n";
        cout << "4. Eliminar nota\n";
        cout << "5. Cerrar sesion\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cout << endl;

        switch (opcion) {
            case 1: {
                Nota nuevaNota = CrearNota(usuario.ID, usuario.notas.size());
                usuario.notas.push_back(nuevaNota);
                GuardarNotas(usuario.notas, usuario);
                cout << "Nota creada exitosamente.\n\n";
                break;
            }
            case 2: {
                if (usuario.notas.empty()) {
                    cout << "No hay notas para mostrar.\n\n";
                } else {
                    for (const auto &nota : usuario.notas) {
                        MostrarNota(nota);
                        cout << "-------------------------\n";
                    }
                }
                break;
            }
            case 3: {
                string idNota;
                cout << "Ingrese el ID de la nota a editar: ";
                cin >> idNota;
                bool encontrada = false;

                for (auto &nota : usuario.notas) {
                    if (nota.id == idNota) {
                        EditarNota(nota);
                        encontrada = true;
                        GuardarNotas(usuario.notas, usuario);
                        cout << "Nota editada exitosamente.\n\n";
                        break;
                    }
                }

                if(!encontrada) {
                    cout << "No se encontro la nota con ID: " << idNota << endl;
                }
                break;
            }
            case 4:{
                string idNota;
                cout << "Ingrese el ID de la nota a eliminar: ";
                cin >> idNota;
                EliminarNota(usuario.notas, idNota);
                GuardarNotas(usuario.notas, usuario);
                break;
            }
            case 5:
                ActualizarArchivo(usuario);
                cout << "Cerrando sesión...\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
        }

    } while (opcion != 5);
}
