#include"MenuNotas.cpp"

vector<Usuario> cargarUsuarios();
Usuario iniciarSesion(const vector<Usuario> &usuarios);
void mostrarMenuNotas(Usuario &usuario);

//Procedimiento en donde se imprime el menu de inicio
void menuUsuarios(){
    vector<Usuario> usuarios = cargarUsuarios();
    int opcion;

    do {

        system("cls");

        cout << "========= MENU PRINCIPAL =========\n";
        cout << "1. Crear usuario\n";
        cout << "2. Iniciar sesion\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cout << endl;

        switch (opcion) {
            case 1: {//Crea un usuario nuevo
                Usuario nuevoUsuario = CrearUsuario(); 
                usuarios.push_back(nuevoUsuario);
                guardarUsuario(nuevoUsuario);//El nuevo usuario creado se guarda en el archivo usuarios.txt
                cout << "Usuario creado exitosamente.\n\n";
                break;
            }
            case 2: {//Si ya existe el usuario, puede iniciar sesion con el mismo
                Usuario usuarioLogeado = iniciarSesion(usuarios);
                if (usuarioLogeado.ID != -1) {
                    usuarioLogeado.notas = CargarNotas(usuarioLogeado.ID);
                    mostrarMenuNotas(usuarioLogeado);//Si es exitoso, entrara al menu de notas
                }
                break;
            }
            case 3: //Sale del programa...
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo.\n";
        }
        system("pause");

    } while (opcion != 3);
    system("cls");
}

vector<Usuario> cargarUsuarios(){//Vector desde donde se cargan los usuarios almacenados en el archivo
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
                usuario.Contrasenia = linea.substr(13);

                usuarios.push_back(usuario);
            }
        }
        archivo.close();
    }
    return usuarios;
}

Usuario iniciarSesion(const vector<Usuario> &usuarios) {//Funion para iniciar sesion
    int id;
    string contrasenia;

    bool confirmarID = true;

    while (confirmarID) {
        cout << "Ingrese su ID: ";
        cin >> id;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Solo se permiten caracteres numericos para el ID.\n";
            continue;;
        }
        confirmarID = false;
    }

    cout << "Ingrese su contrasenia: ";
    cin >> contrasenia;

    for (const auto &usuario : usuarios) {
        if (usuario.ID == id && usuario.Contrasenia == contrasenia) {
            cout << "Inicio de sesion exitoso.\n\n";
            return usuario;
        }
    }

    cout << "Credenciales incorrectas. Por favor, intente de nuevo.\n\n";
    return {-1, "", "", {}};
}