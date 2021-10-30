#include <stdlib.h>
#include <xinu.h>

qid16   userprocesslist;
uint32	total_tickets;

void set_tickets(pid32 pid, uint32 tickets)
{
    intmask mask;
    mask = disable();
    proctab[pid].tickets = tickets;

    recompute_tickets();
    restore(mask);
}

void recompute_tickets()
{
	uint32 counter = 0;
	int16 curr, last;
	intmask mask;
	mask = disable();
	curr = firstid(userprocesslist);
	last = lastid(userprocesslist);
	//kprintf("1. curr = %d last = %d %d\n", curr, last, nonempty(userprocesslist));

	
	while ((curr != last) && (nonempty(userprocesslist)))
	{
		//kprintf("curr = %d tickets = %d\n",curr,queuetab[curr].qkey);
		counter += proctab[curr].tickets;
		queuetab[curr].qkey = proctab[curr].tickets;
		curr = queuetab[curr].qnext;	
	}
	if ((curr == last) && (nonempty(userprocesslist)))
	{
		counter += proctab[curr].tickets;
		queuetab[curr].qkey = proctab[curr].tickets;
	}
	total_tickets = counter;
	restore(mask);
}
	

status insert_to_user(pid32 pid, int32 key)
{
	int16	curr;			
	int16	prev;			
	qid16	q = userprocesslist;
	//kprintf("03. insert user process %d, key %d\n", pid, key);
	intmask mask;
	mask = disable();
	if (isbadqid(q) || isbadpid(pid)) {
		//kprintf("return with syserr %d %d qid %d QENT %d %d\n", isbadqid(q), isbadpid(pid), q, NQENT, NPROC);
		return SYSERR;
	}

	curr = firstid(q);
	//kprintf("inuser curr = %d\n", curr);
	while (queuetab[curr].qkey >= key) {
		if (curr == pid)
		{
			//kprintf("MAJOR PROBLEMSS!!\n");
		}
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
	restore(mask);
	return OK;
}

pid32 find_winner(uint32 random_num)
{
	int16	curr, last;
	uint32	counter = 0;
	qid16	q = userprocesslist;
	intmask mask;
	mask = disable();
	curr = firstid(q);
	last = lastid(q);
	if (curr == last)
	{
		remove_user_process(curr);
		//kprintf("curr = %d", curr);
		return curr;
	}
	counter = queuetab[curr].qkey;
	while (counter <= random_num)
	{
		curr = queuetab[curr].qnext;
		counter += queuetab[curr].qkey;
	}
	remove_user_process(curr);
	restore(mask);
	return curr;
}

void remove_user_process(pid32 pid)
{
	int16 prev;
	intmask mask;
	mask = disable();
	prev = queuetab[pid].qprev;
	queuetab[prev].qnext = queuetab[pid].qnext; 
	queuetab[queuetab[pid].qnext].qprev = prev;
	total_tickets -= queuetab[pid].qkey;
	restore(mask);
	//kprintf("remove_user_process, never should be called\n");
	
}

uint32 get_random_number(uint32 max)
{
	intmask mask;
	uint32 retVal = max;
	mask = disable();
	if (max != 0)
	{
		retVal = rand() % max;
		//kprintf("ZERO STILL\n");
	}
	restore(mask);
	return retVal;
}

void print_user_queue()
{
	int16 curr, last;
	curr = firstid(userprocesslist);
	last = lastid(userprocesslist);
	//kprintf("1. curr = %d last = %d %d\n", curr, last, nonempty(userprocesslist));

	
	while ((curr != last) && (nonempty(userprocesslist)))
	{
		kprintf("USER QUEUE curr = %d tickets = %d\n",curr,queuetab[curr].qkey);
		//counter += proctab[curr].tickets;
		curr = queuetab[curr].qnext;
		//kprintf("USER QUEUE curr = %d tickets = %d\n",curr,queuetab[curr].qkey);	
	}
	if ((curr == last) && (nonempty(userprocesslist)))
	{
		kprintf("USER QUEUE (%d) tickets (%d)\n", curr, queuetab[curr].qkey);
	}
	kprintf("TOTAL TICKETS = %d\n", total_tickets);
}
