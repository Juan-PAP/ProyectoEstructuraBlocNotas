#include <limits>
#include "TDANota.cpp"

struct Usuario {
    int ID;
    string Nombre;
    string Contraseña;
    vector<Nota> notas;
};

struct NotaAux{
    int IDUsuario;
    Nota nota;

};

void guardarUsuario(const Usuario &usuario) {
    ofstream archivo("usuarios.txt", ios::app);
    if (archivo.is_open()) {
        archivo << "ID: " << usuario.ID << endl;
        archivo << "Nombre: " << usuario.Nombre << endl;
        archivo << "Contraseña: " << usuario.Contraseña << endl;
        archivo << "Cantidad de Notas: " << usuario.notas.size() << endl;
        archivo << "-------------------------------" << endl;
        archivo.close();
        cout << "Datos guardados en el archivo 'usuarios.txt'.\n";
    } 
    else {
        cout << "Error al abrir el archivo.\n";
    }
}

bool verificarIDUnico(int id) {
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

Usuario CrearUsuario() {
    Usuario nuevoUsuario;
    bool confirmarID = true;

    while (confirmarID) {
        cout << "Ingrese su ID, debe tener entre 7 a 10 numeros: ";
        cin >> nuevoUsuario.ID;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Solo se permiten caracteres numericos para el ID.\n";
            continue;
        }

        string cantidadCaracteres = to_string(nuevoUsuario.ID);

        if (cantidadCaracteres.length() >= 7 && cantidadCaracteres.length() <= 10) {
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

    do {
        cout << "Ingrese su nombre de usuario, debe tener entre 6 a 18 caracteres: ";
        getline(cin, nuevoUsuario.Nombre);
    } while (nuevoUsuario.Nombre.length() < 6 || nuevoUsuario.Nombre.length() > 18);

    do {
        cout << "Ingrese su contraseña, debe tener entre 4 a 12 caracteres: ";
        getline(cin, nuevoUsuario.Contraseña);
    } while (nuevoUsuario.Contraseña.length() < 4 || nuevoUsuario.Contraseña.length() > 12);

    return nuevoUsuario;
}

void imprimirUsuario(const Usuario &usuario) {
    cout << "ID: " << usuario.ID << endl;
    cout << "Nombre: " << usuario.Nombre << endl;
    cout << "Cantidad de Notas: " << usuario.notas.size() << endl;
}

void GuardarNotas(const vector<Nota> &notas, Usuario usuario) {
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

vector<Nota> CargarNotas(int idUsuario) {
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
            if (idUsuarioArchivo != stringUsuario) continue;

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

vector<NotaAux> CargarNotasNoUsuario(int idUsuario) {
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
            if (idUsuarioArchivo == stringUsuario) continue;

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

void ActualizarArchivo(Usuario usuario){
    ofstream archivo("notas_aux.txt", ios::app);
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
        remove("notas.txt");
        rename("notas_aux.txt", "notas.txt");
    }


}