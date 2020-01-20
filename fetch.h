#ifndef FETCH_H
#define FETCH_H

#include "Pipe.h"
#include "instructionMen.h" 

SC_MODULE( Fetch ) {

	//entradas
	sc_in< bool > clk;
	
	//salidas
	sc_out< sc_uint<INSTRUCTION_SIZE> > instruction;
	
	//modulos
	Pipe *pipe;
	instructionMen *im;
	
	//seniales
	sc_signal<sc_uint<INSTRUCTION_SIZE>> im_pipe_sg;


	SC_CTOR( Fetch ) {
	
		pipe = new Pipe("pipe"); 
		im = new instructionMen("im");
		
		im->clk(clk);
		im->instruction(im_pipe_sg);
		
		pipe->clk(clk);
		pipe->datoIn(im_pipe_sg);
		pipe->datoOut(instruction);	

	}
	
	~Fetch() {
		delete pipe;
		delete im;	
	}
};

#endif // FETCH_H