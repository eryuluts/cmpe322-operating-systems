/*
 * This file contain pseude code for a monitor implementation
 * I have three printers. I want
 */
#include <stdbool.h>
typedef struct Printer
{
  bool busy;
} Printer;

#define NUM_PRINTERS 3
Printer printers[NUM_PRINTERS];

condition x;

/* Monitor functions, all of these function are wrapped between monitor
 * mutex. Only one process can be active in a monitor at a given time.
 */
Printer *Acquire(int priority)
{
  /*
   * If there is an available printer allocate it.
   * If there isn't add process to waiting list.
   */
  
  /*
   * x is a condition implemented by a semaphore with inital value
   * NUM_PRINTERS. This condition have a list associated with it.
   * When x signalled it removes highest priority process from that list
   * and wakes it up.
   */
  x.wait(priority);

  for (int i = 0; i < NUM_PRINTERS; i++)
  {
    if (!printers[i].busy)
    {
      printers[i].busy = true;
      return &printers[i];
    }
  }
}

void *Release(Printer *printer)
{
  printer[i].busy = false;
  x.signal();
}
