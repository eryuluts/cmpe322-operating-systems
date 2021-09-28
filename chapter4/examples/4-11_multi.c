/*
	 Pthreads example figure 4.11
	 Multi thread version. Incomplete!
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10

int sum[NUM_THREADS];	// sub-sums of each thread

void *runner(void *param); /* threads call this function */

int main(int argc, char *argv[])
{
	pthread_t tid[NUM_THREADS]; // Thread identifiers
	pthread_attr_t attr; /* set of thread attributes */

	pthread_attr_init(&attr);

	/* create the threads */
	for(int i = 0; i < NUM_THREADS; i++)
	{
		tid[i] = pthread_create(&tid, &attr, runner, );
	}

	/* wait for the threads to exit */
	for(int i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(tid[i], NULL);
	}

	int overall_sum = 0;
	for(int i = 0; i < NUM_THREADS; i++)
	{
		overall_sum += sum[i];
	}

	printf("sum = %d\n", overall_sum);
}

/* The thread will execute in this function */
void *runner(void *param)
{
	int i, upper = atoi(param)

	sum = 0;
	for (i = 0; i <= upper; i++)
	{
		sum += i;
	}
	pthread_exit(0);
}
