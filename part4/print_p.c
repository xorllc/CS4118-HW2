#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/sched.h>

struct task_struct *t;
struct list_head *lh;
	
/*void dfs_print(struct list_head *list, struct task_struct task){
	list_for_each(list, &((&task)->children)){
		//t = list_entry(list, struct task_struct, sibling);
		//printk(KERN_INFO "task pid: %i\n", t->pid);
		
	}
}*/

int dummy_fun(struct list_head *l, struct task_struct tk, struct task_struct *tp){
	//this is fine	
	/*for_each_process(tp){
		printk(KERN_INFO "task pid: %i\n", tp->pid);
	}*/	

	//this generates a warning for frame size
	list_for_each(l, &((&tk)->children)){
		tp = list_entry(l, struct task_struct, sibling);
		printk(KERN_INFO "task pid: %i\n", tp->pid);
	}
	return 0;
}


/* This function is called when the module is loaded. */
int simple_init(void)
{
       printk(KERN_INFO "Loading Module\n");
	
	//linearly prints tasks; works fine
	/*for_each_process(task){
		printk(KERN_INFO "task pid: %i\n", task->pid);
	}*/

	//the following code works fine and prints task pid
	list_for_each(lh, &((&init_task)->children)){
		t = list_entry(lh, struct task_struct, sibling);
		printk(KERN_INFO "task pid: %i\n", t->pid);
	}
	
	//the dummy_fun() produces warning: frame size larger than
	dummy_fun(lh, init_task, t);
	


	//try to use a stack to do DFS
/*	while(!stack.empty){
		list_for_each(lh, &((&init_task)->children)){
			t = list_entry(lh, struct task_struct, sibling);
			addToStack(t);
			printk(KERN_INFO "task pid: %i\n", t->pid);
		}
	}*/

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
