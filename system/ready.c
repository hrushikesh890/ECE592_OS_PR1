/* ready.c - ready */

#include <xinu.h>

qid16	readylist;			/* Index of ready list		*/

/*------------------------------------------------------------------------
 *  ready  -  Make a process eligible for CPU service
 *------------------------------------------------------------------------
 */
status	ready(
	  pid32		pid		/* ID of process to make ready	*/
	)
{
	uint32		start, stop;
	start =  getRTDSC();
	register struct procent *prptr;

	if (isbadpid(pid)) {
		return SYSERR;
	}

	/* Set process state to indicate ready and add to ready list */

	prptr = &proctab[pid];
	prptr->prstate = PR_READY;
	insert(pid, readylist, prptr->prprio);
	resched();
	stop = getRTDSC();
	proctab[currpid].prnumsys[SYS_READY] += 1;
	proctab[currpid].pravclkc[SYS_READY] = (proctab[currpid].pravclkc[SYS_READY] * (proctab[currpid].prnumsys[SYS_READY] - 1) + (stop - start))/  (proctab[currpid].prnumsys[SYS_READY]);
	kprintf("%d %d %d %d %d\n", currpid, SYS_READY, proctab[currpid].prnumsys[SYS_READY], stop - start, proctab[currpid].pravclkc[SYS_READY]);
	return OK;
}
