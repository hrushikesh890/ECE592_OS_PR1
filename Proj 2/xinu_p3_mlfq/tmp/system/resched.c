/* resched.c - resched, resched_cntl */

#include <xinu.h>
//#define DEBUG_CTXSW

struct	defer	Defer;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/
	pid32	old;
	bool8	user_flag;
	bool8	user_scheduled = FALSE;
	bool8	system_scheduled = FALSE;

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}


	
	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];
	old = currpid;
	
	

	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		if ((ptold->prprio > firstkey(readylist)) && (ptold->ptype == SYSTEM_P) && nonempty(readylist)) {
			return;
		}

		/* Old process will no longer remain current */
		if (ptold->ptype != SYSTEM_P)
		{
			if (ptold->time_alloted >= TIME_ALLOTMENT)
			{
				//kprintf("%d TIME ALLOTED = %d\n", currpid, ptold->time_alloted);
				if (ptold->ptype == USER_P_LOW)
				{
					ptold->time_alloted = 0;
				}
				else
				{
					ptold->ptype += 1;
					ptold->time_alloted = 0;
				}
			}
		}

		ptold->prstate = PR_READY;
		if (ptold->ptype == SYSTEM_P)
		{
			insert(currpid, readylist, ptold->prprio);
		}
		else
		{
			insert_to_user(currpid);
		}
	}

	if (priority_boost_timer >= PRIORITY_BOOST_PERIOD)
	{
		priority_boost_timer = 0;
		priority_boost();
	}

	// Decide whether to mlfq schedule
	if (nonempty(readylist) && (firstid(readylist) != 0))
	{
		user_flag = FALSE;
		currpid = dequeue(readylist);
		system_scheduled = TRUE;
	}
	else{
		if (nonempty(high))
		{
			currpid = dequeue(high);
			user_scheduled = TRUE;
		}
		else if (nonempty(med))
		{
			currpid = dequeue(med);
			user_scheduled = TRUE;
		}
		else if (nonempty(low))
		{
			currpid = dequeue(low);
			user_scheduled = TRUE;
		}
		else
		{
			user_scheduled = FALSE;
		}
	}

	if ((!user_scheduled) && (!system_scheduled))
	{
		currpid = dequeue(readylist);
	}

	/* Force context switch to highest priority ready process */

	//kprintf("THIS %d %d %d\n", currpid, system_scheduled, user_scheduled);
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = get_time_slice(ptnew->ptype);		/* Reset time slice for process	*/
	#ifdef DEBUG_CTXSW
		if(/*old != currpid*/ proctab[currpid].ptype > 0)
		{
			kprintf("ctxsw::%d-%d %d %d\n", old, currpid, proctab[currpid].ptype, proctab[currpid].runtime);
		}
	#endif
	if(old != currpid)
		{
			proctab[currpid].num_ctxsw++;
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
