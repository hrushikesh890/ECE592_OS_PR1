#include <xinu.h>
void dummy()
{
	kprintf("dummy\n");
}

syscall print_ready_list()
{
        qid16 head, tail;
        //resume(create(dummy, 8192, 10, "dummy1", 1));
	//resume(create(dummy, 8192, 11, "dummy2", 1));
        head = firstid(readylist);
        tail = lastid(readylist);
	//kprintf("Head = %d tail %d %d\n", head, tail, readylist);
	//kprintf("%d %d\n", head, queuetab[head].qkey);
	kprintf("============PRINTING READY LIST==================\n");
        while (head != tail)
        {
                kprintf("(%d %d)->", head, queuetab[head].qkey);
                head = queuetab[head].qnext;
        }
	kprintf("(%d %d)\n ========================================", head, queuetab[tail].qkey);
}
                
