#ifndef ALU_H
#define ALU_H

#include "macros.h"
#include <iostream>
#include <systemc>

SC_MODULE( Alu ) {
	
	//entradas
	sc_in< bool > clk;
	sc_in< sc_int< DATA_SIZE > > data_op1, data_op2;
	sc_in< sc_uint<4> > tipoInstruccion;
	
	//salidas
	sc_out< bool > jump_out;
	sc_out< sc_int< DATA_SIZE> > operationResul;
	
	
	//variables 
	bool jump;
	sc_int< DATA_SIZE > resultado;
	
	void read() {
	
		switch( tipoInstruccion.read() ) {
			case 0: //NOP
				//resultado = 0;
				//jump = 0;
				break;
			
			case 1: //suma
				resultado = data_op1.read() + data_op2.read();
				jump = 0;		
				break;
			
			case 2: //resta
				if(data_op1.read() > data_op2.read()) {
					resultado = data_op1.read() - data_op2.read(); 
				}
				else {
					resultado = data_op2.read() - data_op1.read();
				}
				jump = 0;
				break;
				
			case 3: //load
				resultado = 0;
				jump = 0;
				break;
				
			case 4: //store	
 				resultado = data_op1.read();
				jump = 0;
				break;
			
			case 5: //AND
				resultado = data_op1.read() and data_op2.read(); 
				jump = 0;
				break;
				
			case 6: //OR
				resultado = data_op1.read() or data_op2.read(); 
				jump = 0;
				break;
				
			case 7: //not
				resultado = not data_op1.read();
				jump = 0;
				break;
				
			case 8: //jz	
				if( data_op1.read() + data_op2.read() == 0) {
					jump = 1;
				}
				else {
					jump = 0;
				}
				resultado = 0;
				break;
				
			case 9: //Jn
				if(data_op1.read() < 0) {
					jump = 1;
				} 		
				else {
					jump = 0;
				}
				resultado = 0;
				break;
		
			
		}
		write();
	}
	
	void write() { 
		operationResul.write( resultado );
		jump_out.write( jump );
	
	}
	
	SC_CTOR( Alu ) {
	
		SC_METHOD( read );
		sensitive << data_op1 << data_op2 << tipoInstruccion;


	}
};

 
#endif //ALU_H