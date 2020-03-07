//g++ -Wall -std=c++11 conexion.cpp -o conexion.exe -lpthread
//ejecutar conexion.exe para calcular los movimientos en historial.txt
#include <iostream>       
#include <thread>        
#include <chrono>         
#include <cstdlib>
#include <fstream>
#include "macros.h"


 
using namespace std;
 
static bool terminado = false;
void moverLinea(ifstream &archivo, int linea);
void escritor();
void observador();
void brain();

int main() 
{
  
  thread escribir( escritor );
  thread observar( observador );
  thread aplicacion( brain );
  
  aplicacion.join();
  escribir.join();
  observar.join();
  

  
  return 0;
}

void escritor() { // mpr
	cout << "se prendio el mpr" << endl;
	system("./main.exe");
	
	terminado = true;
}

void brain() {

	cout << "se prendio el brain" << endl;
	system ("./brain.exe");
	if(terminado) 
		return ;

}

void observador() {
	string datos_src = "memoriaPrincipal.txt";
	ifstream datos(datos_src);
	ofstream hist ("../historial.txt", ios::ate | ios::app); 
	
	
	if(!hist) {
		cout << "no se pudo abrir historial" << endl;
	}
	
	if(!datos) {
		cout << "no se pudo abrir datoss" << endl;
	}
	
	if(!datos || !hist) {
		cout << "error al abrir los archivos " << endl;
		exit(1);
	}
	
	int ultimo;
	int actual;
	moverLinea(datos, 15);
	datos >> ultimo;	
	actual = ultimo;
	cout << "*el nuevo dato en la linea 15 es: " << actual << endl; // log
	
	datos.close();
	while( !terminado ) {
		std::this_thread::sleep_for (std::chrono::seconds(27));
		datos.open(datos_src);
		
		
		
		moverLinea(datos, 12);
		datos >> actual;
		hist << endl << actual ;
		cout << "se guardo " << actual << endl;
		moverLinea(datos, 13);
		datos >> actual;
		hist << endl << actual ;
		cout << "se guardo " << actual << endl;
		moverLinea(datos, 14);
		datos >> actual;
		hist << endl << actual ;
		cout << "se guardo " << actual << endl;
		moverLinea(datos, 15);
		datos >> actual;
		hist << endl << actual ;
		cout << "se guardo " << actual << endl;
		


		//hist  << endl << actual;
		datos.close();
		//std::this_thread::sleep_for (std::chrono::seconds(28));
	//	usleep(1000000);
	}

}


void moverLinea(ifstream &archivo, int linea) {
	archivo.seekg(0);
	int cont = 0;
	char aux = ' ';
	
	if(linea == 0) {
		return;
	}
	
	while( !archivo.eof() && aux != '\0') {
		aux = archivo.get();
		if(aux == '\n') {
			cont++;
		}
		if(cont == linea) {
			return;
		}
		
	}
	
}

