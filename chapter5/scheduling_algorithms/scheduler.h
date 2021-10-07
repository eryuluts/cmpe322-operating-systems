#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include "list.h"

/* Invoke scheduler */
void Schedule(struct ListHead *head, enum Algorithm nalgorithm);

enum Algorithm
{
  FCFS,
  SJF,
  PRIORITY,
  RR,
  RR_PRIORITY
};

#define TIME_QUANTUM 10 //ms

#define NAME_LENGTH 10
struct Task
{
  char task_name[NAME_LENGTH + 1];  // Task name
  uint8_t priority;                 // An integer from [1, 10]
  uint32_t burst;                   // ms
  struct ListHead head;
};

#endif
