#ifndef MUX_H
#define MUX_H

#include <iostream>
#include <systemc>
#include "macros.h"

using namespace std;

SC_MODULE( Mux ) {

	//entradas
	sc_in< bool > clk;
	sc_in< sc_uint<4> > tipoOperacion;
	sc_in< sc_int<DATA_SIZE> > operation_resul, memoryData;
	
	//salidas
	sc_out< bool > enable_out;
	sc_out< sc_int<DATA_SIZE> > data_out;
	
	//variables
	bool enable;
	sc_int< DATA_SIZE > data;
	
	void read() {
		
		switch( tipoOperacion.read() ) {
			case 0: //NOP
			case 4: // estore
			case 8: //Jz
			case 9: //Jn
				enable = 0;
				//data = 0;
				break; 
			
			case 3: // load	 
				enable = 1;
				data = memoryData.read(); 
				break;
			case 1: //suma
			case 2: //resta
			case 5: //and
			case 6: //or
			case 7: //not
				enable = 1;
				data = operation_resul.read(); 
				break;
			default:
				enable = 0;
				//data = 0;
				break; 
		}
		write();
	}

	void write() {
		enable_out.write( enable );
		data_out.write( data );
	}

	SC_CTOR( Mux ) {
		
		SC_METHOD( read );	
		sensitive << tipoOperacion << operation_resul << memoryData;

	
	}

};

#endif //MUX_H