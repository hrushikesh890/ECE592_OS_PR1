#include <stdlib.h>
#include <xinu.h>

qid16   userprocesslist;
uint32	total_tickets;

void set_tickets(pid32 pid, uint32 tickets)
{
    proctab[pid].tickets = tickets;
}

status insert_to_user(pid32 pid, int32 key)
{
	int16	curr;			
	int16	prev;			
	qid16	q = userprocesslist;
	//kprintf("03. insert user process %d, key %d\n", pid, key);
	if (isbadqid(q) || isbadpid(pid)) {
		//kprintf("return with syserr %d %d qid %d QENT %d %d\n", isbadqid(q), isbadpid(pid), q, NQENT, NPROC);
		return SYSERR;
	}

	curr = firstid(q);
	//kprintf("inuser curr = %d\n", curr);
	while (queuetab[curr].qkey >= key) {
		//kprintf("Not exit yet\n");
		if ((queuetab[curr].qkey == key) && (curr > pid))
		{
			break;
		}
		else
		{
			curr = queuetab[curr].qnext;
		}
	}
	//kprintf("Exit\n");
	

	prev = queuetab[curr].qprev;	
	queuetab[pid].qnext = curr;
	queuetab[pid].qprev = prev;
	queuetab[pid].qkey = key;
	queuetab[prev].qnext = pid;
	queuetab[curr].qprev = pid;
	total_tickets += key;
	//kprintf("04. Total ticks = %d\n",total_tickets);
	return OK;
}

pid32 find_winner(uint32 random_num)
{
	int16	curr;
	uint32	counter = 0;
	qid16	q = userprocesslist;
	curr = firstid(q);
	//kprintf("firstid = %d\n", curr);
	counter = queuetab[curr].qkey;
	while (counter < random_num)
	{
		curr = queuetab[curr].qnext;
		counter += queuetab[curr].qkey;
	}
	remove_user_process(curr);
	return curr;
}

void remove_user_process(pid32 pid)
{
	int16 prev;
	prev = queuetab[pid].qprev;
	queuetab[prev].qnext = queuetab[pid].qnext; 
	queuetab[queuetab[pid].qnext].qprev = prev;
	total_tickets -= queuetab[pid].qkey;
	//kprintf("remove_user_process, never should be called\n");
	
}

uint32 get_random_number(uint32 max)
{
	return (rand() % max);
}


