#include <systemc.h>
#include <iostream>
#include "pc.h"
#include "pipe1.h"
#include "pipe2.h"
#include "pipe3.h"
#include "pipe4.h"
#include "archivoRegistro.h"
#include "decoder.h"
#include "memoriaInstruccion.h"
#include "mux.h"
#include "memoriaPrincipal.h"
#include "ALU.h"


int sc_main(int argv, char* argc[]) {

	sc_time PERIOD(10,SC_NS);
	sc_time DELAY(10,SC_NS);
	sc_clock clock("clock",PERIOD,0.5,DELAY,true);
	
	//instancias
	Pc pc("pc");
	Pipe1 pipe1("pipe1");
	Pipe2 pipe2("pipe2");
	Pipe3 pipe3("pipe3");
	Pipe4 pipe4("pipe4");
	ArchivoRegistro ar("ar");
	Decoder deco("deco");
	MemoriaInstruccion mi("mi");
	Mux mux("mux");
	MemoriaPrincipal mp("mp");
	Alu alu("alu");
	
	//seniales
	sc_signal< bool > jump_pc_alu, enable_mux_ar;
	
	sc_signal< sc_uint< INSTRUCTION_SIZE > > inst_im_pipe1, inst_pipe1_deco;
	
	sc_signal< sc_uint< 32 > > pc_im;
	
	sc_signal< sc_int< DATA_SIZE > > op1_ar_pipe2, op2_ar_pipe2, op1_pipe2_alu, 
	 op2_pipe2_alu, resul_alu_pipe3, resul_pipe3_mp_pipe4, data_mp_pipe4, resul_pipe4_mux,
	  data_pipe4_mux, data_mux_ar;
	  
	sc_signal< sc_int< 4 > > jumpDir_deco_pc;
	
	sc_signal< sc_uint< 4 > > dirResul_deco_pipe2, dirOp1_deco_ar_pipe2, dirOp2_deco_ar,
	 tipoInst_deco_pipe2, dirResul_pipe2_pipe3, dirLoad_pipe2_pipe3, tipoInst_pipe2_alu_pipe3,
	  dirResul_pipe3_mp_pipe4, dirLoad_pipe3_mp, tipoInst_pipe3_mp_pipe4, dirResul_pipe4_ar, 
	   tipoInst_pipe4_mux;
	   
		//conexiones
	
	//pc
	pc.clk(clock);
	pc.jump(jump_pc_alu);
	pc.jumpDir(jumpDir_deco_pc);
	
	pc.instructionOut(pc_im);
	
	//mi
	mi.clk(clock);
	mi.instructionLine(pc_im);
	
	mi.instruction_out(inst_im_pipe1);
	
	pipe1.clk(clock);
	pipe1.input_instruction(inst_im_pipe1);

	pipe1.output_instruction(inst_pipe1_deco);

	//deco
	deco.clk(clock);
	deco.instruction_in(inst_pipe1_deco);
	
	deco.jumpDir_out(jumpDir_deco_pc);
	deco.dirResul_out(dirResul_deco_pipe2);
	deco.op1_out(dirOp1_deco_ar_pipe2);
	deco.op2_out(dirOp2_deco_ar);
	deco.tipoInstruccion_out(tipoInst_deco_pipe2);
	
	//ar
	ar.clk(clock);
	ar.op1_dir(dirOp1_deco_ar_pipe2);
	ar.op2_dir(dirOp2_deco_ar);
	ar.writeDir(dirResul_pipe4_ar);
	ar.enable(enable_mux_ar);
	ar.writeData(data_mux_ar);

	ar.op1_data(op1_ar_pipe2);
	ar.op2_data(op2_ar_pipe2);
	
	//pipe2
	pipe2.clk(clock);
	pipe2.dirResul_in(dirResul_deco_pipe2);
	pipe2.dirLoad_in(dirOp1_deco_ar_pipe2);
	pipe2.tipoInstruccion_in(tipoInst_deco_pipe2);
	pipe2.op1_data_in(op1_ar_pipe2);
	pipe2.op2_data_in(op2_ar_pipe2);
	
	pipe2.dirResul_out(dirResul_pipe2_pipe3);
	pipe2.dirLoad_out(dirLoad_pipe2_pipe3);
	pipe2.tipoInstruccion_out(tipoInst_pipe2_alu_pipe3);
	pipe2.op1_data_out(op1_pipe2_alu);
	pipe2.op2_data_out(op2_pipe2_alu);

	//alu
	alu.clk(clock);
	alu.data_op1(op1_pipe2_alu);
	alu.data_op2(op2_pipe2_alu);
	alu.tipoInstruccion(tipoInst_pipe2_alu_pipe3);
	
	alu.jump_out(jump_pc_alu);
	alu.operationResul(resul_alu_pipe3);
	
	//pipe3
	pipe3.clk(clock);
	pipe3.dirResul_in(dirResul_pipe2_pipe3);
	pipe3.dirLoad_in(dirLoad_pipe2_pipe3);
	pipe3.tipoOperacion_in(tipoInst_pipe2_alu_pipe3);
	pipe3.resul_operation_in(resul_alu_pipe3);
	
	pipe3.dirResul_out(dirResul_pipe3_mp_pipe4);
	pipe3.dirLoad_out(dirLoad_pipe3_mp);
	pipe3.tipoOperacion_out(tipoInst_pipe3_mp_pipe4);
	pipe3.resul_operation_out(resul_pipe3_mp_pipe4);
	
	//mp
	mp.clk(clock);
	mp.dirLoad(dirLoad_pipe3_mp);
	mp.dirResul(dirResul_pipe3_mp_pipe4);
	mp.tipoOperacion(tipoInst_pipe3_mp_pipe4);
	mp.operationResul(resul_pipe3_mp_pipe4); 
	
	mp.memory_data(data_mp_pipe4);
	
	//pipe4
	pipe4.clk(clock);
	pipe4.dirResul_in(dirResul_pipe3_mp_pipe4);
	pipe4.tipoOperacion_in(tipoInst_pipe3_mp_pipe4);
	pipe4.operation_resul_in(resul_pipe3_mp_pipe4);
	pipe4.memory_data_in(data_mp_pipe4);
	
	pipe4.dirResul_out(dirResul_pipe4_ar);
	pipe4.tipoOperacion_out(tipoInst_pipe4_mux);
	pipe4.operation_resul_out(resul_pipe4_mux);
	pipe4.memory_data_out(data_pipe4_mux);
	
	//mux
	mux.clk(clock);
	mux.tipoOperacion(tipoInst_pipe4_mux);
	mux.operation_resul(resul_pipe4_mux);
	mux.memoryData(data_pipe4_mux);
	
	mux.enable_out(enable_mux_ar);
	mux.data_out(data_mux_ar);




	sc_start();


	return 0;
}