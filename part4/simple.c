#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/sched.h>
#define MAX_TABS 20
int i;
char tabs[MAX_TABS];

void DFS_print(struct task_struct *task, int count){
	struct list_head *l;
	struct task_struct *tp;
	
	tabs[count++]='\0';	

	list_for_each(l, &(task->children)){
		tp = list_entry(l, struct task_struct, sibling);
		printk(KERN_INFO "%s\\_[%i] %s\n", tabs, tp->pid, tp->comm);
		
		tabs[count-1]=32;
		DFS_print(tp, count);
		tabs[count+1]=32;
	}
}


/* This function is called when the module is loaded. */
int simple_init(void)
{
       printk(KERN_INFO "Loading Module\n");
	
	for(i=0; i<MAX_TABS-1; i++){
		tabs[i] = 32;
	}
	tabs[MAX_TABS-1] = '\0';	
	//printk("%shi%s\n", tabs, tabs);
	
	DFS_print(&init_task, 0);

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
