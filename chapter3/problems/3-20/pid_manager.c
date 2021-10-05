/*
	 We are going to write a pid manager.
	 We can use a bitmap to represent availibility
	 of a pid value.

	 bitmap[x] represents pid (300 + x)
		0: available
		1: in-use

	API:
	int allocate_map();
	Create and initialize data structure for representing
	pids. Return values: 1 on success, -1 on unsuccesful

	int allocate_pid();
	Allocate and return a pid value. -1 if all in use.

	void release_pid(int pid);
	Release pid value.
 */
#include <limits.h>

#define MIN_PID 300
#define MAX_PID 5000


int allocate_map();
int allocate_pid();
void release_pid(int pid);

/*
	I am going to use a bitmap to represent availibility
	of pid values.
 */

static unsigned char\
	pid_table[(MAX_PID - MIN_PID) / 8 + 1];

int allocate_map()
{
	return 1;
}

int allocate_pid()
{
	for(int i = MIN_PID; i <= MAX_PID; i++)
	{
		int byte_index = (i - MIN_PID) / 8;
		int bit_index = i - MIN_PID - byte_index * CHAR_BIT;
		unsigned char val = pid_table[byte_index];

		if(!(val & (1 << bit_index)))
		{
			val |= (1 << bit_index);
			pid_table[byte_index] = val;
			return i;
		}
	}
}

void release_pid(int pid)
{
	int byte_index = (pid - MIN_PID) / 8;
	int bit_index = pid - MIN_PID - byte_index * 8;
	pid_table[byte_index] &= ~(1 << bit_index);
}
