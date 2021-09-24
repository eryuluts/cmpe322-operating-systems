/*
	 Linux kernel module for listing tasks.
	 This version use list tasks linearly.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>


/* This function is called when the module is loaded. */
int simple_init(void)
{
	struct task_struct *task;
	pr_info("Loading Task List Module\n");

	for_each_process(task)
	{
		pr_info("command: [%s] pid: [%d] state: [%ld]\n",
				task->comm, task->pid, task->state);
	}

	return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void)
{
	pr_info("Removing Task List Module\n");
}

/* macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Task listing");
MODULE_AUTHOR("Eray");

