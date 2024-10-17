#include"MenuNotas.cpp"

Usuario iniciarSesion(ListaSimple *ListaUsuarios);
void mostrarMenuNotas(Usuario &usuario);

ListaSimple *ListaUsuarios = new (ListaSimple);

void cargarUsuarios(){ // Lista desde donde se cargan los usuarios almacenados en el archivo
    ifstream archivo("usuarios.txt");
   
    if (archivo.is_open()) {
        Usuario usuario;
        string linea;
        ListaUsuarios ->cabeza = nullptr;

        while (getline(archivo, linea)) {

            nodoUsuario *Usuarios = new nodoUsuario;

            if (linea.find("ID: ") != string::npos) {
                
                Usuarios->info.ID = stoi(linea.substr(4));
                getline(archivo, linea);
                Usuarios->info.Nombre = linea.substr(8);
                getline(archivo, linea);
                Usuarios->info.Contrasenia = linea.substr(13);

                IngresarNodo(Usuarios,ListaUsuarios);
            }
        }
        archivo.close();
    } else {
        cout << "Error al abrir el archivo." << endl;
    }
}

//Procedimiento en donde se imprime el menu de inicio
void menuUsuarios(){

    cout<< "Cargando usuarios"<< endl;
    cargarUsuarios();

    cout << "Usuarios cargados, mostrando menu..." << endl;

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
            case 1: {//Crea un usuario nuevo

                nodoUsuario *nuevoUsuario = crearNodo(); 
                IngresarNodo(nuevoUsuario, ListaUsuarios);
                guardarUsuario(nuevoUsuario);//El nuevo usuario creado se guarda en el archivo usuarios.txt
                cout << "Usuario creado exitosamente.\n\n";
                break;
            }
            case 2: {//Si ya existe el usuario, puede iniciar sesion con el mismo
                Usuario usuarioLogeado = iniciarSesion(ListaUsuarios);
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
        system("cls");

    } while (opcion != 3);
    system("cls");
}


Usuario iniciarSesion(ListaSimple *ListaUsuarios) {//Funion para iniciar sesion
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

    nodoUsuario *temp = ListaUsuarios->cabeza;
    bool usuarioEncontrado = false; 
    Usuario usuarioLog {-1, " "," ",{}};

    while (temp != NULL) {
        if (temp ->info.ID == id and temp->info.Contrasenia == contrasenia){
            cout<<"Iniciando seccion\n";
            cout<<"Bienvenido "<<temp->info.Nombre<<endl;
           usuarioEncontrado = true;
            usuarioLog = temp ->info;
        }
        temp = temp ->siguiente;
    }
    if (usuarioEncontrado) {
    return usuarioLog;
    } 
    else {
    return Usuario{-1, "", "", {}};
    }


}