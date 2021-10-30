#include <xinu.h>
int num_locks = 0;
syscall	initlock(lock_t *l)
{
	if (num_locks < NLOCKS)
	{
		l->flag = 0;
		l->guard = 0;
		l->q_park = newqueue();
		l->about_to_park = 0;
		num_locks++;
	}
	else
	{
		return SYSERR;
	}

	return OK;
}

syscall lock(lock_t *l)
{
	while (test_and_set(&l->guard, 1) == 1);
	// sync_printf("currpid = %d, locking\n", currpid);
	if (l->flag == 0)
	{
		l->flag = 1;
		l->guard = 0;
		//sync_printf("%d LOCKED\n", currpid);
	}
	else
	{
		set_park(l);		
		l->guard = 0;
		park(l);
	}
	return OK;
}

syscall unlock(lock_t *l)
{
	while (test_and_set(&l->guard, 1) == 1);

	if (isempty(l->q_park))
	{
		l->flag = 0;
	}
	else
	{
		//kprintf("CAME HERE %d %d\n", currpid, firstid(l->q_park));
		unpark(l, dequeue(l->q_park));
	}
	//kprintf("WE ARE HERE\n");
	l->guard = 0;
	return OK;
}

void	set_park(lock_t *l)
{
	l->about_to_park = 1;
}

void	park(lock_t *l)
{
	if ((!l->about_to_park) && isempty(l->q_park))
	{
		// do nothing
	}
	else
	{
		//sync_printf("currpid = %d, queueing = %d\n", currpid, l->q_park);
		enqueue(currpid, l->q_park);
		proctab[currpid].prstate = PR_SLEEP;
		l->about_to_park = 0;
		resched();
	}
	
}

void	unpark(lock_t *l, pid32 pid)
{
	l->about_to_park = 0;
	//sync_printf("%d pid = %d\n", l->id, pid);
	ready(pid);
}
