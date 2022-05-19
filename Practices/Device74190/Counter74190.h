#pragma once
#include <systemc.h>

struct Counter74190 : public sc_module
{
    sc_in_clk clock;
    sc_in<bool> reset;
    sc_in<bool> input;
    sc_out<sc_uint<4>> out;

    sc_uint<4> count = 0;

    void process_clock()
    {
        if (reset.read())
        {
            count = 0;
            out.write(count);
        }
        else if (input.read())
        {
            count += 1;
            out.write(count);
        }
    }

    SC_CTOR(Counter74190)
    {
        SC_METHOD(process_clock);
        sensitive << reset << clock.pos();
    }
};