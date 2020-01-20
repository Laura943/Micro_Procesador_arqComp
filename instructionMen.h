#ifndef IM_H
#define IM_H

#include "macros.h"
#include <systemc>

SC_MODULE( instructionMen ) {
	ifstream IM;
	//entradas
	sc_in< bool > clk;

	//salida
	sc_out< sc_uint<INSTRUCTION_SIZE> > instruction;
	
	
	
	void searchInstruction() {
		char line[INSTRUCTION_SIZE ];
		sc_uint<INSTRUCTION_SIZE> temp;
		
		IM.getline(line, INSTRUCTION_SIZE);
		
		for(int i = 0 ; i < INSTRUCTION_SIZE ; i++) {
			temp[i] = line[16-(i+1)] - '0'; 
		}

		instruction = temp;
	}

	SC_CTOR( instructionMen ) {
		IM.open(ARCHIVE);
		IM.seekg(INSTRUCTION_SIZE);
		
		SC_METHOD(searchInstruction);
		sensitive << clk.neg(); 
	}
	
	~instructionMen() {
		IM.close();
	}

};




#endif //IM_H