/*
	 We are going to use Monte Carlo technique for
	 estimating value of pi by utilizing multithreading.

	 We are creating random points in a 2x2 square
	 and we assume that we have circle in that square
	 with a radius of 1.

	 We are going to estimate value of pi by using
	 following formula.
	 pi = 4 * #points in circle / #points in square

	 Create a worker thread to create a numbers of
	 random points in our square. This thread is going to
	 count the number of points occured in circle and
	 store the result in a global value. When this thread
	 exit parent is going to estimate the value of pi
	 according to our formula.

	 In this version instead of creating threads ourselves
	 we are going to use implicit threading techniques
	 to parallelize our program flow.
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int CreatePoint();

int main(int argc, void *argv[])
{
	if (argc != 2)
	{
		puts("Input the numbers of dots.");
		return -1;
	}
	int number_of_points = atoi(argv[1]);
	int dots_in_circle = 0;

	#pragma omp parallel for reduction(+:dots_in_circle)
	for (int i = 0; i < number_of_points; i++)
	{
		if(CreatePoint())
		{
			dots_in_circle++;
		}
	}

	printf("Estimated value of pi: %.4f\n",
			4.0*dots_in_circle/number_of_points);
}

float RandomfInRange(int lower, int upper)
{
	float number =\
		((float)random())/RAND_MAX * (upper - lower);
	return lower + number;
}

/*
	 Thread task
	 Center of circle (0,0)
	 radius of circle 1

	 Vertices of square (-1,1), (1,1), (-1,-1), (1,-1)
 */
int CreatePoint()
{
	float x, y, radius;
	x = RandomfInRange(-1, 1);
	y = RandomfInRange(-1, 1);
	radius = sqrtf(x*x + y*y);
	if (radius <= 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

