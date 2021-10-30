#include <stdlib.h>
#include <xinu.h>

qid16   userprocesslist;
qid16	high;
qid16	med;
qid16	low;

status insert_to_user(pid32 pid)
{
	int type = proctab[pid].ptype;

	switch (type)
	{
		case USER_P_HIGH:
			enqueue(pid, high);
			//proctab[pid].time_alloted = TIME_ALLOTMENT;
			break;
		case USER_P_MED:
			enqueue(pid, med);
			//proctab[pid].time_alloted = TIME_ALLOTMENT;
			break;
		case USER_P_LOW:
			enqueue(pid, low);
			//proctab[pid].time_alloted = TIME_ALLOTMENT;
			break;
		default:
			break;
	}
	return OK;
}
/*
void remove_user_process(pid32 pid)
{
	int16 prev;
	prev = queuetab[pid].qprev;
	queuetab[prev].qnext = queuetab[pid].qnext; 
	queuetab[queuetab[pid].qnext].qprev = prev;
	total_tickets -= queuetab[pid].qkey;
	
}*/

int get_time_slice(int type)
{
	int retVal = QUANTUM;
	switch (type)
	{
		
		case USER_P_HIGH:
			retVal = QUANTUM;
			break;
		case USER_P_MED:
			retVal = 2*QUANTUM;
			break;
		case USER_P_LOW:
			retVal = 4*QUANTUM;
			break;
		case SYSTEM_P:
			retVal = QUANTUM;
		default:
			break;
	}
	return retVal;
}

void priority_boost()
{
	pid32 deqpid;
	//kprintf("=================PRIORITY BOOST==========================");	
	while((!isbadqid(med)) && nonempty(med))
	{
		deqpid = dequeue(med);
		enqueue(deqpid, high);
		proctab[deqpid].ptype = USER_P_HIGH;
	}

	while((!isbadqid(low)) && nonempty(low))
	{
		deqpid = dequeue(low);
		enqueue(deqpid, high);
		proctab[deqpid].ptype = USER_P_HIGH;
	}
	reset_allotment();
}

void reset_allotment()
{
	int i;

	for (i = 0; i < NPROC; i++)
	{
		proctab[i].time_alloted = 0;
		if (proctab[i].ptype != SYSTEM_P)
		{
			proctab[i].ptype = USER_P_HIGH;
		}
	}
}

