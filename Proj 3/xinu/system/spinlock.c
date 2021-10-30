#include <xinu.h>
int num_spinlocks = 0;
syscall	sl_initlock(sl_lock_t *l)
{
	if (num_spinlocks < NSPINLOCKS)
	{
		num_spinlocks += 1;
		*l = 0;
	}
	else
	{
		return SYSERR;
	}
	return OK;
}

syscall sl_lock(sl_lock_t *l)
{
	while (test_and_set(l, 1) == 1);
	//kprintf("LOCK TAKEN BY %d\n", currpid);
	return OK;
}

syscall sl_unlock(sl_lock_t *l)
{
	//kprintf("LOCK RELEASED BY %d\n", currpid);
	*l = 0;
	return OK;
}
