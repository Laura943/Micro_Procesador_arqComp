#ifndef DECODER_h
#define DECODER_h

#include "macros.h"
#include <systemc>
#include <iostream>

using namespace std;

SC_MODULE( Decoder ) {

	//entradas 
	sc_in< sc_uint<INSTRUCTION_SIZE> > instruction_in;
	sc_in<bool> clk;
	
	//salidas
	sc_out< sc_int<4> > jumpDir_out;
	sc_out< sc_uint<4> > dirResul_out, op1_out, op2_out, tipoInstruccion_out;

	//variables
	sc_int<4> jumpDir;
	sc_uint<4> dirResul, op1, op2, tipoInstruccion;


	void read() {
		for(int i = 3, j = INSTRUCTION_SIZE - 1; i >= 0; i--, j--) {
			tipoInstruccion[i] = instruction_in.read()[j];
		}	
		
		switch( tipoInstruccion ) {
			
			case 0: //instruccion NOP
				//jumpDir = 0;
				//dirResul = 0;
				//op1 = 0;
				//op2 = 0;
				//tipoInstruccion = 0;
				break;
			
			case 1: //instruccion suma
				
			case 2: //instruccion resta
				jumpDir = 0;
				for(int i = 3, j = INSTRUCTION_SIZE - 1; i >= 0; i--, j--) {
					dirResul[i] = instruction_in.read()[j-4];
					op1[i] = instruction_in.read()[j-8];
					op2[i] = instruction_in.read()[j-12];
				}		
				break;
				
			case 3: //instruccion load
				jumpDir = 0;
				op2 = 0;
				for(int i = 3, j = INSTRUCTION_SIZE - 1; i >= 0; i--, j--) {
					dirResul[i] = instruction_in.read()[j-4];
					op1[i] = instruction_in.read()[j-8];
				}		
				break;
			
			case 4: //instruccion store
				jumpDir = 0;
				op2 = 0;
				 for(int i = 3, j = INSTRUCTION_SIZE - 1; i >= 0; i--, j--) {
					op1[i] = instruction_in.read()[j-4];
					dirResul[i] = instruction_in.read()[j-8];
				}		
				
				break;
				
			case 5: //operacion AND
				
			case 6: //operacion OR
				
			case 7: //operacion NOT
				jumpDir = 0;
				for(int i = 3, j = INSTRUCTION_SIZE - 1; i >= 0; i--, j--) {
					dirResul[i] = instruction_in.read()[j-4];
					op1[i] = instruction_in.read()[j-8];
					op2[i] = instruction_in.read()[j-12];
				}		
				break;
				
			case 8: //operacion Jz
				
			case 9: //operacion Jn
				dirResul = 0;
				for(int i = 3, j = INSTRUCTION_SIZE - 1; i >= 0; i--, j--) {
					jumpDir[i] = instruction_in.read()[j-4];
					op1[i] = instruction_in.read()[j-8];
					op2[i] = instruction_in.read()[j-12];
				}
				break;
				
			default: //si no esta registrada la trata como una NOP
				//jumpDir = 0;
				//dirResul = 0;
				//op1 = 0;
				//op2 = 0;
				//tipoInstruccion = 0;
				break;
		}
		write();
	}
			
	
	void write() {
		jumpDir_out.write( jumpDir );
		dirResul_out.write( dirResul );
		op1_out.write( op1 );
		op2_out.write( op2 );
		tipoInstruccion_out.write( tipoInstruccion );
	}


	SC_CTOR( Decoder ) {
	
		jumpDir = 0;
		dirResul = 0;
		op1 = 0;
		op2 = 0;
		tipoInstruccion = 0;
	
		SC_METHOD( read );
		sensitive << instruction_in;
	

	}
	
};


#endif //DECODER_h