#pragma once
#include "Counter74190.h"
#include <iostream>
#include "systemc.h"

class RunBase
{
protected:
    sc_signal<bool> allow_clock;
    sc_signal<bool> clock;
    sc_signal<bool> count_down;
    sc_signal<bool> load;
    sc_signal<sc_uint<4>> data_in;

    sc_signal<bool> minmax;
    sc_signal<sc_uint<4>> out;
    sc_signal<bool> rc;

    Counter74190 counter = Counter74190("74190");
    
    sc_trace_file* trace_file;
    const char* file_name;

    RunBase(const char* file_name)
    {
        this->file_name = file_name;
        cout << "Starting simulation '" << file_name << "'." << endl;

        // Set input signals to zero before start
        allow_clock = 0;
        clock = 0;
        count_down = 0;
        load = 0;
        data_in = 0;

        // Connect signals to counter ports
        counter.ce(allow_clock);
        counter.clock(clock);
        counter.count_down(count_down);
        counter.load(load);
        counter.P(data_in);

        counter.m(minmax);
        counter.Q(out);
        counter.rc(rc);

        // Open trace file
        trace_file = sc_create_vcd_trace_file(file_name);
        trace_file->set_time_unit(0.1, SC_NS);

        // Set tracing signals
        sc_trace(trace_file, allow_clock, "allow_clock");
        sc_trace(trace_file, clock, "clock");
        sc_trace(trace_file, count_down, "count_down");
        sc_trace(trace_file, load, "load");
        sc_trace(trace_file, data_in, "data_in");

        sc_trace(trace_file, minmax, "minmax");
        sc_trace(trace_file, out, "out");
        sc_trace(trace_file, rc, "rc");

        // Pass 2ns
        sc_start(2, SC_NS);
    }

    ~RunBase()
    {
        sc_close_vcd_trace_file(trace_file);
        cout << "Simulation '" << file_name << "' completed." << endl;
    }
};