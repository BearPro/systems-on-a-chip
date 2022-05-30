#include <iostream>
#include "systemc.h"
#include "Counter74190.h"

int sc_main(int argc, char* argv[])
{
    sc_signal<bool> allow_clock;
    sc_signal<bool> clock;
    sc_signal<bool> count_down;
    sc_signal<bool> load;
    sc_signal<sc_uint<4>> data_in;
    
    sc_signal<bool> minmax;
    sc_signal<sc_uint<4>> out;
    sc_signal<bool> rc;

    allow_clock = 0;
    clock = 0;
    count_down = 0;
    load = 0;
    data_in = 0;

    Counter74190 counter("74190");

    counter.ce(allow_clock);
    counter.clock(clock);
    counter.count_down(count_down);
    counter.load(load);
    counter.P(data_in);
    
    counter.m(minmax);
    counter.Q(out);
    counter.rc(rc);

    sc_trace_file* trace_file = sc_create_vcd_trace_file("../../Traces/74190");
    trace_file->set_time_unit(0.1, SC_NS);

    sc_trace(trace_file, allow_clock, "allow_clock");
    sc_trace(trace_file, clock, "clock");
    sc_trace(trace_file, count_down, "count_down");
    sc_trace(trace_file, load, "load");
    sc_trace(trace_file, data_in, "data_in");

    sc_trace(trace_file, minmax, "minmax");
    sc_trace(trace_file, out, "out");
    sc_trace(trace_file, rc, "rc");

    sc_start(2, SC_NS);

    allow_clock = true;
    for (size_t i = 0; i < 20; i++)
    {
        clock = false;
        sc_start(1, SC_NS);
        clock = true;
        sc_start(1, SC_NS);
    }
    allow_clock = false;

    count_down = true;
    for (size_t i = 0; i < 32; i++)
    {
        clock = true;
        sc_start(1, SC_NS);
        clock = false;
        sc_start(1, SC_NS);
    }

    sc_close_vcd_trace_file(trace_file);

    cout << "Simulation completed." << endl;
    return 0;
}
