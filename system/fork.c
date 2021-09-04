#include <xinu.h>
pid32 fork()
{
	stacktrace(currpid);
	pid32 retPID = NPROC;
	pid32 childPID = 0, parentPID = 0;
	parentPID = currpid;

	childPID = create_child();
	
	if (childPID == SYSERR)
	{
		return SYSERR;
	}
	
	if (currpid == parentPID)
	{
		kprintf("CHILD PRINTING");
		stacktrace(childPID);
		return childPID;
	}
	else
	{
		return retPID;
	}
}

pid32 create_child()
{
	uint32		savsp, *pushsp;
	intmask 	mask;    	/* Interrupt mask		*/
	pid32		pid;		/* Stores new process id	*/
	struct	procent	*prptr;		/* Pointer to proc. table entry */
	struct	procent	*parentptr;	
	int32		i;
	uint32		*a;		/* Points to list of args	*/
	uint32		*saddr;		/* Stack address		*/
	unsigned long	*sebp, *sbase;
	uint32 	ssize;
	unsigned long	*fp, *sp;

	parentptr = &proctab[currpid];
	ssize = parentptr->prstklen;
	mask = disable();
	
	if (ssize < MINSTK)
		ssize = MINSTK;
	ssize = (uint32) roundmb(ssize);
	if ( (parentptr->priority < 1) || ((pid=newpid()) == SYSERR) ||
	     ((saddr = (uint32 *)getstk(ssize)) == (uint32 *)SYSERR) ) {
		restore(mask);
		return SYSERR;
	}

	prcount++;
	prptr = &proctab[pid];
	

	/* Initialize process table entry for new process */
	prptr->prstate = PR_SUSP;	/* Initial state is suspended	*/
	prptr->prprio = parentptr->prprio;
	prptr->prstkbase = (char *)saddr;
	prptr->prstklen = ssize;
	prptr->prtime = ctr1000; /* Assign the created time */
	prptr->prname[PNMLEN-1] = NULLCH;
	for (i=0 ; i<PNMLEN-1 && (prptr->prname[i]=parentptr->prname[i])!=NULLCH; i++)
		;
	prptr->prsem = -1;
	prptr->prparent = (pid32)getpid();
	prptr->prhasmsg = FALSE; 

	/* Set up stdin, stdout, and stderr descriptors for the shell	*/
	prptr->prdesc[0] = CONSOLE;
	prptr->prdesc[1] = CONSOLE;
	prptr->prdesc[2] = CONSOLE;

	/* Initialize stack as if the process was called		*/
	savsp = (uint32)saddr;
	// Copy data
	asm("movl %%ebp, %0\n" :"=r"(fp));
	
	fp++; // return address of prev stack frame
	sp = (unsigned long)(parentptr->prstkbase);
	while((unsigned long)(parentptr->prstkbase) > fp)
	{
		*saddr = *sp;
		sp--;
		saddr--;
	}	

	
	restore(mask);
	return pid;
}

