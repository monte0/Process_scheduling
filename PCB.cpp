#include "PCB.h"
#include <cstdlib>
// TODO: Add your implementation here
//default constructor
PCB::PCB()
{
	wait_time = 0;
	turnaround_time = 0;
	name = " ";
	priority = 0;
	burst = 0;
	state = ProcState::NEW;
	ID = 0;
}
//constructor
PCB::PCB(std::string s, int pri, int bur, ProcState st, int id_num)
{
	wait_time = 0;
	turnaround_time = 0;
	name = s;
	priority = pri;
	state = st;
	burst = bur;
	ID = id_num;
}