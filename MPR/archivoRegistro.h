#ifndef ARCHIVO_REGISTRO_H
#define ARCHIVO_REGISTRO_H

#include <iostream>
#include <systemc>
#include "macros.h"


SC_MODULE( ArchivoRegistro ) {


	//entradas 
	sc_in< sc_uint<4> > op1_dir, op2_dir, writeDir;
	sc_in< bool > clk, enable;
	sc_in< sc_int< DATA_SIZE > > writeData;
	
	//salidas
	sc_out< sc_int< DATA_SIZE > > op1_data, op2_data;
	

	//variables
	sc_int< DATA_SIZE > data[16];


	void read() {
		
		if(enable == 1) {
			data[ writeDir.read() ] = writeData.read();

		}
		write();
	}

	void write() {
		op1_data.write( data[ op1_dir.read() ] );
		op2_data.write( data[ op2_dir.read() ] );
	}





	SC_CTOR( ArchivoRegistro ) {
	
		for(int i = 0; i < 16; i++) {
			data[i] = 0; 
		} 
	
		SC_METHOD( read );
		sensitive << op1_dir << op2_dir << writeDir << enable << writeData;
		
	

	}


};


#endif //ARCHIVO_REGISTRO_H	