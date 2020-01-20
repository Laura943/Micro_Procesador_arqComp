#ifndef TESTBENCH_H
#define TESTBENCH_H

#include "fetch.h"
#include <iostream>

using namespace std;

SC_MODULE(TestBench) {

	//entradas
	sc_in< sc_uint<INSTRUCTION_SIZE> > instruction;
	sc_in<bool> clk;
	
	//salidas 
	

	void print() {
		cout << ": "; 
		for(int i = 0; i < 16 ; i++) {
			cout << instruction.read().range(16-(i+1),16-(i+1));
		}
		cout << endl;
		
	}
	
	void test() {
		vector<string> nombreInst = {"suma ", "read" , "wirte", "AND", "OR", "NOT", "J-carry", "J-over"};
		cout << "\t** instrucciones **" <<  endl << endl;  
				
	for(int i = 0; i < NUM_INSTRUCTIONS; ++i) {
		cout << "\t"<< nombreInst[i];
		wait();
		print();
	}
		
		
		sc_stop();
	}
	
	
	SC_CTOR(TestBench) {

		SC_THREAD(test);
		sensitive << clk.neg();
	}
	

	
	
};


#endif // TESTSUMADOR_H