#include <iostream>
#include <ctime>
using namespace std;

struct fecha { 
	int d,m,a;
};

struct nodo { 
	fecha info; 
	nodo *sig;
} ;


bool esBisiesto(int a) {
    // Un año es bisiesto si es divisible por 4, pero no por 100,
    // excepto si también es divisible por 400.
    if (a % 4 == 0) {
        if (a % 100 == 0) {
            if (a % 400 == 0) {
                return true;
            } else {
                return false;
            }
        } else {
            return true;
        }
    } else {
        return false;
    }
}

int numeroDias(fecha feValidar)
{
	
	switch (feValidar.m) 
	{
        case 1: // Enero
        case 3: // Marzo
        case 5: // Mayo
        case 7: // Julio
        case 8: // Agosto
        case 10: // Octubre
        case 12: // Diciembre
            return 31;
        case 4: // Abril
        case 6: // Junio
        case 9: // Septiembre
        case 11: // Noviembre
            return 30;
        case 2: //  Febrero
        
        	if (esBisiesto(feValidar.a)) 
			{
                return 29;
            } 
			
			else 
			{
                return 28;
            }
	}
}


fecha IngresarFecha()
{	fecha feIngresar;
	do{
		cout<<"Ingrese el año debe ser mayor o igual a 1900:  ";
		cin>>feIngresar.a;
	}while (feIngresar.a<1900);
	
	do{
		cout<<"Ingrese el mes:  ";
		cin>>feIngresar.m;
	}while (feIngresar.m<1 or feIngresar.m>12 );
	
	do{
		cout<<"Ingrese el dia:  ";
		cin>>feIngresar.d;
	}while (feIngresar.d>numeroDias(feIngresar) or feIngresar.d<=0);
	return feIngresar;
		
}

void imprimirNodo(nodo *imp){
	cout<<"Fecha:  "<<imp->info.d<<"/"<<imp->info.m<<"/"<<imp->info.a<<endl;
}

fecha ObtenerFechaActual()
{
	time_t tiempoActual = time(NULL);
	tm* fechaLocal = localtime(&tiempoActual);
	fecha fecha;
	fecha.d = fechaLocal->tm_mday;
	fecha.m = fechaLocal->tm_mon + 1;
	fecha.a = fechaLocal->tm_year + 1900;
	
	return fecha;
}

