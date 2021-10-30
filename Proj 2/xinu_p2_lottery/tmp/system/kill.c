/* kill.c - kill */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  kill  -  Kill a process and remove it from the system
 *------------------------------------------------------------------------
 */
syscall	kill(
	  pid32		pid		/* ID of process to kill	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/
	int32	i;			/* Index into descriptors	*/

	mask = disable();
	if (isbadpid(pid) || (pid == NULLPROC)
	    || ((prptr = &proctab[pid])->prstate) == PR_FREE) {
		restore(mask);
		return SYSERR;
	}

	if (--prcount <= 1) {		/* Last user process completes	*/
		xdone();
	}

	send(prptr->prparent, pid);
	for (i=0; i<3; i++) {
		close(prptr->prdesc[i]);
	}
	freestk(prptr->prstkbase, prptr->prstklen);

	switch (prptr->prstate) {
	case PR_CURR:
		//kprintf("yo HERE, %d %d\n", currpid, pid);
		prptr->prstate = PR_FREE;	/* Suicide */
		prptr->turnaroundtime = ctr1000 - prptr->arrival_time;
		getitem(pid);
		/*if (proctab[pid].ptype == USER_P)
		{
			kprintf("\nBIIIIIIIIG PROBLEM\nBIIIIIIIIG PROBLEM\nBIIIIIIIIG PROBLEM\n");
			print_user_queue();
		}*/
		resched();

	case PR_SLEEP:
	case PR_RECTIM:
		//kprintf("SLEEP or PR_RECTIM %d %d\n", pid, prptr->prstate);
		unsleep(pid);
		prptr->prstate = PR_FREE;
		//prptr->turnaroundtime = ctr1000 - prptr->arrival_time;
		
		break;

	case PR_WAIT:
		semtab[prptr->prsem].scount++;
		/* Fall through */

	case PR_READY:
		//kprintf("0.0.0 here\n");
		getitem(pid);
		/*if (proctab[pid].ptype == USER_P)
		{
			kprintf("\nREADY BIIIIIIIIG PROBLEM\nBIIIIIIIIG PROBLEM\nBIIIIIIIIG PROBLEM\n");
			print_user_queue();
		}*/		/* Remove from queue */
		/* Fall through */

	default:
		//kprintf("currpid = %d came here\n", pid);
		prptr->turnaroundtime = ctr1000 - prptr->arrival_time;
		prptr->prstate = PR_FREE;
	}
	//kprintf("currpid = %d came here\n", pid);
	restore(mask);
	return OK;
}
