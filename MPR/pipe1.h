#ifndef PIPE1_H
#define PIPE1_H

#include <systemc>
#include "macros.h"

SC_MODULE( Pipe1 ) {

	//entradas
	sc_in< sc_uint< INSTRUCTION_SIZE> > input_instruction;
	sc_in<bool> clk;

	//salidas
	sc_out< sc_uint< INSTRUCTION_SIZE> > output_instruction;
	
	
	//variable
	sc_uint< INSTRUCTION_SIZE> registro;
	
	void read() {
		registro = input_instruction.read();
	}
	
	void write() {
		output_instruction.write( registro );
	}
	
	SC_CTOR( Pipe1 ) {
		
		//cuando sea pos lee
		SC_METHOD( read );
		sensitive << clk.pos();
		
		//cuando sea neg escribe
		SC_METHOD( write );
		sensitive << clk.neg();
	}

};

	
#endif //PIPE1_H