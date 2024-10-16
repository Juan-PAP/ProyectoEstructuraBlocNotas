#include "TDAUsuario.cpp"

void mostrarMenuNotas(Usuario &usuario) { //Procedimiento en donde el usuario puede interactuar con la aplicacion de notas
    int opcion;

    do {
        system("cls");

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
            case 1: {//Crea una nueva nota asociada al usuario
                Nota nuevaNota = CrearNota(usuario.ID, usuario.notas.size());
                usuario.notas.push_back(nuevaNota);
                GuardarNotas(usuario.notas, usuario);
                cout << "Nota creada exitosamente.\n\n";
                break;
            }
            case 2: {//Imprime las notas creadas por el usuario
                if (usuario.notas.empty()){
                    cout << "No hay notas para mostrar.\n\n";
                } 
                else{
                    for (const auto &nota : usuario.notas) {
                        MostrarNota(nota);
                        cout << "-------------------------\n";
                    }
                }
                break;
            }
            case 3: {//Permite editar una nota del usuario
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
            case 4:{//Permite eleminar una nota del usuario
                string idNota;
                cout << "Ingrese el ID de la nota a eliminar: ";
                cin >> idNota;
                EliminarNota(usuario.notas, idNota);
                GuardarNotas(usuario.notas, usuario);
                break;
            }
            case 5://Actualiza el archivo para guardar los cambios y cierra el menu notas...
                ActualizarArchivo(usuario);
                cout << "Cerrando sesion...\n";
                break;
            default:
                cout << "Opcian no valida. Intente de nuevo.\n";
        }
        system("pause");

    } while (opcion != 5);
}
