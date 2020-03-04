#ifndef MEMORIA_PRINCIPAL_H
#define MEMORIA_PRINCIPAL_H

#include <iostream>
#include <fstream>
#include "macros.h"
#include <systemc>
#include <string>

using namespace std;

SC_MODULE( MemoriaPrincipal ) {

	//entradas
	sc_in< bool > clk;
	sc_in< sc_uint<4> > dirLoad, dirResul, tipoOperacion;
	sc_in< sc_int< DATA_SIZE > > operationResul; 

	//salidas
	sc_out< sc_int<DATA_SIZE > > memory_data;

	//variables 
	sc_int< DATA_SIZE > data;	

	void read() {
		
		if(tipoOperacion.read() == 3) {// la operacion es load
			int aux;
			ifstream memoria("memoriaPrincipal.txt");
		
			moverLinea( memoria, dirLoad.read() );
			memoria >> aux;
			data = aux;
			
			memoria.close();
		}
		else if(tipoOperacion.read() == 4) { // la operacion es store
			cambiarLinea( "memoriaPrincipal.txt", dirResul.read(), operationResul.read() ); 
			data = 0;
		}
		else {
			data = 0;
		}
			
		write();
	}

	void write() {
		memory_data.write( data );
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



void cambiarLinea(string nombreArchivo, int lineaBuscada, int remplazar) {
	
	ofstream temp("temp.txt");
	ifstream archivo(nombreArchivo);
	const int TAM = 16; // un txt de 16 lineas
	int contenido, i;
	
	if(!temp || !archivo) {
		cout << "no se pudo abrir el archivo" << nombreArchivo << endl;
		exit(1);
	}

	archivo.seekg(0);
	
	for(i = 0; i < TAM && !archivo.eof(); i++) {
	
		moverLinea(archivo, i);
		archivo >> contenido;
		
		if(i != lineaBuscada) {
			temp << contenido ;
			if(i != TAM-1) {
				temp << endl;
			}
		}
		else {
			temp << remplazar ;
			if(i != TAM-1) {
				temp << endl;
			}
		}
		
	}

	archivo.close();
	temp.close();
	remove( nombreArchivo.c_str() );
	rename("temp.txt", nombreArchivo.c_str() );
	
}

	SC_CTOR( MemoriaPrincipal ) {

		SC_METHOD( read );
		sensitive << dirLoad << dirResul << tipoOperacion << operationResul;
	

		
	}


};


#endif // MEMORIA_PRINCIPAL_H