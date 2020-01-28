#ifndef ARCHIVO_REGISTRO_H
#define ARCHIVO_REGISTRO_H

#include "macros.h"

SC_MODULE( ArchivoRegistro ) { 

	//entradas
	sc_in<sc_int<INSTRUCTION_SIZE>> data_in;
	sc_in< sc_uint< 4 > > dir1;
	sc_in< sc_uint< 4 > > dir2;

	sc_in<bool> control;
	sc_in<bool> clk;
	
	//salidas
	sc_out<sc_int<INSTRUCTION_SIZE>> data_out;

	// variables
	sc_int< INSTRUCTION_SIZE > *registros;

	//funciones
	
	void load() {
		if(control == 0) {

			data_out.write( registros[dir1.read()] ); 
		}
	}
	
	void store() {
		if(control == 1) {
			sc_int<INSTRUCTION_SIZE> temp;

			temp = data_in.read();
			registros[dir2.read()] =  temp ;
		}
	}


	SC_CTOR( ArchivoRegistro ) {
		registros = new sc_int<INSTRUCTION_SIZE> [16];
		for(int i = 0 ; i < 16 ; i++) {
			registros[i] = 0;
		}
		
		SC_METHOD( store ); // se hace el procesamiento de las instruccion
		sensitive << clk.neg();

		SC_METHOD( load ); // se hace la operacion de  cargar los datos
		sensitive << clk.pos();

	}

	~ArchivoRegistro() {
		delete [] registros;
	}



};


#endif // ARCHIVO_REGISTRO_H