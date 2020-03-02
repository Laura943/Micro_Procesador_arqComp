#ifndef PIPE4_H
#define PIPE4_H

#include "macros.h"
#include <iostream>
#include <systemc>

SC_MODULE( Pipe4 ) {

	//entradas
	sc_in< bool > clk;
	sc_in< sc_uint<4> > dirResul_in, tipoOperacion_in;
	sc_in< sc_int<DATA_SIZE> > operation_resul_in, memory_data_in;
		
	//salidas
	sc_out< sc_uint<4> > dirResul_out, tipoOperacion_out;
	sc_out< sc_int<DATA_SIZE> > operation_resul_out, memory_data_out;
		
	//variables
	sc_uint<4> dirResul, tipoOperacion;
	sc_int<DATA_SIZE> operation_resul, memory_data;
		
		
	void read() {
		dirResul = dirResul_in.read();
		tipoOperacion = tipoOperacion_in.read();
		operation_resul = operation_resul_in.read();
		memory_data = memory_data_in.read(); 
	}
	
	void write() {
		dirResul_out.write( dirResul );
		tipoOperacion_out.write( tipoOperacion );
		operation_resul_out.write( operation_resul );
		memory_data_out.write( memory_data );
	}	

	SC_CTOR( Pipe4 ) {
		
		//si el clk es pos se lee
		SC_METHOD( read );
		sensitive << clk.pos();
		
		//si el clk en neg se escribe
		SC_METHOD( write );
		sensitive << clk.neg();
	}
};

 
#endif //PIPE4_H