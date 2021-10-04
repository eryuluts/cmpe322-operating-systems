/*
	 This is going to be a test program for
	 pid manager we writed for problem 3.20

Flow:
	1 - Create any number of threads.
	2 - Each thread acquires one pid.
	3 - Sleeps for a random quantity of time.
	4 - Each thread releases pid it acquired.
 */

/* pid manager api */
extern int allocate_map();
extern int allocate_pid();
extern void release_pid(int pid);

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define NUMBER_THREADS 100

void *task_func(void *args)
{
	int pid = allocate_pid();
	int time = 1 + (float)random()/RAND_MAX * 10;

	printf("Acquired PID: %d for %d s\n", pid, time);
	sleep(time);

	release_pid(pid);
	printf("Released PID: %d\n", pid);
}

int main()
{
	if(allocate_map() == -1)
	{
		perror("Failed to initialize PID table");
		return -1;
	}

	pthread_t tid[NUMBER_THREADS]; // workers
	pthread_attr_t attr; /* set of thread attributes */

	/* set the default attributes of the thread */
	pthread_attr_init(&attr);

	/* create workers */
	for(int i = 0; i < NUMBER_THREADS; i++)
	{
		pthread_create(&tid[i], &attr, task_func, 0);
	}

	/* wait for workers */
	for (int i = 0; i < NUMBER_THREADS; i++)
	{
		pthread_join(tid[i], NULL);
	}

	puts("All threads exited.");
}
