#include <iostream>
#include "systemc.h"
#include "Counter74190.h"

int sc_main(int argc, char* argv[])
{
    sc_signal<bool> clock;
    sc_signal<bool> reset;
    sc_signal<bool> input;
    sc_signal<sc_uint<4>> out;

    Counter74190 counter("counter");
    counter.clock(clock);
    counter.reset(reset);
    counter.input(input);
    counter.out(out);

    sc_start();
    sc_trace_file* trace_file = sc_create_vcd_trace_file("../../Traces/74190");

    sc_trace(trace_file, clock, "clock");
    sc_trace(trace_file, reset, "reset");
    sc_trace(trace_file, input, "input");
    sc_trace(trace_file, out, "out");

    reset = false;
    clock = false;
    input = false;

    for (size_t i = 0; i < 2; i++)
    {
        clock = false;
        sc_start(10, SC_NS);
        clock = true;
        sc_start(10, SC_NS);
    }

    input = true;
    for (size_t i = 0; i < 16; i++)
    {
        if (i % 6 == 0)
        {
            reset = true;
            sc_start(10, SC_NS);
            reset = false;
            sc_start(10, SC_NS);
        }
        clock = false;
        sc_start(10, SC_NS);
        clock = true;
        sc_start(10, SC_NS);
    }

    input = false;
    reset = true;
    sc_start(10, SC_NS);

    reset = false;
    input = true;
    for (size_t i = 0; i < 16; i++)
    {
        clock = false;
        sc_start(10, SC_NS);
        clock = true;
        sc_start(10, SC_NS);
    }

    sc_close_vcd_trace_file(trace_file);
    return 0;
}
