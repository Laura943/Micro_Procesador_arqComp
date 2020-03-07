#ifndef PC_H
#define PC_H

#include <iostream>
#include <systemc>
#include "macros.h"

#include <thread>        
#include <chrono>     

using namespace std;

SC_MODULE( Pc ) {

	//entradas
	sc_in<bool> jump;
	sc_in< sc_int<4> > jumpDir; 
	sc_in<bool> clk;
	
	//salidas
	sc_out< sc_uint<32> > instructionOut;  

	//variables
	sc_uint<32> instructionLine;
	
	//funciones

	void read() {
		std::this_thread::sleep_for (std::chrono::seconds(1)); // dar tiempo a la conexion para que guarde el dato
		if(jump.read() == 1) {
			instructionLine += jumpDir.read();
		}
		else {
			instructionLine++;
		}
	
	}
	
	void write() {
		
			if(instructionLine > NUM_INSTRUCTIONS+4) { 
				sc_stop();
			}  
		instructionOut.write( instructionLine );
	}


	SC_CTOR( Pc ) {
		instructionLine = -1;
		
		//en positivo lee
		SC_METHOD( read );
		sensitive << clk.pos();
	
		//en negativo escribe
		SC_METHOD( write )
		sensitive << clk.neg();
	
	}

};


#endif //PC_H