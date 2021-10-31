#include <xinu.h>
int num_active_locks = 0;

bool8 detect_deadlock(al_lock_t* l)
{
	int counter = 0; 
	int id = l->id;
	//sync_printf("detect Called id = %d active_lock_list = %d, counter = %d\n", l->id, active_lock_list[id]);
	while ((id != -1) && (counter < num_active_locks) && (active_lock_list[id] != 0))
	{
		//sync_printf("detect l-id = %d active_lock_list = %d , wait for = %d\n", l->id, active_lock_list[id],proctab[active_lock_list[id]].wait_for);
		if (proctab[active_lock_list[id]].wait_for == l->id)
		{
			return 1;
		}
		else 
		{
			id = proctab[active_lock_list[id]].wait_for;
		}
		counter++;
	}
	return 0;
}

	
void print_deadlock(al_lock_t* l)
{
	int deadlock_list[NALOCKS];
	int counter = 0; 
	int id = l->id;
	int i, j;
	pid32 temp;
	intmask mask;
	mask = disable();
	for (i = 0; i < NALOCKS; i++)
	{
		deadlock_list[i] = NPROC + 1;
	}
	while ((counter < NALOCKS) && (active_lock_list[id] != 0))
	{
		//kprintf("PRINTING .. counter = %d, wait_for = %d, active = %d\n", counter, proctab[active_lock_list[id]].wait_for, active_lock_list[id]);
		if (proctab[active_lock_list[id]].wait_for == l->id){
			deadlock_list[counter] = active_lock_list[id];
			counter++;
			break;
		}
		else 
		{	
			//kprintf("ENTERED ELSE\n");
			deadlock_list[counter] = active_lock_list[id];
			id = proctab[active_lock_list[id]].wait_for;
		}
		counter++;
	}
	
	for (i = 0; i < counter; i++)
	{
		for (j = 0; j < counter - i; j++)
		{
			if (deadlock_list[j] > deadlock_list[j+1])
			{
				temp = deadlock_list[j];
				deadlock_list[j] = deadlock_list[j+1];
				deadlock_list[j+1] = temp;
			}
		}
	}
	kprintf("lock_detected=");
	for (i = 0; i < counter; i++)
	{
		kprintf("P%d", deadlock_list[i]);
		if (i != (counter - 1))
		{
			kprintf("-");
		}
	}
	kprintf("\n");
	restore(mask);
}

syscall	al_initlock(al_lock_t *l)
{
	if (num_active_locks < NALOCKS)
	{
		l->flag = 0;
		l->guard = 0;
		l->q_park = newqueue();
		l->about_to_park = 0;
		l->id = num_active_locks;
		num_active_locks++;
	}
	else
	{
		return SYSERR;
	}

	return OK;
}

syscall al_lock(al_lock_t *l)
{
	while (test_and_set(&l->guard, 1) == 1);
	// sync_printf("currpid = %d, locking\n", currpid);
	if (l->flag == 0)
	{
		l->flag = 1;
		active_lock_list[l->id] = currpid;
		l->guard = 0;
		//sync_printf("%d LOCKED\n", currpid);
	}
	else
	{
		//sync_printf("HERE currrpid = %d\n", currpid);
		al_set_park(l);
		/*if (detect_deadlock(l))
		{
			print_deadlock(l);
		}*/		
		l->guard = 0;
		al_park(l);
	}
	return OK;
}

syscall al_unlock(al_lock_t *l)
{
	//sync_printf("Should not be called yet %d\n", currpid);
	while (test_and_set(&l->guard, 1) == 1);

	if (isempty(l->q_park))
	{
		l->flag = 0;
		active_lock_list[l->id] = 0;
	}
	else
	{
		al_unpark(l, dequeue(l->q_park));
	}
	l->guard = 0;
	return OK;
}

void	al_set_park(al_lock_t *l)
{
	l->about_to_park = 1;
}

void	al_park(al_lock_t *l)
{
	if ((!l->about_to_park) && isempty(l->q_park))
	{
		// do nothing
	}
	else
	{
		proctab[currpid].wait_for = l->id;
		if (detect_deadlock(l))
		{
			print_deadlock(l);
		}
		enqueue(currpid, l->q_park);
		proctab[currpid].prstate = PR_SLEEP;
		l->about_to_park = 0;
		resched();
	}
	
}

void	al_unpark(al_lock_t *l, pid32 pid)
{
	l->about_to_park = 0;
	proctab[pid].wait_for = -1;
	active_lock_list[l->id] = pid;
	ready(pid);
}

bool8 al_trylock(al_lock_t *l)
{
	while (test_and_set(&l->guard, 1) == 1);
	if (l->flag == 0)
	{
		l->flag = 1;
		active_lock_list[l->id] = currpid;
		l->guard = 0;
	}
	else
	{
		return 0;
	}
	return 1;
}
