#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	/* sequential code */
	#pragma omp parallel
	{
		puts("I am a parallel region.");
	}
	/* sequential code */
	return 0;
}
