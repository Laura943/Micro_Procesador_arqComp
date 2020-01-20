#include <systemc.h>
#include <string>

#include "fetch.h"
#include "Testbench.h"

using namespace std;


void llenarInstrucciones(); //llena las instrucciones en le archivo

int sc_main(int argv, char* argc[]) {
	sc_time PERIOD(10,SC_NS);
	sc_time DELAY(10,SC_NS);
	sc_clock clock("clock",PERIOD,0.5,DELAY,true);

	Fetch ft("ft");
  	TestBench tb("tb");

	sc_signal<sc_uint<INSTRUCTION_SIZE>> inst_sg;
	
	ft.clk(clock);
	ft.instruction(inst_sg);
	
	tb.clk(clock);
	tb.instruction(inst_sg);
	
	sc_start();

	return 0;
}
