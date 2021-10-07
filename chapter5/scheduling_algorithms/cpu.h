#ifndef CPU_H
#define CPU_H
#include "scheduler.h"

/*
 * @task: The task given to the cpu to run.
 *
 */
void run(struct Task *task);

/*
 * This function returns clock ticks since first usage of cpu.
 *
 */
int clock();

#endif
