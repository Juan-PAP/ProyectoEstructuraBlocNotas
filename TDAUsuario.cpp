#include <limits>
#include "TDANota.cpp"

struct Usuario { //Estructura para los usuarios
    int ID;
    string Nombre;
    string Contrasenia;
    vector<Nota> notas;
};

struct NotaAux{ //Estructura para manejar las notas pertenecientes a un usuario
    int IDUsuario;
    Nota nota;

};

void guardarUsuario(const Usuario &usuario) { //Procedimiento para guardar un nuevo usuario en el archivo
    ofstream archivo("usuarios.txt", ios::app);
    if (archivo.is_open()) {
        archivo << "ID: " << usuario.ID << endl;
        archivo << "Nombre: " << usuario.Nombre << endl;
        archivo << "Contrasenia: " << usuario.Contrasenia << endl;
        archivo << "-------------------------------" << endl;
        archivo.close();
        cout << "Datos guardados en el archivo 'usuarios.txt'.\n";
    } 
    else {
        cout << "Error al abrir el archivo.\n";
    }
}

bool verificarIDUnico(int id) { //Funcio para confirmar si el ID es unico dentro del archivo usuarios
    ifstream archivo("usuarios.txt");
    string linea;
    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            if (linea.find("ID: ") != string::npos) {
                int idExistente = stoi(linea.substr(4));
                if (idExistente == id) {
                    archivo.close();
                    return false;
                }
            }
        }
        archivo.close();
    }
    return true;
}

Usuario CrearUsuario() {//Funcion para crear un nuevo usuario
    Usuario nuevoUsuario;
    bool confirmarID = true;

    while (confirmarID){ //Confirmar si el ID cumple con las restricciones
        cout << "Ingrese su ID, debe tener entre 7 a 10 numeros: ";
        cin >> nuevoUsuario.ID;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Solo se permiten caracteres numericos para el ID.\n";
            continue;
        }

        string cantidadCaracteres = to_string(nuevoUsuario.ID);

        if (cantidadCaracteres.length() >= 7 && cantidadCaracteres.length() <= 10){ 
            if (verificarIDUnico(nuevoUsuario.ID)) {
                confirmarID = false;
            } 
            else {
                cout << "El ID ya esta en uso. Por favor, intente con otro.\n";
            }
        } 
        else {
            cout << "El ID solo debe tener de entre 7 a 10 numeros.\n";
            cout << "Por favor, intentalo de nuevo.\n";
            cin.ignore();
        }
    }

    cin.ignore();

    do {//Confirmar si el nombre de usuario cumple con las condiciones
        cout << "Ingrese su nombre de usuario, debe tener entre 6 a 18 caracteres: ";
        getline(cin, nuevoUsuario.Nombre);
    } while (nuevoUsuario.Nombre.length() < 6 || nuevoUsuario.Nombre.length() > 18);

    do {//Confirmar si la contraseña cumple con las condiciones
        cout << "Ingrese su contrasenia, debe tener entre 4 a 12 caracteres: ";
        getline(cin, nuevoUsuario.Contrasenia);
    } while (nuevoUsuario.Contrasenia.length() < 4 || nuevoUsuario.Contrasenia.length() > 12);

    return nuevoUsuario;
}

void imprimirUsuario(const Usuario &usuario) {//Procedimiento para imprimer la informacion del usuario
    cout << "ID: " << usuario.ID << endl;
    cout << "Nombre: " << usuario.Nombre << endl;
}

void GuardarNotas(const vector<Nota> &notas, Usuario usuario) {//Procedimiento para guardar las notas de un usuario especifico en el archivo notas
    ofstream archivo("notas_aux.txt", ios::out);
    if (archivo.is_open()) {
        for (const auto &nota : notas) {
            archivo
                    << usuario.ID << "|"
                    << nota.id << "|"
                    << nota.titulo << "|"
                    << nota.contenido << "|"
                    << nota.fechaCreacion.d << "/"
                    << nota.fechaCreacion.m << "/"
                    << nota.fechaCreacion.a << "|"
                    << nota.fechaModificacion.d << "/"
                    << nota.fechaModificacion.m << "/"
                    << nota.fechaModificacion.a << "\n";
        }
        archivo.close();
        cout << "Notas guardadas exitosamente." << endl;
    } else {
        cout << "Error al guardar las notas en el archivo." << endl;
    }
}

vector<Nota> CargarNotas(int idUsuario) { //Carga todas las notas en un vector que pertenescan a un usuario especifico
    vector<Nota> notas;
    ifstream archivo("notas.txt", ios::in);

    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            Nota nota;
            size_t pos = 0;

            pos = linea.find("|");
            string idUsuarioArchivo = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            string stringUsuario = to_string(idUsuario);
            if (idUsuarioArchivo != stringUsuario) continue; //Punto para verificar si la nota es del usuario

            pos = linea.find("|");
            nota.id = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            pos = linea.find("|");
            nota.titulo = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            pos = linea.find("|");
            nota.contenido = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            pos = linea.find("|");
            sscanf(linea.substr(0, pos).c_str(), "%d/%d/%d", &nota.fechaCreacion.d, &nota.fechaCreacion.m, &nota.fechaCreacion.a);
            linea.erase(0, pos + 1);

            sscanf(linea.c_str(), "%d/%d/%d", &nota.fechaModificacion.d, &nota.fechaModificacion.m, &nota.fechaModificacion.a);

            notas.push_back(nota);
        }
        archivo.close();
        cout << "Notas cargadas exitosamente." << endl;
    } else {
        cout << "Error al cargar las notas desde el archivo." << endl;
    }

    return notas;
}

vector<NotaAux> CargarNotasNoUsuario(int idUsuario) { //Carga todas las notas en un vector auxiliar, que NO pertenescan al usuario en cuestion
    vector<NotaAux> notas;
    ifstream archivo("notas.txt", ios::in);

    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            NotaAux nota;
            size_t pos = 0;

            pos = linea.find("|");
            string idUsuarioArchivo = linea.substr(0, pos);
            nota.IDUsuario = stoi(idUsuarioArchivo);
            linea.erase(0, pos + 1);

            string stringUsuario = to_string(idUsuario);
            if (idUsuarioArchivo == stringUsuario) continue; //Punto para verificar que la nota NO sea del usuario

            pos = linea.find("|");
            nota.nota.id = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            pos = linea.find("|");
            nota.nota.titulo = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            pos = linea.find("|");
            nota.nota.contenido = linea.substr(0, pos);
            linea.erase(0, pos + 1);

            pos = linea.find("|");
            sscanf(linea.substr(0, pos).c_str(), "%d/%d/%d", &nota.nota.fechaCreacion.d, &nota.nota.fechaCreacion.m, &nota.nota.fechaCreacion.a);
            linea.erase(0, pos + 1);

            sscanf(linea.c_str(), "%d/%d/%d", &nota.nota.fechaModificacion.d, &nota.nota.fechaModificacion.m, &nota.nota.fechaModificacion.a);

            notas.push_back(nota);
        }
        archivo.close();
        cout << "Notas cargadas exitosamente." << endl;
    } else {
        cout << "Error al cargar las notas desde el archivo." << endl;
    }

    return notas;
}

void ActualizarArchivo(Usuario usuario){//Procedimiento para unificar las notas, se llaman tantos las notas pertenecientes como no pertenecientes del usuario
    ofstream archivo("notas_aux.txt", ios::app);//Y las pertenecientes del usuario, son cargadas en en archivo auxilar (en donde se guardaban las no pertenecientes al usuario)
    vector<NotaAux> complemento = CargarNotasNoUsuario(usuario.ID);
    if (archivo.is_open()) {
        for (const auto &nota : complemento) {
            archivo
                    << nota.IDUsuario << "|"
                    << nota.nota.id << "|"
                    << nota.nota.titulo << "|"
                    << nota.nota.contenido << "|"
                    << nota.nota.fechaCreacion.d << "/"
                    << nota.nota.fechaCreacion.m << "/"
                    << nota.nota.fechaCreacion.a << "|"
                    << nota.nota.fechaModificacion.d << "/"
                    << nota.nota.fechaModificacion.m << "/"
                    << nota.nota.fechaModificacion.a << "\n";
        }
        archivo.close();
        remove("notas.txt"); //Se elimina el archivo viejo
        rename("notas_aux.txt", "notas.txt"); //Se vuelve a renombrar on la nueva informacion actualizada
    }
}