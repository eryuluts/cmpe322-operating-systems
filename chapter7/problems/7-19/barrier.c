/*
 * Implementation of a synchronization tool called barrier. When a
 * thread reaches to a barrier it cannot proceed untill all other
 * threads reach to this barrier too.
 *
 * I can create x number of mutexes and when last thread reaches I can
 * make it release all those mutexes.
 *
 * I can create one semaphore and give it value 0. When last thread
 * reaches I can increase value of x times;
 */
#include <semaphore.h>
#include <pthread.h>

int number_of_threads, waiting_threads;

sem_t sem;
pthread_mutex_t mutex;

int Init(int nthreads)
{
  number_of_threads = nthreads;
  pthread_mutex_init(&mutex, NULL);
  sem_init(&sem, 0, 0); /* create and init semaphore to 0 */
  return 0;
}

/*
 * If there is x number of threads waiting, release all threads.
 */
int BarrierPoint()
{
  pthread_mutex_lock(&mutex);
  waiting_threads++; /* data race */
  if (waiting_threads == number_of_threads)
  {
    for (int i = 0; i < number_of_threads - 1; i++)
    {
      sem_post(&sem);
    }
    waiting_threads = 0;
    pthread_mutex_unlock(&mutex);
  }
  else
  {
    pthread_mutex_unlock(&mutex);
    sem_wait(&sem);
  }
  return 0;
}
