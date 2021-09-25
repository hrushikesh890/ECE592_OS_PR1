#include <xinu.h>

syscall print_ready_list()
{
        qid16 head, tail;
        
        head = firstid(readylist);
        tail = lastid(readylist);
        while (queuetab[head] != queuetab[tail])
        {
                kprintf("%d %d\n", head, queuetab[head].qkey);
                head = queuetab[head].qnext;
        }
}
                
