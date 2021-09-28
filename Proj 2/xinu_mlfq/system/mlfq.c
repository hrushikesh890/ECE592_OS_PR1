#include <stdlib.h>
#include <xinu.h>

qid16   userprocesslist;
status insert_to_user(pid32 pid, int32 key)
{
	int16	curr;			/* Runs through items in a queue*/
	int16	prev;			/* Holds previous node index	*/
	qid16	q = userprocesslist;
	if (isbadqid(q) || isbadpid(pid)) {
		return SYSERR;
	}

	curr = firstid(q);
	while (queuetab[curr].qkey >= key) {
		if ((queuetab[curr].qkey == key) && (curr > pid))
		{
			break;
		}
		else
		{
			curr = queuetab[curr].qnext;
		}
	}

	/* Insert process between curr node and previous node */

	prev = queuetab[curr].qprev;	/* Get index of previous node	*/
	queuetab[pid].qnext = curr;
	queuetab[pid].qprev = prev;
	queuetab[pid].qkey = key;
	queuetab[prev].qnext = pid;
	queuetab[curr].qprev = pid;
	total_tickets += key;
	return OK;
}
void remove_user_process(pid32 pid)
{
	int16 prev;
	prev = queuetab[pid].qprev;
	queuetab[prev].qnext = queuetab[pid].qnext; 
	queuetab[queuetab[pid].qnext].qprev = prev;
	total_tickets -= queuetab[pid].qkey;
	
}