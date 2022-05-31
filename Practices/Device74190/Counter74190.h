#pragma once
#include <systemc.h>

struct Counter74190 : public sc_module
{
private:
    sc_uint<4> count = 0;

public:
    // Такт (in)
    sc_in_clk clock;
    
    // Направление счёта, если истина - вычитание (in)
    sc_in<bool> count_down;

    // Загрузка данных из информационного ввода (in)
    sc_in<bool> load;
    
    // Разрешает счёт (in)
    sc_in<bool> ce;

    // Коэффициент (информационный ввод) (in)
    sc_in<sc_uint<4>> P;

    // Показывает что счётчик достиг максимального или минимального значения (out)
    sc_out<bool> m;
    
    // Информационный вывод (out)
    sc_out<sc_uint<4>> Q;

    // wtf? (out)
    sc_out<bool> rc;

    SC_CTOR(Counter74190) :
        clock("clock"),
        count_down("count_down"),
        load("load"),
        ce("ce"),
        P("P"),
        m("m"),
        Q("Q"),
        rc("rc")
    {
        SC_METHOD(process_clock);
        
        sensitive << clock.pos();
    }

    void process_clock()
    {
        // Логика загрузки
        if (load)
        {
            count = P;
            Q.write(count);
        }

        // Логика счёта
        if (ce)
        {
            if (count_down)
            {
                if (count == 0)
                {
                    count = 10;
                }
                
                count--;
                
                if (count == 0)
                {
                    m = true;
                }
                else
                {
                    m = false;
                }
            }
            else
            {
                if (count == 9)
                {
                    count = -1;
                }

                count++;
                if (count == 9)
                {
                    m = true;
                }
                else
                {
                    m = false;
                }
            }
            
            Q.write(count);
        }

        // Логика каскадного соединения.
        if (!ce && m)
        {
            rc = true;
        }
        else if (rc)
        {
            rc = false;
        }
    }
};