/*
	 This is again an exercise for using circular
	 doubly linked list in linux kernel.

	 Collatz conjecture states that if the algorithm
	 below applied enough times starting from an
	 arbitrary positive integer we are going to reach 1
	 eventually.

	 We are going to use this to create a list.

	 if n is even
	 	n = n/2;
	 if n is odd
	 	n = B * n + 1
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/moduleparam.h>


static int start = 26, b = 2;
module_param(start, int, 0);
module_param(b, int, 0);

struct element
{
	int number;
	struct list_head list;
};

static LIST_HEAD(number_list);

/* This function is called when the module is loaded. */
int simple_init(void)
{
	struct element *element;
	int n = start, i = 0;
	pr_info("Loading Data Structures Module\n");
	pr_info("start: %d, b: %d\n", start, b);

	while(n > 1)
	{
		if (i++ > 200)
		{
			pr_err("Not enough space");
			break;
		}

		if(n % 2)
		{
			n = b * n + 1;
		}
		else
		{
			n /= 2;
		}

		element = kmalloc(sizeof(struct element), GFP_KERNEL);
		element->number = n;
		list_add_tail(&element->list, &number_list);
	}


	list_for_each_entry(element, &number_list, list)
	{
		/* On each iteration p_color points to next entry */
		pr_info("%d\n", element->number);
	}

	return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void)
{
	struct element *element, *next;
	pr_info("Removing Data Structures Module\n");
	list_for_each_entry_safe(element, next, &number_list, list)
	{
		list_del(&element->list);
		kfree(element);
	}
}

/* macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Task listing");
MODULE_AUTHOR("Eray");

