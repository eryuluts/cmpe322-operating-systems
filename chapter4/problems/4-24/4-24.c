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
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int dots_in_circle;
pthread_mutex_t count_lock;

void *CreatePoints(void *number_of_points);

int main(int argc, void *argv[])
{
  pthread_t tid; // workers
  pthread_attr_t attr; /* set of thread attributes */

  /* set the default attributes of the thread */
  pthread_attr_init(&attr);

  if (argc != 2)
  {
    puts("Input the numbers of dots.");
    return -1;
  }

  int number_of_points = atoi(argv[1]);
  /* create workers */
  pthread_create(&tid, &attr, CreatePoints,
      &number_of_points);

  /* wait for thread to exit*/
  pthread_join(tid, NULL);

  printf("Estimated value of pi: %.4f\n",
      4.0*dots_in_circle/number_of_points);
}

float RandomfInRange(int lower, int upper)
{
  float number = ((float)random())/RAND_MAX * (upper - lower);
  return lower + number;
}

/*
   Thread task
   Center of circle (0,0)
   radius of circle 1

   Vertices of square (-1,1), (1,1), (-1,-1), (1,-1)
 */
void *CreatePoints(void *number_of_points)
{
  /* Create a point in square */
  int count = 0;
  for(int i = 0; i < *(int *)number_of_points; i++)
  {
    float x, y, radius;
    x = RandomfInRange(-1, 1);
    y = RandomfInRange(-1, 1);
    radius = sqrtf(x*x + y*y);
    if (radius <= 1)
    {
      count++;
    }
  }

  pthread_mutex_lock(&count_lock);
  dots_in_circle = count;
  pthread_mutex_unlock(&count_lock);
}

