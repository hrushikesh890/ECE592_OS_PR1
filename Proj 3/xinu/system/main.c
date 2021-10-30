#include <xinu.h>
 
void sync_printf(char *fmt, ...)
{
    	intmask mask = disable();
	void *arg = __builtin_apply_args();
	__builtin_apply((void*)kprintf, arg, 100);
	restore(mask);
}
process do_something_1(al_lock_t *mutex1, al_lock_t *mutex2)
{
	al_lock(mutex1);
	sync_printf("lock1 acquired by 1\n");
	sleepms(100);
	al_lock(mutex2);
	sync_printf("lock2 acquired by 1\n");
	sync_printf("SHOULD NOT EXECUTE_1\n");
	
	al_unlock(mutex1);
	al_unlock(mutex2);
}
process do_something_2(al_lock_t *mutex2, al_lock_t *mutex3)
{
	al_lock(mutex2);
	//sync_printf("lock2 acquired by 2\n");
	sleepms(30);
	al_lock(mutex3);
	sync_printf("lock1 acquired by 2\n");
	sync_printf("SHOULD NOT EXECUTE_2\n");
	
	al_unlock(mutex2);
	al_unlock(mutex3);
}

process do_something_3(al_lock_t *mutex1, al_lock_t *mutex3)
{
	al_lock(mutex3);
	//sync_printf("lock2 acquired by 2\n");
	sleepms(10);
	al_lock(mutex1);
	sync_printf("lock1 acquired by 2\n");
	sync_printf("SHOULD NOT EXECUTE_2\n");
	
	al_unlock(mutex1);
	al_unlock(mutex3);
}

process do_something_4(al_lock_t *mutex1, al_lock_t *mutex2)
{
	al_lock(mutex1);
	//sync_printf("lock1 acquired by 1\n");
	sleepms(100);
	al_lock(mutex2);
	sync_printf("lock2 acquired by 1\n");
	sync_printf("SHOULD NOT EXECUTE_1\n");
	
	al_unlock(mutex1);
	al_unlock(mutex2);
}
process do_something_5(al_lock_t *mutex1, al_lock_t *mutex2)
{
	al_lock(mutex2);
	//sync_printf("lock2 acquired by 2\n");
	sleepms(30);
	al_lock(mutex1);
	sync_printf("lock1 acquired by 2\n");
	sync_printf("SHOULD NOT EXECUTE_2\n");
	
	al_unlock(mutex2);
	al_unlock(mutex1);
}

process main(void)
{
	al_lock_t mutex1;
	al_lock_t mutex2;
	al_lock_t mutex3;
	al_lock_t mutex4;
	al_lock_t mutex5;
	
	al_initlock(&mutex1);
	al_initlock(&mutex2);
	al_initlock(&mutex3);
	al_initlock(&mutex4);
	al_initlock(&mutex5);
	
	resume(create((void *)do_something_1, INITSTK, 1,"s1", 2, &mutex1, &mutex2));
	resume(create((void *)do_something_2, INITSTK, 1,"s1", 2, &mutex2, &mutex3));
	resume(create((void *)do_something_3, INITSTK, 1,"s1", 2, &mutex1, &mutex3));
	resume(create((void *)do_something_4, INITSTK, 1,"s1", 2, &mutex4, &mutex5));
	resume(create((void *)do_something_5, INITSTK, 1,"s1", 2, &mutex4, &mutex5));
	
	receive();
	receive();
	receive();
} 
