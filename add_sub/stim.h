//------------------------------------------------------------------
// Simple 4-bits adder
//
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------
#ifndef STIM_H
#define STIM_H

#include <systemc.h>

SC_MODULE(stim) {
	sc_in<bool> clk;
	sc_out<sc_uint<16> > ain, bin;
	sc_out<sc_uint<4> > op;
	void ps1() {

		ain.write(0b0000000000000000);
		bin.write(0b0000000000000000);
		op.write(0b0000000000000000);
		wait();

		ain.write(0b0000000000000110);
		bin.write(0b0000000000000011);

		op.write(0b0000000000000000);
		wait();

		op.write(0b0000000000000001);
		wait();

		op.write(0b0000000000000010);

		wait();

		op.write(0b0000000000000011);

		wait();

		op.write(0b0000000000000100);

		wait();

		op.write(0b0000000000000101);

		wait();


		op.write(0b0000000000000110);

		wait();


		sc_stop();                          // End simulation
	}

	SC_CTOR(stim) {
		SC_THREAD(ps1);                     // Run ps1 only ones
		sensitive << clk.pos();
	}
};
#endif
