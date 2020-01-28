#include <systemc.h>
#include <string>

#include "decodificacion.h"
#include "Testbench.h"

using namespace std;


int sc_main(int argv, char* argc[]) {
	sc_time PERIOD(10,SC_NS);
	sc_time DELAY(10,SC_NS);
	sc_clock clock("clock",PERIOD,0.5,DELAY,true);

	Decodificacion deco("deco");
  	TestBench tb("tb");

	sc_signal<sc_uint<INSTRUCTION_SIZE>> instruccion_sg;
	sc_signal<sc_int<INSTRUCTION_SIZE>> data_in_sg, data_out_sg;
	
	deco.instruccion(instruccion_sg);
	deco.data_in(data_in_sg);
	deco.clk(clock);
	deco.data_out(data_out_sg);
	
	tb.clk(clock);
	tb.instruccion(instruccion_sg);
	tb.data_in(data_in_sg);
	tb.data_out(data_out_sg);
	
	sc_start();

	return 0;
}
