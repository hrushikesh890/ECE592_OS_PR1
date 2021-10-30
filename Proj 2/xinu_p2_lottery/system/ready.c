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
	register struct procent *prptr;
	intmask	mask;
	if (isbadpid(pid)) {
		return SYSERR;
	}

	/* Set process state to indicate ready and add to ready list */
	mask = disable();
	prptr = &proctab[pid];
	prptr->prstate = PR_READY;
	//kprintf("02. PID %d, PTYPE = %d comp %d\n", pid, prptr->ptype, (prptr->ptype == USER_P));
	if (prptr->ptype == USER_P)
	{
		insert_to_user(pid, prptr->tickets);
	}
	else
	{
		insert(pid, readylist, prptr->prprio);
	}
	restore(mask);
	resched();

	return OK;
}
