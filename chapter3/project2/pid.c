#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/sched.h>

#define BUFFER_SIZE 128
#define PROC_NAME "pid"

ssize_t proc_read(struct file *file, char __user *usr_buf,
		size_t count, loff_t *pos);

ssize_t proc_write(struct file *file, const char __user *usr_buf,
		size_t count, loff_t *pos);

static int npid;

static struct file_operations proc_ops = {
	.owner = THIS_MODULE,
	.read = proc_read,
	.write = proc_write,
};

/* This function is called when the module is loaded. */
int simple_init(void)
{
	pr_info("Loading PID\n");

	// Create /proc/pid entry
	proc_create(PROC_NAME, 0666, 0, &proc_ops);

	return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void)
{
	pr_info("Removing PID\n");

	// Remove /proc/pid entry
	remove_proc_entry(PROC_NAME, 0);
}

/* This function is called each time /proc/pid is read */
ssize_t proc_read(struct file *file, char __user *usr_buf,
		size_t count, loff_t *pos)
{
	int rv = 0;
	char buffer[BUFFER_SIZE];
	static int completed = 0;
	struct task_struct *ptask;
	struct pid *ppid;

	if (completed) {
		completed = 0;
		return 0;
	}

	completed = 1;

	ppid = find_vpid(npid);
	if(!ppid)
	{
		pr_err("Invalid pid\n");
		return 1;
	}

	ptask = pid_task(ppid, PIDTYPE_PID);

	rv = sprintf(buffer, "command: [%s] pid: [%d] state: [%ld]\n",
			ptask->comm, ptask->pid, ptask->state);

	/* copies kernel space buffer to user space usr buf */
	copy_to_user(usr_buf, buffer, rv);
	return rv;
}

ssize_t proc_write(struct file *file, const char __user *usr_buf,
		size_t count, loff_t *pos)
{
	int rv = 0;
	char *k_mem;
	long result;

	/* allocate kernel memory */
	k_mem = kzalloc(count + 1, GFP_KERNEL);

	/* copies user space usr buf to kernel memory */
	copy_from_user(k_mem, usr_buf, count);

	rv = kstrtol(k_mem, 10, &result);
	if (rv)
	{
		pr_err("kstrtol");
		kfree(k_mem);
		return rv;
	}
	npid = result;


	/* return kernel memory */
	kfree(k_mem);
	return count;
}


/* macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PID Module");
MODULE_AUTHOR("Eray");

