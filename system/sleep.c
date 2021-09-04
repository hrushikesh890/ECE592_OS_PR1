/* sleep.c - sleep sleepms */

#include <xinu.h>

#define	MAXSECONDS	2147483		/* Max seconds per 32-bit msec	*/

/*------------------------------------------------------------------------
 *  sleep  -  Delay the calling process n seconds
 *------------------------------------------------------------------------
 */
syscall	sleep(
	  int32	delay		/* Time to delay in seconds	*/
	)
{
	if ( (delay < 0) || (delay > MAXSECONDS) ) {
		return SYSERR;
	}
	sleepms(1000*delay);
	return OK;
}

/*------------------------------------------------------------------------
 *  sleepms  -  Delay the calling process n milliseconds
 *------------------------------------------------------------------------
 */
syscall	sleepms(
	  int32	delay			/* Time to delay in msec.	*/
	)
{
	uint32		start, stop;
	start =  getRTDSC();
	intmask	mask;			/* Saved interrupt mask		*/

	if (delay < 0) {
		return SYSERR;
	}

	if (delay == 0) {
		yield();
		return OK;
	}

	/* Delay calling process */

	mask = disable();
	if (insertd(currpid, sleepq, delay) == SYSERR) {
		restore(mask);
		return SYSERR;
	}

	proctab[currpid].prstate = PR_SLEEP;
	proctab[currpid].prnumsys[SYS_SLEEPMS] += 1; // Set before resched and after state change because status will not increment till resched has finished
	resched();
	restore(mask);
	proctab[currpid].pravclkc[SYS_SLEEPMS] = (proctab[currpid].pravclkc[SYS_SLEEPMS] * (proctab[currpid].prnumsys[SYS_SLEEPMS] - 1) + (stop - start))/  (proctab[currpid].prnumsys[SYS_SLEEPMS]);
	return OK;
}
