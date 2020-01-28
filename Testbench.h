#ifndef TESTBENCH_H
#define TESTBENCH_H

#include <iostream>
#include <vector>
#include "decodificacion.h"

using namespace std;

SC_MODULE(TestBench) {

	//salidas
	sc_out< sc_uint<INSTRUCTION_SIZE>> instruccion;
	sc_out< sc_int<INSTRUCTION_SIZE>> data_in;
	
	
	//entradas 
	sc_in< sc_int<INSTRUCTION_SIZE>> data_out;
	sc_in<bool> clk;
	// variables 

	vector<string> strign_test_instructions;
	vector<sc_uint<INSTRUCTION_SIZE>> test_instructions;
	
	//funciones


	void imprimir() {
			//imprimira basura cuando la instruccion sea de escritura
		cout << "el dato pedido es: " << data_out.read() << endl; 
	}
	
	void test() {
	
		int dato = 5;
		for(auto a : test_instructions) {
			instruccion.write( a );
			data_in.write( dato++);
			 
			wait();
			imprimir();
			
		}
	
	
	
		sc_stop();
	}
	
	
	SC_CTOR(TestBench) {

		strign_test_instructions.push_back("0010000000010000");//cargar 
		strign_test_instructions.push_back("0010000001000000");//cargar 
		strign_test_instructions.push_back("0001000100000000");//leer
		strign_test_instructions.push_back("0001010000000000");//leer
	
		for(auto a : strign_test_instructions ) {
			sc_uint<INSTRUCTION_SIZE> aux;
			
			for(int i = 0; i < INSTRUCTION_SIZE; i++) {
				aux[i] = a[INSTRUCTION_SIZE-(i+1)] - '0' ; 
			}
			
			test_instructions.push_back(aux);
			
 		}
		
		cout << "las instrucciones que se usaran son "  << endl;
		for(auto a: test_instructions) {
			
			for(int i= 0; i < INSTRUCTION_SIZE ; i++) {
				cout << a.range(INSTRUCTION_SIZE-(i+1),INSTRUCTION_SIZE-(i+1));
			}
			cout << endl;
		}

		cout << endl << endl;
		
		SC_THREAD(test);
		sensitive << clk.neg();
		

	}
	

	
	
};


#endif // TESTSUMADOR_H