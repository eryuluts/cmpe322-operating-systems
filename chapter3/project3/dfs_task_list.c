/*
	 Linux kernel module for listing tasks.
	 This version of module iterates over all tasks on
	 system by using Depth-First Search(DFS) Tree.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/sched/task.h>
#include <linux/list.h>

void dfs_traverse(struct list_head *head);

/* This function is called when the module is loaded. */
int simple_init(void)
{
	pr_info("Loading Task List Module\n");
	dfs_traverse(&init_task.children);

	return 0;
}

void dfs_traverse(struct list_head *head)
{
	struct task_struct *task;
	struct list_head *list;

	if (!head)
	{
		return;
	}

	list_for_each(list, head)
	{
		task = list_entry(list, struct task_struct, sibling);
		pr_info("command: [%s] pid: [%d] state: [%ld]\n",
				task->comm, task->pid, task->state);
		dfs_traverse(&task->children);
	}
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

