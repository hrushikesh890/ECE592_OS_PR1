/* yield.c - yield */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  yield  -  Voluntarily relinquish the CPU (end a timeslice)
 *------------------------------------------------------------------------
 */
syscall	yield(void)
{
	uint32		start, stop;
	start =  getRTDSC();
	intmask	mask;			/* Saved interrupt mask		*/
	proctab[currpid].prnumsys[SYS_YIELD] += 1;
	mask = disable();
	resched();
	restore(mask);
	stop = getRTDSC();
	
	proctab[currpid].pravclkc[SYS_YIELD] = (proctab[currpid].pravclkc[SYS_YIELD] * (proctab[currpid].prnumsys[SYS_YIELD] - 1) + (stop - start))/  (proctab[currpid].prnumsys[SYS_YIELD]);
	return OK;
}
