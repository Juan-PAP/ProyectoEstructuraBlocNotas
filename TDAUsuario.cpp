#include <iostream>
#include <string>
#include <limits>

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
            confirmarID = false;
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

int main(){

    nodo *nuevoUsuario = crearNodo();

    imprimirUsuario(nuevoUsuario);

}