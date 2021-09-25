/*
	 In this module we are exploring circular
	 doubly linked list type defined in
	 linux kernel.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/moduleparam.h>

struct color
{
	int red, green, blue;
	struct list_head list;
};

static LIST_HEAD(color_list);

static int start = 25;
module_param(start, int, 0);

/* This function is called when the module is loaded. */
int simple_init(void)
{
	struct color *violet, *red, *green, *blue, *start_color;
	struct color *p_color;
	pr_info("Loading Data Structures Module\n");

	violet = kmalloc(sizeof(struct color), GFP_KERNEL);
	violet->red = 138;
	violet->green = 43;
	violet->blue = 226;
	list_add_tail(&violet->list, &color_list);

	red = kmalloc(sizeof(struct color), GFP_KERNEL);
	red->red = 255;
	red->green = 0;
	red->blue = 0;
	list_add_tail(&red->list, &color_list);

	green = kmalloc(sizeof(struct color), GFP_KERNEL);
	green->red = 0;
	green->green = 255;
	green->blue = 0;
	list_add_tail(&green->list, &color_list);

	blue = kmalloc(sizeof(struct color), GFP_KERNEL);
	blue->red = 0;
	blue->green = 0;
	blue->blue = 255;
	list_add_tail(&blue->list, &color_list);


	start_color = kmalloc(sizeof(struct color), GFP_KERNEL);
	start_color->red = start;
	start_color->green = start;
	start_color->blue = start;
	list_add_tail(&start_color->list, &color_list);


	list_for_each_entry(p_color, &color_list, list)
	{
		/* On each iteration p_color points to next entry */
		pr_info("Color Values: r%d, g%d, b%d\n",
				p_color->red, p_color->green, p_color->blue);
	}

	return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void)
{
	struct color *p_color, *next;
	pr_info("Removing Data Structures Module\n");
	list_for_each_entry_safe(p_color, next, &color_list, list)
	{
		list_del(&p_color->list);
		kfree(p_color);
	}
}

/* macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Task listing");
MODULE_AUTHOR("Eray");

