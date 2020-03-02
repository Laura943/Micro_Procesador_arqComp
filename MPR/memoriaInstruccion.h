#ifndef MEMORIA_INSTRUCCION_H
#define MEMORIA_INSTRUCCION_H

#include "macros.h"
#include <fstream>
#include <systemc>
#include <string>

using namespace std;

SC_MODULE( MemoriaInstruccion ) {

	//entradas
	sc_in<bool> clk;
	sc_in< sc_uint<32> > instructionLine;
	
	//salidas
	sc_out< sc_uint< INSTRUCTION_SIZE >> instruction_out;

	//variables
	sc_uint< INSTRUCTION_SIZE > instruction;



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


	void read() { // por ahora no hace manejo de dependencia de datos
		
		ifstream registros;
		string aux = "";
		registros.open("memoriaInstruccion.txt");
		int numeroInstrucciones;
		
		if(!registros) {
			cout << "no se pudo abrir el archivo" << endl;
			exit(1);
		}
		
		registros.seekg(0, registros.end);
		numeroInstrucciones = registros.tellg(); 
		registros.seekg(0);
		
		int linea = instructionLine.read();
		//si se esta buscando en una linea mayor a las que hay, se busca la ultima instruccion
		if(linea > numeroInstrucciones) {
			linea = numeroInstrucciones;
		}
		
		moverLinea(registros, linea);
		
		//getline(registros, aux);
		
		for(int i = 0 ; i < 16 ; i++) {
			char a;
			registros >> a;
			aux += a;
		}

		for(int i = 0, j = INSTRUCTION_SIZE-1; i < INSTRUCTION_SIZE; i++, j--) {
			instruction[i] = aux[j] - '0';
		}
		
		write();
	}
	
	

	void write() {
		//cout << "im: el dato que sale es " << instruction << endl; //log
		instruction_out.write( instruction );
	}

	SC_CTOR( MemoriaInstruccion ) {
		
		instruction = 0;
		

		SC_METHOD( read );
		sensitive << instructionLine;

	}

};

#endif //MEMORIA_INSTRUCCION_H