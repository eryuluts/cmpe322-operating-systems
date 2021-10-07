#include "cpu.h"

void run(struct Task *task)
{
  if (task->burst)
  {
    task->burst--;
  }
}


int clock()
{
  static int tick;
  return tick++;
}
