//------------------------------------------------------------------
// 4-bits adder checker module
//
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------
#ifndef CHECK_H
#define CHECK_H

#include <systemc.h>

#include <iostream>
using namespace std;

SC_MODULE(check) {
	sc_in<bool> clk;
	sc_in<sc_uint<16> > ain, bin;
	sc_in<bool> ci, as;
	sc_in<sc_uint<16> > sum;
	sc_in<bool> co;
	sc_in<bool> zflag, oflag, lflag;
	sc_in< sc_uint<4> > control;
	sc_uint<5> sumc;

	void pc1() {
		string name[7] = {"ADD: ","SUB: ","XOR: ","AND: ","OR: ","NOT A: ","STL: "};
		string op[7] = { " + "," - "," ^ "," & "," | "," ~ "," < " };
		int con = control.read();
		if (con != 5) {
			cout << name[con] << ain.read() << op[con] << bin.read() << " = " << sum.read();
		}
		else {
			cout << name[con] <<" ~ "<<ain.read()<< " = " << sum.read();
		}
		sc_uint<16> nota = ~ain.read();
		if ((con == 0 && sum.read() == (ain.read()+bin.read()) )||
			(con == 1 && sum.read() == (ain.read() - bin.read()) )||
			(con == 2 && sum.read() == (ain.read() ^ bin.read()) )||
			(con == 3 && sum.read() == (ain.read() & bin.read()) )||
			(con == 4 && sum.read() == (ain.read() | bin.read()) )||
			(con == 5 && sum.read() == nota) ||
			(con == 6 && sum.read() == (ain.read() < bin.read()))
			) {
			cout << " PASS";
		}
		else {
			cout << " FAIL";
		}
		cout << endl;
		if (zflag.read() == true) { // something like this.
			cout << "zero value" << endl;
		}
		if (oflag.read() == true && !lflag.read() == true) { // something like this.
			cout << "overflow" << endl;
		}
		if (lflag.read() == true && zflag.read() == false) {
			cout << "a less than b " << endl;
		}

	}

	SC_CTOR(check) {
		SC_METHOD(pc1);
		sensitive << clk.pos();
		dont_initialize();
	}
};
#endif
