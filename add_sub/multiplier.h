#ifndef MULTIPLY_H
#define MULTIPLY_H

#include <systemc.h>
#include "alu.h"
SC_MODULE(multiplier) {
	sc_in<sc_uint<16> > ain, bin;
	sc_signal<sc_uint<16> > a,q,m,aa,mm,ss;
  sc_signal<sc_uint<4> > control;
	sc_uint<16> _q, _m,_a;

	bool c;
	sc_out<sc_uint<32> > out;
	alu ALUA;
	sc_signal<bool> aci, aco, oflag, lflag, zflag;
	void p1() {

		_q = ain.read();
		_m = bin.read();
		_a = 0b0000000000000000;
		c = 0b00;
		//cout << "_M: " << _m << " " << "_Q: " << _q << " _A: " << _a << endl;

		/*q.write(ain.read());
		m.write(bin.read());*/
		/*q.write(_q);
		m.write(_m);*/
		/*
		while (true) {
			sc_start(100, SC_NS);
		}*/
		//cout << "M: " << m.read()<< " " << "Q: " << q.read() << " A: "<<ain.read()<< endl;
		for (int i = 0; i < 16; i++) {
			if (_q[0]) {
				aa = _m;
				mm = _a;
				_a = ss;
				c = oflag;
			}
			/*sc_uint<16> sq = q.read();*/
			//sq = sq >> 1;
			_q = _q >> 1;
			_q[15] = _a[0];
			/*sc_uint<16> sa = a.read();
			sa = sa >> 1;
			sq[15] = sa[0];
			sa[15] = c;
			c = false;
			q.write(sq);
			a.write(sa);*/
			_a = _a >> 1;
			_a[15] = c;
			c = false;
		}
		sc_uint<32> outi;
		for (int i = 0; i < 15; i++) {
			outi[i] = _q[i];
		}
		for (int i = 0; i < 15; i++) {
			outi[16+i] = _a[i];
		}
		out.write(outi);
	}
	SC_CTOR(multiplier): ALUA("ALU") {
		SC_METHOD(p1);
		ALUA.ain(aa);
		ALUA.bin(mm);
		//ALU.ci(aci)
		ALUA.sum(ss);
		control.write(0);
		ALUA.control(control);
		//ALU.co(aco);
		ALUA.zflag(zflag);
		ALUA.oflag(oflag);
		ALUA.lflag(lflag);

		sensitive << ain << bin << a << q << m << aa << mm << ss << out << aci << aco ;
	}
};

#endif
