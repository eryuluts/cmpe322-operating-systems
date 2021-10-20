#include "cpu.h"
int tick;

void run(struct Task *task)
{
  if (task->burst)
  {
    task->burst--;
    tick++;
  }
}


int clock()
{
  return tick;
}
