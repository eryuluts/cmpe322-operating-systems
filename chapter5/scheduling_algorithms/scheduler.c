#include "scheduler.h"
#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>

struct Task *SelectNextFcfs(struct ListHead *head);
struct Task *SelectNextSjf(struct ListHead *head);
struct Task *SelectNextPriority(struct ListHead *head);
struct Task *SelectNextRr(struct ListHead *head);
struct Task *SelectNextRrPriority(struct ListHead *head);

struct Task *PickNextTask(struct ListHead *head, enum Algorithm nalgorithm);

void Schedule(struct ListHead *head, enum Algorithm nalgorithm)
{
  struct Task *task;
  puts("------Execution Starting-------");
  while(1)
  {
    task = PickNextTask(head, nalgorithm);
    if (task)
    {
      if (task->burst)
      {
//        printf("RUN: task name %s priority %d burst %d\n",
//              task->task_name, task->priority, task->burst);
        run(task);
      }

      if (!task->burst)
      {
        printf("Execution of task: %s finished\n", task->task_name);
        ListDel(&task->head); 
        free(task);  // ListDel only deletes element from queue 
      }
    }
    else
    {
      puts("All tasks in ready queue are terminated");
      break;
    }
  }
}


/*
 * @nalgorihm: index of scheduling algorithm
 * @head: head of read queue
 */
struct Task *PickNextTask(struct ListHead *head, enum Algorithm nalgorithm)
{
  switch (nalgorithm)
    {
      case FCFS:
      {
        return SelectNextFcfs(head);
      } break;
      case SJF:
      {
        return SelectNextSjf(head);
      } break;
      case PRIORITY:
      {
        return SelectNextPriority(head);
      } break;
      case RR:
      {
        return SelectNextRr(head);
      } break;
      case RR_PRIORITY:
      {
        return SelectNextRrPriority(head);
      } break;
      default:
      {
        fputs("error: Undefined algorithm index: PickNextTask()", stderr);
        exit(1);
      }
    }
}

/*
 * @head: pointer to head of ready queue
 * First Comes First Served scheduling algorithm implementation.
 */
struct Task *SelectNextFcfs(struct ListHead *head)
{
  if (head->next == head)
  {
    /* circular list is empty */
    return NULL;
  }
  else if(!head->next)
  {
    fprintf(stderr, "error: corrupted circular list\n");
    exit(1);
  }

  struct Task *task = LIST_ENTRY(head->next, struct Task, head);
  return task;
}

/*
 * @head: pointer to head of ready queue
 * Shortest Job First scheduling algorithm implementation.
 */
struct Task *SelectNextSjf(struct ListHead *head)
{
  if (head->next == head)
  {
    /* circular list is empty */
    return NULL;
  }
  else if(!head->next)
  {
    fprintf(stderr, "error: corrupted circular list\n");
    exit(1);
  }

  struct Task *shortest_task = 0;
  for (struct ListHead *cur = head->next; cur != head;
        cur = cur->next)
  {
    struct Task *task = LIST_ENTRY(cur, struct Task, head);
    if (!shortest_task)
    {
      shortest_task = task;
    }
    else
    {
      int condition = task->burst < shortest_task->burst;
      if (condition)
      {
        shortest_task = task;
      }
    }
  }
  return shortest_task;
}

// NOTE(Eray): Review chapter
/*
 * @head: pointer to head of ready queue
 * Priority based scheduling algorithm implementation.
 */
struct Task *SelectNextPriority(struct ListHead *head)
{
  if (head->next == head)
  {
    /* circular list is empty */
    return NULL;
  }

  struct Task *important_task= 0;
  for (struct ListHead *cur = head->next; cur != head;
        cur = cur->next)
  {
    if (!cur)
    {
      fprintf(stderr, "error: corrupted circular list\n");
      exit(1);
    }

    struct Task *task = LIST_ENTRY(cur, struct Task, head);
    if (!important_task)
    {
      important_task = task;
    }
    else
    {
      int condition = task->priority > important_task->priority;
      if (condition)
      {
        important_task = task;
      }
    }
  }
  return important_task;
}

/*
 * @head: pointer to head of ready queue
 * Round Robin scheduling algorithm implementation.
 */
struct Task *SelectNextRr(struct ListHead *head)
{
  static struct ListHead *cur;
  if (head->next == head)
  {
    /* circular list is empty */
    cur = NULL; /* reset cur since we finished traversin over list */
    return NULL;
  }

  if (!cur)
  {
    cur = head->next;
    if (!cur)
    {
      fprintf(stderr, "error: corrupted circular list\n");
      exit(1);
    }
  }
  else if (!cur->next)
  {
    fprintf(stderr, "error: corrupted circular list\n");
    exit(1);
  }

  static int count_down = TIME_QUANTUM;
  struct Task *task = LIST_ENTRY(cur, struct Task, head);
  if (count_down--)
  {
    /*
     * I expect that a task with 1 ms burst left is going to
     * terminated next cycle of CPU. So we need to get info
     * it contains before we pass it to outside. Because terminated
     * tasks can be deleted.
     */
    if (task->burst > 1)
    {
      return task;
    }
    else
    {
      count_down = TIME_QUANTUM;
      if (cur->next == head)
      {
        cur = head->next;
      }
      else
      {
        cur = cur->next;
      }
      /*
       * Clearing ready queue is not a duty of "selection from read
       * queue" process. That is why I'm returning a task with
       * 0 burst left as a candidate to execute. I expect scheduler to
       *   clear this task from ready queue after I return.
       */
      return task;  
    }
  }
  else
  {
    count_down = TIME_QUANTUM - 1; // Need to count this cycle too
    if (cur->next == head)
    {
      cur = head->next;
    }
    else
    {
      cur = cur->next;
    }
    task = LIST_ENTRY(cur, struct Task, head);
    return task;
  }
}

/*
 * @head: pointer to head of ready queue
 * Round Robin  + Priority scheduling algorithm implementation.
 * We are going to schedule task in order of priority and
 * we are going to use round-robin scheduling between tasks with
 * same priority.
 */
struct Task *SelectNextRrPriority(struct ListHead *head)
{
  static struct ListHead *cur;
  if (head->next == head)
  {
    /* circular list is empty */
    cur = NULL; /* reset cur since we finished traversin over list */
    return NULL;
  }

  if (!cur)
  {
    struct Task *important_task= 0;
    for (struct ListHead *cur = head->next; cur != head;
        cur = cur->next)
    {
      if (!cur)
      {
        fprintf(stderr, "error: corrupted circular list\n");
        exit(1);
      }

      struct Task *task = LIST_ENTRY(cur, struct Task, head);
      if (!important_task)
      {
        important_task = task;
      }
      else
      {
        int condition = task->priority > important_task->priority;
        if (condition)
        {
          important_task = task;
        }
      }
    }
    cur = &important_task->head;
  }

  static int count_down = TIME_QUANTUM;
  struct Task *task = LIST_ENTRY(cur, struct Task, head);
  if (count_down--)
  {
    /*
     * I expect that a task with 1 ms burst left is going to
     * terminated next cycle of CPU. So we need to get info
     * it contains before we pass it to outside. Because terminated
     * tasks can be deleted.
     */
    if (task->burst > 1)
    {
      return task;
    }
    else
    {
      count_down = TIME_QUANTUM;
      {
        struct Task *important_task = 0;
        struct ListHead *current = cur;
        for (struct ListHead *cur = head->next; cur != head;
            cur = cur->next)
        {
          if (cur == current)
          {
            continue;
          }

          if (!cur)
          {
            fprintf(stderr, "error: corrupted circular list\n");
            exit(1);
          }

          struct Task *task = LIST_ENTRY(cur, struct Task, head);
          if (!important_task)
          {
            important_task = task;
          }
          else
          {
            int condition = task->priority > important_task->priority;
            if (condition)
            {
              important_task = task;
            }
          }
        }
        cur = &important_task->head;
        /*
         * Clearing ready queue is not a duty of "selection from read
         * queue" process. That is why I'm returning a task with
         * 0 burst left as a candidate to execute. I expect scheduler to
         * clear this task from ready queue after I return.
         * A task with 1 burst left is returned for last execution.
         */
        return task;  
      }
    }
  }
  else
  {
    count_down = TIME_QUANTUM - 1; // Need to count this cycle too
      {
        struct Task *important_task = task;
        for (struct ListHead *cursor = cur->next; cursor != cur;
            cursor = cursor->next)
        {
          if (cursor == head)
          {
            continue;
          }

          if (!cursor)
          {
            fprintf(stderr, "error: corrupted circular list\n");
            exit(1);
          }

          struct Task *task = LIST_ENTRY(cursor, struct Task, head);
          int condition = task->priority >= important_task->priority;
          if (condition)
          {
            important_task = task;
            break;
          }
        }
        cur = &important_task->head;
      }
    task = LIST_ENTRY(cur, struct Task, head);
    return task;
  }
}
