/*
 We are going to create a program that calculates
 some statistical values in a multithreaded fashion.

 We will be given a set of numbers as input.
 We are going to create 3 different worker threads
 and each of these threads are going to calculate one
 of these values.

	worker1: average
	worker2: min value
	worker3: max value

	We are going to output these values after
	our workers have exited.
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int average, max_value, min_value;
void *calc_average(void *numbers);
void *calc_max(void *numbers);
void *calc_min(void *numbers);

int main(int argc, void *argv[])
{
	int numbers[argc];
	pthread_t tid[3]; // workers
	pthread_attr_t attr; /* set of thread attributes */

	/* set the default attributes of the thread */
	pthread_attr_init(&attr);

	if (argc < 2)
	{
		puts("no numbers given.");
		return -1;
	}

	/*
		 using first member in array to pass
		 length of array info.
	 */
	numbers[0] = argc;
	for(int i = 1; i < argc; i++)
	{
		numbers[i] = atoi(argv[i]);
	}

	/* create workers */
	pthread_create(&tid[0], &attr, calc_average, numbers);
	pthread_create(&tid[1], &attr, calc_max, numbers);
	pthread_create(&tid[2], &attr, calc_min, numbers);

	/* wait for workers */
	for (int i = 0; i < 3; i++)
	{
		pthread_join(tid[i], NULL);
	}

	printf("Average of numbers: %d\n", average);
	printf("Max of numbers: %d\n", max_value);
	printf("Min of numbers: %d\n", min_value);
}

void *calc_average(void *numbers)
{
	int *pnumbers, length;
	pnumbers = (int *) numbers;
	length = pnumbers[0];

	int sum = 0;
	for (int i = 1; i < length; i++)
	{
		sum += pnumbers[i];
	}
	average = sum/(length - 1);

}

void *calc_max(void *numbers)
{
	int *pnumbers, length;
	pnumbers = (int *) numbers;
	length = pnumbers[0];

	int max = 0;
	for (int i = 1; i < length; i++)
	{
		if (pnumbers[i] > max)
		{
			max = pnumbers[i];
		}
	}

	max_value = max;
}

void *calc_min(void *numbers)
{
	int *pnumbers, length;
	pnumbers = (int *) numbers;
	length = pnumbers[0];

	int min = pnumbers[1];
	for (int i = 2; i < length; i++)
	{
		if (pnumbers[i] < min)
		{
			min = pnumbers[i];
		}
	}

	min_value = min;
}

