/* resched.c - resched, resched_cntl */

#include <xinu.h>
#define DEBUG_CTXSW 1

struct	defer	Defer;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */

void	resched(void)		// /* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/
	pid32	old;
	bool8	user_flag = FALSE;
	//kprintf("1. old id:%d readyfirst %d  userprocesslist %d\n", currpid, firstid(readylist), nonempty(userprocesslist));
	//print_ready_list();
	/* If rescheduling is deferred, record attempt and return */
	
	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}
	//kprintf("2. old id:%d readyfirst %d  userflag %d\n", currpid, firstid(readylist), user_flag);
	/* Point to process table entry for the current (old) process */
	//if (ptold)
	ptold = &proctab[currpid];
	old = currpid;
	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		if ((ptold->prprio > firstkey(readylist)) && (ptold->ptype == SYSTEM_P) && nonempty(readylist)) {
			//kprintf("Should not come_here %d %d\n", ptold->prprio, firstkey(readylist));			
			return;
		}
		ptold->prstate = PR_READY;

		if (ptold->ptype == SYSTEM_P)
		{
			insert(currpid, readylist, ptold->prprio);
		}
		else
		{
			insert_to_user(currpid, ptold->tickets);
		}
	}
	if ((isempty(readylist) || (firstid(readylist) == 0)) && nonempty(userprocesslist))
	{
		//kprintf("SHOULD COME HERE\n");
		user_flag = TRUE;
	}

	
	if (user_flag && (total_tickets != 0))
	{
		currpid = find_winner(get_random_number(total_tickets));
		kprintf("total tickets = %d and runtime = %d\n", total_tickets, proctab[currpid].runtime);
	}
	else{	
		/* Force context switch to highest priority ready process */
		currpid = dequeue(readylist);
	}


	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = QUANTUM;		/* Reset time slice for process	*/
	#ifdef DEBUG_CTXSW
		if(old != currpid)
		{
			//kprintf("total tickets = %d\n", total_tickets);
			kprintf("ctxsw::%d-%d\n", old, currpid);
		}
	#endif
	//kprintf("3. old id:%d newid %d  userprocesslist %d\n", old, currpid, nonempty(userprocesslist));
	//print_ready_list();
	if(old != currpid)
	{
		ptnew->num_ctxsw++;
	}
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
