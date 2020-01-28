#ifndef DECODIFICADOR_INST_H
#define DECODIFICADOR_INST_H

#include <systemc>
#include <iostream>
#include <macros.h>

SC_MODULE( DecodificadorInstruc ) {

	//entradas
	sc_in< sc_uint< INSTRUCTION_SIZE > > instruccion;
		
	//salidas
	sc_out<bool> control; // 0 = load | 1 = store 
	sc_out<sc_uint< 4 > > dir1;
	sc_out<sc_uint< 4 > > dir2;
 
 
 	sc_uint< INSTRUCTION_SIZE > auxInstruction;
 
 	sc_uint<4> decodificarDir1() {
		sc_uint<4> direc1;
		auxInstruction = instruccion.read();
		
		for(int i = 3, j = INSTRUCTION_SIZE-5; i >= 0 ; i--, j--) {
			direc1[i] = auxInstruction[j];
		}
	
		
		return direc1;
	}
	
	sc_uint<4> decodificarDir2() {
		sc_uint<4> direc2;
		auxInstruction = instruccion.read();
		
		for(int i = 3, j = INSTRUCTION_SIZE-9; i >= 0 ; i--, j--) {
			direc2[i] = auxInstruction[j];
		}
		
		return direc2;
	}
 
 
 
	void decodificar() {
	
		sc_uint<4> tipoInstruccion;
		auxInstruction = instruccion.read();
		
		for(int i = 3, j = INSTRUCTION_SIZE-1; i >= 0 ; i--, j--) {
			tipoInstruccion[i] = auxInstruction[j];
		}	
		
		switch( tipoInstruccion ) {
			case 0 :	
					
					break;
					
			case 1 :
					control.write(0);
					dir1.write( decodificarDir1() );
					dir2.write( decodificarDir2() );
					break;
					
			case 2 : 
					control.write(1);
					dir1.write( decodificarDir1() );
					dir2.write( decodificarDir2() );
					break;
					
			case 3 :
				
					break;
					
			case 4 :
					
					break;
					
			case 5 :
					
					break;
					
			case 6 :
					
					break;
					
			case 7 :
					
					break;

		}
	
	}
	
	


	SC_CTOR( DecodificadorInstruc) {
		
		
		SC_METHOD(decodificar);
		sensitive << instruccion;
	
	}
	
	

};


#endif //DECODIFICADOR_INST_H 