#ifndef ALU
#define ALU

#include <systemc.h>

SC_MODULE(alu) {
	sc_in<sc_uint<16> > ain, bin;
	sc_signal<bool> ciS, as , coS;
	sc_signal<bool> ciA, coA;
	sc_in<sc_uint<4> > control;
	sc_out<sc_uint<16> > sum;
	sc_out<bool> zflag, oflag, lflag;
	sc_signal<bool> zflagA, oflagA, lflagA;
	sc_signal<bool> zflagB, oflagB, lflagB;
	sc_signal<sc_uint<16> > sum_add, sum_sub;
	sc_uint<16> sum_xor, sum_or, sum_nota, sum_stl, sum_and;
	sc_uint<16> sum_s, sum_f;
	sc_uint<16> XOR(sc_uint<16> ain, sc_uint<16> bin) {
		return ain ^ bin;
	}

  bool fulladder(bool a, bool b, bool cif, bool& cof) {
    bool sumr;
    sumr = (a ^ b) ^ cif;
    cof = (a & b) | ((a ^ b) & cif);
    return sumr;
  }
  void ADD__SUB(){
      oflag.write(0);
      zflag.write(0);
      sc_uint<16> inb = bin.read();
			//cout<<bin.read()<<endl;
      for (int i = 0; i < 16; i++) {
        inb[i] = inb[i] ^ as;
      }
      sc_uint<16> one;
      one[0] = as;
      bool temp0 = false;
      bool temp1 = ciS.read();
      for (int i = 0; i < 16; i++) {
        temp0 = temp1;
        sum_s[i] = fulladder(ain.read()[i], inb[i], temp0, temp1);
      }

      bool tempi0 = false;
      bool tempi1 = false;
      for (int i = 0; i < 16; i++) {
        tempi0 = tempi1;
        sum_f[i] = fulladder(sum_s[i], one[i], tempi0, tempi1);
      }


      sum_a.write(sum_f);
      coS.write(temp1);

      oflag.write(temp1);
      zflag.write(!(sum_f[0] || sum_f[1] || sum_f[2] || sum_f[3] || sum_f[4] || sum_f[5] || sum_f[6] || sum_f[7] || sum_f[8] || sum_f[9] || sum_f[10] || sum_f[11] || sum_f[12] || sum_f[13] || sum_f[14] || sum_f[15]));
      lflag.write(!temp1);

  }
	void AND(/* arguments */) {
		/* code */
		for (int i = 0; i < 16;i++)
			sum_and[i] = ain.read()[i] & bin.read()[i];
	}
	void OR(/* arguments */) {
		/* code */
		for (int i = 0; i < 16; i++)
			sum_or[i] = ain.read()[i] | bin.read()[i];
	}
	void NOTA(/* arguments */) {
		/* code */
		for (int i = 0; i < 16; i++)
			sum_nota[i] = ~ain.read()[i];
	}

	void run(/* arguments */) {
		AND();
		OR();
		NOTA();
		sum_xor =XOR(ain.read(),bin.read());
		sum_stl[0] = lflagB;
		if (control.read() == 0) {
			ADD__SUB();
		//	sum.write(sum_add);
		//	cout<<sum_add<<endl;
			lflag.write(lflagA);
			oflag.write(oflagA);
			zflag.write(zflagA);
		}
		if (control.read() == 1) {
			sum.write(sum_sub);
			lflag.write(lflagB);
			oflag.write(oflagB);
			zflag.write(zflagB);
		}
		if (control.read() == 2) {
			sum.write(sum_xor);
		}
		if (control.read() == 3) {
			sum.write(sum_and);
		}
		if (control.read() == 4) {
			sum.write(sum_or);
		}
		if (control.read() == 5) {
			sum.write(sum_nota);
		}
		if (control.read() == 6) {
			sum.write(sum_stl);
			lflag.write(lflagB);
		}
	}

	SC_CTOR(alu){

		SC_METHOD(run);
		sensitive << control << ain << bin ;
	}



};

#endif
