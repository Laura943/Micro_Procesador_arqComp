#ifndef PIPE_H
#define PIPE_H

#include <systemc>
#include <vector>
#include "macros.h"

SC_MODULE( Pipe ) {

		//entradas
	sc_in<bool> clk;
	sc_in< sc_uint<INSTRUCTION_SIZE> > datoIn;	

		//salidas 
	sc_out< sc_uint<INSTRUCTION_SIZE> > datoOut;		
	
	sc_uint<INSTRUCTION_SIZE> registros;

	
	void read() {
	
		registros = datoIn;
	
	}
	
	void write() {
		datoOut = registros;
	
	}

	SC_CTOR( Pipe ) {	
	
		SC_METHOD(read);
		sensitive << clk.neg();
			
		SC_METHOD(write);
		sensitive << clk.pos();
		
	}
};





#endif //PIPE_H