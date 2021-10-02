/* resched.c - resched, resched_cntl */

#include <xinu.h>
//#define DEBUG_CTXSW 1

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
	intmask mask;
	mask = disable();
	/* If rescheduling is deferred, record attempt and return */
	kprintf("0. CAME HERE NO PROBLEM\n");
	
	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}
	//kprintf("0. CAME HERE NO PROBLEM\n");
	/* Point to process table entry for the current (old) process */
	//if (ptold)
	ptold = &proctab[currpid];
	old = currpid;
	//kprintf("1. CAME HERE NO PROBLEM\n");
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
		
		if ((isempty(readylist) || (firstid(readylist) == 0)) && nonempty(userprocesslist))
		{
			//kprintf("SHOULD COME HERE\n");
			user_flag = TRUE;
		}
	}
	else
	{
		//kprintf("NON CURR PROCESS APPEARED %d\n", currpid);
	}	
	//kprintf("2. CAME HERE NO PROBLEM\n");
	recompute_tickets();
	//kprintf("2_2. CAME HERE NO PROBLEM\n");
	if ((ptold->runtime > 500) && (ptold->runtime < 515))
	{
		print_user_queue();
	}
	
	if (user_flag && (total_tickets > 0))
	{
		currpid = find_winner(get_random_number(total_tickets));
		kprintf("(%d). (%d)\n", currpid, proctab[currpid].runtime);
	}
	else{	
		/* Force context switch to highest priority ready process */
		currpid = dequeue(readylist);
	}
	
	//kprintf("SO THE PROBLEM WAS HERE %d %d\n", currpid, proctab[currpid].prstate);		
	


	ptnew = &proctab[currpid];
	//kprintf("3. CAME HERE NO PROBLEM\n");
	ptnew->prstate = PR_CURR;
	preempt = QUANTUM;		/* Reset time slice for process	*/
	//kprintf("4. CAME HERE NO PROBLEM\n");
	#ifdef DEBUG_CTXSW
		if(old != currpid)
		{
			//kprintf("total tickets = %d\n", total_tickets);
			kprintf("ctxsw::%d-%d\n", old, currpid);
		}
	#endif
	//kprintf("3. old id:%d newid %d  userprocesslist %d\n", old, currpid, nonempty(userprocesslist));
	//print_ready_list();
	//kprintf("5. CAME HERE NO PROBLEM\n");
	if(old != currpid)
	{
		ptnew->num_ctxsw++;
	}
	//kprintf("6. CAME HERE NO PROBLEM\n");
	kprintf("(%d). (%d) (%u) (%u) (%d) (%d)\n", old, currpid, ptold->prstkptr, ptnew->prstkptr, ptold->prstate, ptnew->prstate);
	
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);
	restore(mask);
	kprintf("7. CAME HERE NO PROBLEM\n");
	

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
