#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/sched.h>

void DFS_print(struct task_struct *task){
	struct list_head *l;
	struct task_struct *tp;
	
	list_for_each(l, &(task->children)){
		tp = list_entry(l, struct task_struct, sibling);
		printk(KERN_INFO "task pid: %i\n", tp->pid);
		DFS_print(tp);
	}
}


/* This function is called when the module is loaded. */
int simple_init(void)
{
       printk(KERN_INFO "Loading Module\n");
	DFS_print(&init_task);

       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
	
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
