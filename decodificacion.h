#ifndef DECODIFICACION_H
#define DECODIFICACION_H

#include <systemc>
#include "archivoRegistro.h"
#include "decodificadorInstruc.h"

SC_MODULE( Decodificacion ) {
	
		// entradas
		sc_in< sc_uint<INSTRUCTION_SIZE>> instruccion;
		sc_in< sc_int<INSTRUCTION_SIZE>> data_in;
		sc_in<bool> clk;
		
		//salidas
		sc_out< sc_int<INSTRUCTION_SIZE>> data_out;
		
		//modulos
		ArchivoRegistro *ar;
		DecodificadorInstruc *di;
		
		//seniales
		sc_signal<bool> control_sg;
		sc_signal<sc_uint< 4 >> dir1_sg, dir2_sg;
		 
		SC_CTOR( Decodificacion ) {

		di = new DecodificadorInstruc("ar");
		ar = new ArchivoRegistro("di");
		
		di->instruccion(instruccion);
		di->control(control_sg);
		di->dir1(dir1_sg);
		di->dir2(dir2_sg);
		
		ar->data_in(data_in);
		ar->dir1(dir1_sg);
		ar->dir2(dir2_sg);
		ar->control(control_sg);
		ar->clk(clk);
		ar->data_out(data_out);
	}
	
	~Decodificacion() {
		delete ar;
		delete di;
	}
};



#endif //DECODIFICACION_H