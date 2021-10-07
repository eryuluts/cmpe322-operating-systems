# Information
For this project We are going to implement
following scheduling algorithms.

- First Comes First Served (FCFS), which schedules
tasks in the order in which they request the CPU.
- Shortest-job-first (SJF), which schedules tasks
in order of the length of the task's next CPU burst.
- Priority scheduling, which schedules tasks based
on priority.
- Round-robin (RR) scheduling, where each task is
run for a time quantum (or for the remainder of its
CPU burst).
- Priority with round-robin, which schedules tasks
in order of priority and uses round-robin scheduling
for tasks with equal priority.

Priorities {1 ... 10}  
Time Quantum for RR is 10 ms


Schedule of task has the format [task name], [priority], [CPU burst]  
T1, 4, 20  
T2, 2, 25  
T3, 3, 25  
T4, 3, 15  
T5, 10, 10  
It's assumed that all task arrive at same time.


# Architecture  
## CPU module:  
    void run(struct task *task);  
Run given task. In this context running a task means decreasing that
task's  CPU burst time.  

## Driver module:  
    struct task  
    {  
        char task_name[10]; // Task name  
        uint8 priority;     // An integer from [1, 10]  
        uint32 burst;       // ms  
    }  
ready\_queue (circular doubly linked list)  

    void schedule();  
This function invokes scheduler. Scheduler executes each task in the
list according to selected scheduling algorithm. Scheduler needs to
know which list associated with which cpu. It's schedulers duty to
link queues with CPUs.

The selection process is carried out by the CPU scheduler, which selects
a process from the processes in memory that are ready to execute and
allocates the CPU to that process.

CPU-scheduling decisions may take place under the following four
circumstances:

1. When a process switches from the running state to the waiting state
   (for example, as the result of an I/O request or an invocation of
   wait() for the termination of a child process)
2. When a process switches from the running state to the ready state
   (for example, when an interrupt occurs)
3. When a process switches from the waiting state to the ready state
   (for example, at completion of I/O)
4. When a process terminates

    pick\_next\_task(task\_list);  
Used to select task to run from read\_queue.

Sheduler defined as the part of operating system that selects task
to run from ready queue and allocates CPU to that selected task.
Dispatcher is the module that gives the control of CPU to task selected
by scheduler.


We are going to write a make file. We are going to have a different
built version of driver for each scheduling algorithm.  

    make fcfs  
Builts driver for that drives scheduler in fcfs mode.

