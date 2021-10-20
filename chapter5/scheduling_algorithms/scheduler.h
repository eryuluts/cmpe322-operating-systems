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
  uint32_t pid;
  char task_name[NAME_LENGTH + 1];  // Task name
  uint8_t priority;                 // An integer from [1, 10]
  uint32_t burst_init;              // Initial burst time for monitoring
  uint32_t burst;                   // ms
  struct ListHead head;
  uint32_t turn_around;    // time passed between submission and termination
  uint32_t wait_time;     // time passed while waiting in ready_queue
  uint32_t response_time; // time passed between sumission and first execution
};

#endif
