#pragma once
#include "RunBase.h"

class ClockNotAllowed : public RunBase
{
public:
	ClockNotAllowed() : RunBase("ClockNotAllowed") { }
	
	void Run()
	{
		for (size_t i = 0; i < 10; i++)
		{
			Start();
			clock = false;
			Start();
			clock = true;
		}
	}
};

class CountUpThenDown : public RunBase
{
public:
	CountUpThenDown() : RunBase("CountUpThenDown") { }

	void Run()
	{
		allow_clock = true;
		
		for (size_t i = 0; i < 20; i++)
		{
			Start();
			clock = false;
			Start();
			clock = true;
		}

		allow_clock = false;
		clock = false;
		
		Start();
		Start();

		allow_clock = true;
		count_down = true;

		for (size_t i = 0; i < 20; i++)
		{
			Start();
			clock = false;
			Start();
			clock = true;
		}
	}
};