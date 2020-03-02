#ifndef PIPE2_H
#define PIPE2_H

#include <systemc>
#include <iostream>
#include "macros.h"

SC_MODULE( Pipe2 ) {

	//entradas
	sc_in< bool > clk;
	sc_in< sc_uint<4> > dirResul_in, dirLoad_in, tipoInstruccion_in;
	sc_in< sc_int< DATA_SIZE > > op1_data_in, op2_data_in;
	
	//salidas
	sc_out< sc_uint<4> > dirResul_out, dirLoad_out, tipoInstruccion_out;
	sc_out< sc_int< DATA_SIZE > > op1_data_out, op2_data_out;
	
	//variables
	sc_uint<4> dirResul, dirLoad, tipoInstruccion;
	sc_int< DATA_SIZE > op1_data, op2_data;


	void read() {
		dirResul = dirResul_in.read();
		dirLoad = dirLoad_in.read();
		tipoInstruccion = tipoInstruccion_in.read();
		op1_data = op1_data_in.read();
		op2_data = op2_data_in.read();
	}
	
	void write() {
		dirResul_out.write( dirResul ); 
		dirLoad_out.write( dirLoad );
		tipoInstruccion_out.write( tipoInstruccion ); 
		op1_data_out.write( op1_data ); 
		op2_data_out.write( op2_data );
	
	}


	SC_CTOR( Pipe2 ) {
	
		//lee cuando el clk esta en pos
		SC_METHOD( read );
		sensitive << clk.pos();
		
		//escribe cuando el clk esta en neg
		SC_METHOD( write );
		sensitive << clk.neg();
	}
	
};




#endif //PIPE2_H