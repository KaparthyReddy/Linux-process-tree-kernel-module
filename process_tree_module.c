#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/task.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("kaparthy");
MODULE_DESCRIPTION("Kernel module to list parent and child processes in a tree structure with memory segment details");
MODULE_VERSION("1.0");

static void print_process_tree(struct task_struct *process, int depth)
{
    struct task_struct *child_process;
    struct list_head *child_list;
    char spaces[64] = {0};
    unsigned long code_start = 0, code_end = 0;

    memset(spaces, ' ', depth * 4);

    if (process->mm) {
        code_start = process->mm->start_code;
        code_end = process->mm->end_code;
    }

    printk(KERN_INFO "%sProcess: PID=%d, Name=%s, Memory Segment: [%lx - %lx]\n",
           spaces, process->pid, process->comm, code_start, code_end);

    list_for_each(child_list, &process->children) {
        child_process = list_entry(child_list, struct task_struct, sibling);
        print_process_tree(child_process, depth + 1);
    }
}

static void list_root_process(void)
{
    struct task_struct *process;

    for_each_process(process) {
        if (process->pid == 1) {
            print_process_tree(process, 0);
        }
    }
}

static int __init process_list_init(void)
{
    printk(KERN_INFO "Loading process tree module...\n");
    list_root_process();
    return 0;
}

static void __exit process_list_exit(void)
{
    printk(KERN_INFO "Unloading process tree module...\n");
}

module_init(process_list_init);
module_exit(process_list_exit);
