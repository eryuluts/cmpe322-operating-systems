#include "buffer.h"
#include <windows.h>
#include <stdio.h>


BufferItem buffer[BUFFER_SIZE];

/*
 * in points to next empty slot in buffer and out points to first full
 * slot in buffer.
 */
int in, out;
HANDLE mutex, sem_empty, sem_full;

int InitBuffer()
{
  /* initialize lock for access to buffer */
  mutex = CreateMutex
    (
     NULL, /* security attributes */
     FALSE, /* is creating thread inital holder */
     NULL /* mutex name */
    );
  if (!mutex)
  {
    fputs("Error: CreatingMutex", stderr);
    exit(EXIT_FAILURE);
  }

  /* initalize semaphores for empty and full slots */
  sem_empty = CreateSemaphore
    (
     NULL, /* security attribute */
     BUFFER_SIZE, /* initial value */
     BUFFER_SIZE, /* maximum value */
     NULL /* security attribute */
    );
  if (!sem_empty)
  {
    fputs("Error: CreatingSemaphore", stderr);
    exit(EXIT_FAILURE);
  }

  sem_full = CreateSemaphore
    (
     NULL, /* security attribute */
     0, /* initial value */
     BUFFER_SIZE, /* maximum value */
     NULL /* security attribute */
    );
  if (!sem_full)
  {
    fputs("Error: CreatingSemaphore", stderr);
    exit(EXIT_FAILURE);
  }
}

int InsertItem(BufferItem buffer_item)
{
  /* acquire lock */
  WaitForSingleObject(mutex, INFINITE);
  /* wait for empty slot */
  WaitForSingleObject(sem_empty, INFINITE);

  buffer[in] = buffer_item;
  in = in + 1 % BUFFER_SIZE;
  
  /* signal full */
  ReleaseSemaphore(sem_full, 1, NULL);
  /* release lock */
  ReleaseMutex(mutex);
}

int RemoveItem(BufferItem *pbuffer_item)
{
  /* acquire lock */
  WaitForSingleObject(mutex, INFINITE);
  /* wait for full slot */
  WaitForSingleObject(sem_full, INFINITE);

  *pbuffer_item = buffer[out];
  out = out + 1 % BUFFER_SIZE;

  /* signal empty */
  ReleaseSemaphore(sem_empty, 1, NULL);
  /* release lock */
  ReleaseMutex(mutex);
}
