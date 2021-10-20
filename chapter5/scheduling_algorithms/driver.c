/*
 * Implementation of scheduler driver.
 * Contains entry point and parser.
 */
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "scheduler.h"
#include "list.h"
#include <stdarg.h>

/* For atomic increment in Windows API */
#include <Windows.h>

#define LINE_SIZE 1024

void ErrorExit(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  fprintf(stderr, "error: ");
  vfprintf(stderr, fmt, ap);
  fputc('\n', stderr);
  va_end(ap);
  exit(EXIT_FAILURE);
}

#define TO_STR(s) #s
#define FORMAT_STR(count)\
  " %" TO_STR(count) "[a-zA-Z0-9], %" SCNu8 ", %" SCNu32

int pid = 1;

/*
 * First we need to parse file that contains information about tasks and
 * store that information in task objects.
 *
 * 1- Read a line into buffer from file
 * 2- Convert string in buffer to sequence of tokens
 * 3- Parse these tokens into an entry
 * 4- Calculate values of tokens that entry constructed from
 * 5- Store those values in corresponding fields in task structures
 *
 * entry: [name] [priority] [burst]
 *
 */
struct ListHead *parse_task_file(const char *filename)
{
  FILE *fp = fopen(filename, "r");
  if (!fp)
  {
    ErrorExit("Can't open file: %s", filename); 
  }


  /* Dummy head makes looping easier. */
  struct ListHead *list_head = malloc(sizeof(struct ListHead));
  InitListHead(list_head);
  int nline = 1;
  while (1)
  {
    char buffer[LINE_SIZE];
    struct Task task = {0};
    if (fgets(buffer, LINE_SIZE, fp))
    {
      int count = sscanf(buffer, FORMAT_STR(NAME_LENGTH),
          task.task_name, &task.priority, &task.burst
          );

      if (count == 3)
      {
        /* add task structs to linked list */
        struct Task *ptask = malloc(sizeof(struct Task));
        if (!ptask)
        {
          ErrorExit("Out of memory");
        }
        *ptask = task;
        ptask->pid = pid;
        ptask->burst_init = ptask->burst;
        InterlockedIncrement(&pid);
        ListAdd(&ptask->head, list_head->prev); 
      }
      else
      {
        if (nline == 1)
        {
          ErrorExit("Schedule of tasks file is empty: %s", filename);
        }
        fprintf(stderr, "Corrupted entry: line %d: %s\n",
            nline, filename);
      }
      nline++;  // increase line count
    }
    else
    {
      if (ferror(fp))
      {
        ErrorExit("Error reading: %s", filename);
      }
      else
      {
        printf("Reached EOF: %s\n", filename);
        break;
      }
    }
  }
  return list_head;
}

/* 
 * These macro names used for making conditional build using a makefile
 */
#if defined(PP_FCFS)
#define SCH_ALG FCFS

#elif defined(PP_SJF)
#define SCH_ALG SJF

#elif defined(PP_PRIORITY)
#define SCH_ALG PRIORITY

#elif defined(PP_RR)
#define SCH_ALG RR

#elif defined(PP_PRIORITY)
#define SCH_ALG RR_PRIORITY 

#else
#define SCH_ALG FCFS
#endif

#define SCH_STR(alg) TO_STR(alg)

#define USAGE "Usage: [PROGRAM NAME] [FILE NAME]"
int main(int argc, void *argv[])
{
  if (argc != 2)
  {
    ErrorExit(USAGE);
  }
  
  struct ListHead *head = parse_task_file(argv[1]);

  puts("ready queue:");
  for (struct ListHead *cur = head->next; cur != head; cur = cur->next)
  {
    struct Task *task = LIST_ENTRY(cur, struct Task, head);
    printf("Task name: %s priority: %hhu burst: %" PRIu32 "\n",
          task->task_name, task->priority, task->burst);  
  }
  
  puts("Scheduling algorithm: " SCH_STR(SCH_ALG));
  Schedule(head, SCH_ALG);
}

