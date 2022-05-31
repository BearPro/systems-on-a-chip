#include <iostream>
#include "systemc.h"
#include "Counter74190.h"
#include "counter_traces.h"

int sc_main(int argc, char* argv[])
{
    //ClockNotAllowed run1;
    //run1.Run();

    CountUpThenDown run2;
    run2.Run();

    return 0;
}
