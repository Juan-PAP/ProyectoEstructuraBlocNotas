#include <iostream>
#include <string>
#include <ctime>
#include "TDANodo.cpp"
using namespace std;

struct nota
{
	string id;
	string titulo;
	string contenido;
	fecha fechaCreacion;
	fecha fechaModificacion;
	nota *siguiente;
	nota *anterior;
};

nota CrearNota(int idUsuario, int numeroNota)
{
	nota nota;
	string stringUsuario = to_string(idUsuario);
	string idNota = to_string(numeroNota + 1);
	nota.id = stringUsuario + "-" + idNota;
	cout<<"Ingrese el titulo de la nota: ";
	getline(cin, nota.titulo);
	cout<<endl;
	cout<<"Ingrese el contenido de la nota: "<<endl;
	getline(cin, nota.contenido);
	cout<<endl;
	nota.fechaCreacion = ObtenerFechaActual();
	nota.fechaModificacion = {0, 0, 0};
	
	return nota;
}

void EditarNota(nota &nota)
{
	bool cambios;
	char cTitulo, cContenido;
	
	cout<<"Desea cambiar el titulo de la nota? (S/N) ";
	cin>>cTitulo;
	cout<<endl;
	bool cambiarTitulo;
	if (tolower(cTitulo) == 's')
	{
		string nuevoTitulo;
		cout<<"Ingrese el nuevo titulo de la nota: "<<endl;
		getline(cin, nuevoTitulo);
		
		nota.titulo = nuevoTitulo;
		cambios = true;
	}
	
	cout<<"Desea cambiar el contenido de la nota? (S/N) ";
	cin>>cContenido;
	cout<<endl;
	bool cambiarContenido;
	if (tolower(cContenido) == 's')
	{
		string nuevoContenido;
		cout<<"Ingrese el nuevo contenido de la nota: "<<endl;
		getline(cin, nuevoContenido);
		
		nota.contenido = nuevoContenido;
		cambios = true;
	}
	
	if (cambios == true)
	{
		cout<<"Nota modificada exitosamente."<<endl;
		nota.fechaModificacion = ObtenerFechaActual();
	}
}

void MostrarNota(nota nota)
{
	if (nota.anterior != NULL)
	{
		cout<<"NOTA ANTERIOR: "<<nota.anterior->titulo<<endl;
	}
	
	cout<<"ID: "<<nota.id<<endl;
	cout<<"TITULO: "<<nota.titulo<<endl;
	cout<<"CONTENIDO: "<<nota.contenido<<endl;
	cout<<"FECHA CREACION: "<<nota.fechaCreacion.d<<"/"<<nota.fechaCreacion.m<<"/"<<nota.fechaCreacion.a<<endl;
	
	if (nota.fechaModificacion.a != 0 );
	{
		cout<<"FECHA MODIFICACION: "<<nota.fechaModificacion.d<<"/"<<nota.fechaModificacion.m<<"/"<<nota.fechaModificacion.a<<endl;
	}
	
	if (nota.siguiente != NULL)
	{
		cout<<"NOTA SIGUIENTE: "<<nota.siguiente->titulo<<endl;
	}
}

void EliminarNota(nota &nota)
{
	nota.anterior->siguiente = nota.siguiente;
	nota.siguiente->anterior = nota.anterior;
	
	delete(nota.anterior);
	delete(nota.siguiente);
	
}

int main()
{
	nota miNota = CrearNota(1035971461, 0);
	cout<<"ASI QUEDO LA NOTA:"<<endl;
	cout<<"ID: "<<miNota.id<<endl;
	cout<<"TITULO: "<<miNota.titulo<<endl;
	cout<<"CONTENIDO: "<<miNota.contenido<<endl;
	cout<<"FECHA CREACION: "<<miNota.fechaCreacion.d<<"/"<<miNota.fechaCreacion.m<<"/"<<miNota.fechaCreacion.a<<endl;
	return 0;
}