#include <xinu.h>

/*void sync_printf(char *fmt, ...)
{
    	intmask mask = disable();
	void *arg = __builtin_apply_args();
	__builtin_apply((void*)kprintf, arg, 100);
	restore(mask);
}
process do_something_1(pi_lock_t *mutex1)
{
	uint32 start = proctab[currpid].runtime;
	pi_lock(mutex1);
	
	while ((proctab[currpid].runtime - start) < 1000);
	
	pi_unlock(mutex1);
	
}

process do_something_2(pi_lock_t *mutex1)
{
	uint32 start = proctab[currpid].runtime;
	pi_lock(mutex1);
	
	while ((proctab[currpid].runtime - start) < 1000);
	
	pi_unlock(mutex1);
	
}

process do_something_3(pi_lock_t *mutex1)
{
	uint32 start = proctab[currpid].runtime;
	pi_lock(mutex1);
	
	while ((proctab[currpid].runtime - start) < 1000);
	
	pi_unlock(mutex1);
	
}

process main(void)
{
	pi_lock_t mutex1;
	
	
	pi_initlock(&mutex1);
	
	
	resume(create((void *)do_something_1, INITSTK, 1,"s1", 1, &mutex1));
	resume(create((void *)do_something_2, INITSTK, 2,"s1", 1, &mutex1));
	resume(create((void *)do_something_3, INITSTK, 3,"s1", 1, &mutex1));
	
	
	receive();
	receive();
	receive();
} 
*/
