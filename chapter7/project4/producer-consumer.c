/*
 * Buffer implemented as array of buffer items.
 * It's going to be manipulated as a circular queue.
 * Buffer is going to be manipulated by two functions:
 * InsertItem(); RemoveItem();
 *
 * Buffer also going to have a initialization function that initializes
 * a mutex and semaphores empty and full.
 *
 * Main function:
 * Initalize buffer
 * create producer and consumer threads
 * sleep for a period
 * terminate program.
 *
 *
 * Main function is going to be passed three arguments
 * duration of sleep
 * #producer threads
 * #consumer threads
 *
 * I'm going to use Windows API for this project. Because I want to
 * learn about it too.
 */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "buffer.h"

int RandomIntegerInRange(int lower, int upper)
{
  int number = ((float)random())/RAND_MAX * (upper - lower);
  return lower + number;
}

#define LOOP_SLEEP_SECONDS 1
/*
 * I'm handling synchronization inside buffer library. Thus I can access
 * methods to buffer without thinking about synchronization.
 */
DWORD WINAPI Producer(LPVOID param)
{
  while(true)
  {
    /* sleep for a while */
    Sleep(LOOP_SLEEP_SECONDS * 1000);
    /* produce random number */
    BufferItem rand = RandomIntegerInRange(0, 100);
    InsertItem(rand);
    printf("Inserted Item: %d\n", rand);
  }
}

DWORD WINAPI Consumer(LPVOID param)
{
  BufferItem *pitem;
  while(true)
  {
    /* sleep for a while */
    Sleep(LOOP_SLEEP_SECONDS * 1000);
    /* remove to buffer */
    RemoveItem(pitem);
    printf("Removed Item: %d\n", *pitem);
  }
}


#define USAGE "Usage: [PROGRAM NAME]"\
              "[SLEEP SECONDS] [#PRODUCER_THREADS] [#CONSUMER_THREADS]"
int main(int argc, char *argv[])
{
  int sleep_seconds, nproducers, nconsumers;
  if (argc != 4)
  {
    puts(USAGE);
    exit(EXIT_FAILURE);
  }

  sleep_seconds = atoi[1];
  nproducers = atoi[2];
  nconsumers = atoi[3];

  /* initialize buffer */
  InitBuffer();

  /* create producer and consumer threads */
  HANDLE producers[nproducers];
  HANDLE consumer[nconsumers];

  for (int i = 0; i < nproducers; i++)
  {
    HANDLE hthread = CreateThread(
        NULL, /* default security attributes */
        0, /* default stack size */
        Producer, /* thread function */
        0, /* parameter to thread function */
        0, /* default creation flags */
        0
        ); /* returns the thread identifier */

    if (!hthread)
    {
      perror("Thread Creation");
      return -1;
    }
    else
    {
      producer[i] = hthread;
    }
  }

  for (int i = 0; i < nconsumers; i++)
  {
    HANDLE hthread = CreateThread(
        NULL, /* default security attributes */
        0, /* default stack size */
        Consumer, /* thread function */
        0, /* parameter to thread function */
        0, /* default creation flags */
        0
        ); /* returns the thread identifier */

    if (!hthread)
    {
      perror("Thread Creation");
      return -1;
    }
    else
    {
      consumer[i] = hthread;
    }
  }

  Sleep(sleep_seconds * 1000);
}


