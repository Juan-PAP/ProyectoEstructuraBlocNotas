#include <iostream>
#include <string>
#include <limits>
#include <fstream>

using namespace std;
struct Nota{

};

struct Usuario{
    int ID;
    string Nombre;
    string Contraseña;
    Nota *notas;
    int CanNotas;
};

struct nodo {
    Usuario info;
    nodo *sig;  
};

void guardarUsuario(Usuario usuario) {
    ofstream archivo("usuarios.txt", ios::app);
    if(archivo.is_open()) {
        archivo << "ID: " << usuario.ID << endl;
        archivo << "Nombre: " << usuario.Nombre << endl;
        archivo << "Contraseña: " << usuario.Contraseña << endl;
        archivo << "Notas: " << usuario.CanNotas << endl;
        archivo << "-------------------------------" << endl;
        archivo.close();
        cout << "Datos guardados en el archivo 'usuarios.txt'.\n";
    } else {
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

Usuario CrearUsuario(){

    Usuario nuevoUsuario;
    bool confirmarID = true;

    while(confirmarID){
        cout<<"Ingrese su ID, debe tener entre 7 a 10 numeros: ";
        cin>>nuevoUsuario.ID;

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Solo se permiten caracteres numericos para el ID.\n";
            continue;
        }

        string cantidadCaracteres = to_string(nuevoUsuario.ID);

        if (cantidadCaracteres.length()>= 7 and cantidadCaracteres.length() <= 10){
            if (verificarIDUnico(nuevoUsuario.ID)) {
                confirmarID = false;
            } else {
                cout << "El ID ya esta en uso. Por favor, intente con otro.\n";
            }
        }
        else{
            cout<<"El ID solo debe tener de entre 7 a 10 numeros.\n";
            cout<<"Por favor, intentalo de nuevo.\n";
            cin.ignore();
        }
    }

    cin.ignore();

    bool confirmarNombre = true;

    while(confirmarNombre){
        cout<<"Ingrese su nombre de usuario, debe tener entre 6 a 18 caracteres: ";
        getline(cin,nuevoUsuario.Nombre);

        if (nuevoUsuario.Nombre.length()>= 6 and nuevoUsuario.Nombre.length()<= 18){
            confirmarNombre = false;
        }
        else{
            cout<<"El nombre debe tener de 6 a 18 caracteres\n";
            cout<<"Por favor, intentalo de nuevo\n";
        }
    }

    bool confirmarContraseña = true;

    while(confirmarContraseña){
        cout<<"Ingrese su contraseña, debe tener entre 4 a 12 caracteres: ";
        getline(cin,nuevoUsuario.Contraseña);

        if (nuevoUsuario.Contraseña.length() >= 4 and nuevoUsuario.Contraseña.length()<= 12){           
            confirmarContraseña = false;
        }
        else{
            cout<<"La contraseña solo debe tener de 4 a 12 caracteres\n";
            cout<<"Por favor, intentalo de nuevo\n";
        }
    }

    nuevoUsuario.notas = NULL;

    nuevoUsuario.CanNotas = 0;

    return nuevoUsuario;

}

nodo *crearNodo(){
    nodo *nuevo;
    nuevo = new(nodo);
    nuevo->info = CrearUsuario();
    nuevo ->sig = NULL;
    return nuevo;
}

bool verificarNotas(Usuario *usuario){
    return usuario -> notas != NULL;
};

void imprimirUsuario(nodo *imp){

    cout<<"Los datos del usuario serian:\n";
    cout<<"ID: "<< imp->info.ID<<endl;
    cout<<"Nombre: "<< imp->info.Nombre<<endl;

    if(verificarNotas(&imp ->info)){
        cout<<"El usuario tiene "<<imp->info.CanNotas<<" notas"<<endl;
    }
    else{
        cout<<"El usuario aun no tiene notas creadas."<<endl;
    }
};

bool iniciarseccion(nodo *Usuarios){

    int ID;
    cin>>ID;
    cout<<"\nIngrese tu ID: ";
    cin>>ID;
    cin.ignore();
    string contraseña;
    cout<<"\nIngrese su contraseña: ";
    cin>>contraseña;
    cin.ignore();
    nodo *temp = Usuarios;
    
    while (temp != NULL) {
        if (temp ->info.ID == ID and temp->info.Contraseña == contraseña){
            cout<<"Iniciando seccion\n";
            cout<<"Bienvenido "<<temp->info.Nombre<<endl;
            return true;
        }
        temp = temp ->sig;
    }

    cout<<"ID de usuario o contraseña incorrecta\n";
    return false;

};

int main(){

    nodo *nuevoUsuario = crearNodo();

    guardarUsuario(nuevoUsuario->info);

    imprimirUsuario(nuevoUsuario);

    iniciarseccion(nuevoUsuario);
}