#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<ctime>
using namespace std;

struct fecha{
    int d, m, a;
};

struct Nota{
    string id;
    string titulo;
    string contenido;
    fecha fechaCreacion;
    fecha fechaModificacion;
};

fecha ObtenerFechaActual(){
    time_t tiempoActual=time(NULL);
    tm* fechaLocal=localtime(&tiempoActual);
    fecha fechaActual;
    fechaActual.d=fechaLocal->tm_mday;
    fechaActual.m=fechaLocal->tm_mon + 1;
    fechaActual.a=fechaLocal->tm_year + 1900;
    return fechaActual;
}

Nota CrearNota(int idUsuario, int numeroNota){
    Nota nuevaNota;
    string stringUsuario = to_string(idUsuario);
    string idNota = to_string(numeroNota + 1);
    nuevaNota.id = stringUsuario + "-" + idNota;

    cin.ignore();
    cout << "Ingrese el titulo de la nota: ";
    getline(cin, nuevaNota.titulo);
    cout << endl;

    cout << "Ingrese el contenido de la nota: " << endl;
    getline(cin, nuevaNota.contenido);
    cout << endl;

    nuevaNota.fechaCreacion = ObtenerFechaActual();
    nuevaNota.fechaModificacion = {0, 0, 0};
    return nuevaNota;
}

void MostrarNota(const Nota &nota) {
    cout << "ID: " << nota.id << endl;
    cout << "TITULO: " << nota.titulo << endl;
    cout << "CONTENIDO: " << nota.contenido << endl;
    cout << "FECHA CREACION: " << nota.fechaCreacion.d << "/"
         << nota.fechaCreacion.m << "/" << nota.fechaCreacion.a << endl;

    if (nota.fechaModificacion.a != 0) {
        cout << "FECHA MODIFICACION: " << nota.fechaModificacion.d << "/"
             << nota.fechaModificacion.m << "/" << nota.fechaModificacion.a << endl;
    }
}

void EditarNota(Nota &nota) {
    bool cambios = false;
    char cTitulo, cContenido;

    cout << "Desea cambiar el titulo de la nota? (S/N) ";
    cin >> cTitulo;
    cout << endl;
    cin.ignore();
    if (tolower(cTitulo) == 's') {
        cout << "Ingrese el nuevo titulo de la nota: ";
        getline(cin, nota.titulo);
        cambios = true;
    }

    cout << "Desea cambiar el contenido de la nota? (S/N) ";
    cin >> cContenido;
    cout << endl;
    cin.ignore();
    if (tolower(cContenido) == 's') {
        cout << "Ingrese el nuevo contenido de la nota: ";
        getline(cin, nota.contenido);
        cambios = true;
    }

    if (cambios) {
        cout << "Nota modificada exitosamente." << endl;
        nota.fechaModificacion = ObtenerFechaActual();
    }
}

void EliminarNota(vector<Nota> &notas, const string &id) {
    for (auto it = notas.begin(); it != notas.end(); ++it) {
        if (it->id == id) {
            notas.erase(it);
            cout << "Nota eliminada exitosamente." << endl;
            return;
        }
    }
    cout << "No se encontró la nota con ID: " << id << endl;
}
