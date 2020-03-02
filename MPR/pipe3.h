#ifndef PIPE3_H
#define PIPE3_H

#include "macros.h"
#include <iostream>
#include <systemc>

SC_MODULE( Pipe3 ) {

	//entradas
	sc_in< bool > clk; 
	sc_in< sc_uint<4> > dirResul_in, dirLoad_in, tipoOperacion_in;
	sc_in< sc_int< DATA_SIZE >> resul_operation_in;
 	
	//salidas
	sc_out< sc_uint<4> > dirResul_out, dirLoad_out, tipoOperacion_out;
	sc_out< sc_int< DATA_SIZE >> resul_operation_out;


	//variables
	sc_uint<4> dirResul, dirLoad, tipoOperacion;
	sc_int< DATA_SIZE > resul_operation;
	
	void read() {
		dirResul = dirResul_in.read();
		dirLoad = dirLoad_in.read();
		tipoOperacion = tipoOperacion_in.read();
		resul_operation = resul_operation_in.read();
	}
	
	void write() {
		dirResul_out.write( dirResul );
		dirLoad_out.write( dirLoad );
		tipoOperacion_out.write( tipoOperacion );
		resul_operation_out.write( resul_operation );
	}
	
	
	
	
	SC_CTOR( Pipe3 ) {
	
		//si el clk es pos se lee
		SC_METHOD( read );
		sensitive << clk.pos();
		
		//si el clk es neg se escribe
		SC_METHOD( write );
		sensitive << clk.neg();
		
	} 
};


#endif //PIPE3_H	