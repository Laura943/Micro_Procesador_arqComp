#include <iostream>       
#include <thread>        
#include <chrono>         
#include <cstdlib>
#include <fstream>


 
using namespace std;
 
static bool terminado = false;
void moverLinea(ifstream &archivo, int linea);
void escritor();
void observador();

int main() 
{
  
  thread escribir( escritor );
  thread observar( observador );
  
  escribir.join();
  observar.join();
  

  
  return 0;
}

void escritor() { // mpr

	system("./main.exe");
	
	terminado = true;
}

void observador() {
	string datos_src = "memoriaPrincipal.txt";
	ifstream datos(datos_src);
	ofstream hist ("historial.txt", ios::ate | ios::app); 
	
	
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
	cout << "*el nuevo dato en la linea 15 es: " << actual << endl;
	
	datos.close();
	while( !terminado ) {
		datos.open(datos_src);
		moverLinea(datos, 15);
		datos >> actual;
	
		cout << "el dato actual es: " << actual <<endl;
	
		if( actual != ultimo ) {
			ultimo = actual;
			cout << "el dato en la linea 15 es: " << actual << endl;
			hist << endl << actual ;
		}
		
		datos.close();
		std::this_thread::sleep_for (std::chrono::seconds(1));
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

