/* wakeup.c - wakeup */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  wakeup  -  Called by clock interrupt handler to awaken processes
 *------------------------------------------------------------------------
 */
void	wakeup(void)
{
	/* Awaken all processes that have no more time to sleep */
	uint32		start, stop;
	start =  getRTDSC();
	resched_cntl(DEFER_START);
	while (nonempty(sleepq) && (firstkey(sleepq) <= 0)) {
		ready(dequeue(sleepq));
	}
	resched_cntl(DEFER_STOP);
	stop = getRTDSC();
	proctab[currpid].prnumsys[SYS_WAKEUP] += 1;
	proctab[currpid].pravclkc[SYS_WAKEUP] = (proctab[currpid].pravclkc[SYS_WAKEUP] * (proctab[currpid].prnumsys[SYS_WAKEUP] - 1) + (stop - start))/  (proctab[currpid].prnumsys[SYS_WAKEUP]);
	return;
}
