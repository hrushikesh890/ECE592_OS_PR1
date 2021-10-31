#include <xinu.h>
int num_pi_locks = 0;
void priority_inheritance(pi_lock_t *l)
{
	pri16 old_prio;
	int id = l->id;
	int counter = 0;
	while ((id != -1) && (pi_lock_list[id] != 0) && (counter < num_pi_locks))
	{
		if (proctab[pi_lock_list[id]].prprio < l->highest_priority)
		{
			proctab[pi_lock_list[id]].prprio = l->highest_priority;
			id = proctab[pi_lock_list[id]].wait_for;
		}
		counter++;
	}
		
}



void recalculate_highest_priority(pi_lock_t *l)
{
	pri16 temp;
	temp = proctab[firstid(l->q_park)].prprio;
	qid16 curr = firstid(l->q_park);
	while (curr != queuetail(l->q_park))
	{
		if (proctab[curr].prprio > l->highest_priority)
		{
			l->highest_priority = proctab[curr].prprio;
		}
		curr = queuetab[curr].qnext;
	}
}	

void restore_priority(pi_lock_t *l)
{
	proctab[currpid].prprio = l->original_priority;
	if ((l->original_priority == l->highest_priority) && nonempty(l->q_park))
	{
		recalculate_highest_priority(l);
	}
}


syscall	pi_initlock(pi_lock_t *l)
{
	if (num_pi_locks < NPILOCKS)
	{
		l->flag = 0;
		l->guard = 0;
		l->q_park = newqueue();
		l->about_to_park = 0;
		l->id = num_pi_locks;
		l->original_priority = 0;
		l->highest_priority = 0;
		num_pi_locks++;
	}
	else
	{
		return SYSERR;
	}

	return OK;
}

syscall pi_lock(pi_lock_t *l)
{
	while (test_and_set(&l->guard, 1) == 1);
	// sync_printf("currpid = %d, locking\n", currpid);
	if (l->flag == 0)
	{
		l->flag = 1;
		pi_lock_list[l->id] = currpid;
		l->original_priority = proctab[currpid].prprio;
		l->highest_priority = proctab[currpid].prprio;
		l->guard = 0;
		//sync_printf("%d LOCKED\n", currpid);
	}
	else
	{
		pi_set_park(l);		
		l->guard = 0;
		pi_park(l);
	}
	return OK;
}

syscall pi_unlock(pi_lock_t *l)
{
	while (test_and_set(&l->guard, 1) == 1);

	if (isempty(l->q_park))
	{
		restore_priority(l);
		l->flag = 0;
	}
	else
	{
		restore_priority(l);
		pi_unpark(l, dequeue(l->q_park));
	}
	//kprintf("WE ARE HERE\n");
	l->guard = 0;
	return OK;
}

void	pi_set_park(pi_lock_t *l)
{
	l->about_to_park = 1;
}

void	pi_park(pi_lock_t *l)
{
	if ((!l->about_to_park) && isempty(l->q_park))
	{
		// do nothing
	}
	else
	{
		proctab[currpid].wait_for = l->id;
		if (proctab[currpid].prprio > l->highest_priority)
		{
			l->highest_priority = proctab[currpid].prprio;
			priority_inheritance(l);
		}
		enqueue(currpid, l->q_park);
		proctab[currpid].prstate = PR_SLEEP;
		l->about_to_park = 0;
		resched();
	}
	
}

void	pi_unpark(pi_lock_t *l, pid32 pid)
{
	l->about_to_park = 0;
	proctab[pid].wait_for = -1;
	pi_lock_list[l->id] = pid;
	if (l->highest_priority > proctab[pid].prprio)
	{
		l->original_priority = proctab[pid].prprio;
		proctab[pid].prprio = l->highest_priority;
	}
	ready(pid);
}
