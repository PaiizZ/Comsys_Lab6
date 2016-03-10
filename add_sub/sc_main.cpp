//------------------------------------------------------------------
// Simple Testbench for 4-bits adder file
//
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------

#include <systemc.h>

#include "adder.h"
#include "stim.h"
#include "check.h"

int sc_main(int argc, char* argv[])
{
    sc_signal<sc_uint<4> > ain, bin, sum;
    sc_signal<bool> ci,co;
    sc_signal<bool> zflag,oflag,lflag;
    sc_signal<bool> as ;
    sc_clock clk("clk",10,SC_NS,0.5);   // Create a clock signal


    sc_trace_file *fp;
    fp=sc_create_vcd_trace_file("add_sub_wave");
    fp->set_time_unit(1, SC_PS);
    sc_trace(fp,ain,"ain");
    sc_trace(fp,bin,"bin");
    sc_trace(fp,sum,"sum");
    sc_trace(fp,ci,"ci");
    sc_trace(fp,co,"co");
    sc_trace(fp,zflag,"zflag");
    sc_trace(fp,oflag,"oflag");
    sc_trace(fp,lflag,"lflag");
    sc_trace(fp,clk,"clk");


    add_sub DUT("add_sub");                 // Instantiate Device Under Test
    DUT.ain(ain);                       // Connect ports
    DUT.bin(bin);
    DUT.ci(ci);
    DUT.sum(sum);
    DUT.oflag(oflag);
    DUT.zflag(zflag);
    DUT.co(co);
    DUT.as(as);
    DUT.lflag(lflag);

    stim STIM("stimulus");              // Instantiate stimulus generator
    STIM.clk(clk);
    STIM.ain(ain);
    STIM.bin(bin);
    STIM.ci(ci);
    STIM.as(as);

    check CHECK("checker");             // Instantiate checker
    CHECK.clk(clk);
    CHECK.ain(ain);
    CHECK.bin(bin);
    CHECK.ci(ci);
    CHECK.sum(sum);
    CHECK.oflag(oflag);
    CHECK.zflag(zflag);
    CHECK.co(co);
    CHECK.as(as);
    CHECK.lflag(lflag);

    sc_start(100, SC_NS);               // Run simulation

    return 0;                           // Return OK, no errors.
}
