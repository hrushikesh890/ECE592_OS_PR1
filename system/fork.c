#include <xinu.h>

pid32 create_child();

pid32 fork()
{
	//stacktrace(currpid);
	pid32 retPID = NPROC;
	pid32 childPID, parentPID;
	struct procent	*proc = &proctab[currpid];

	childPID = create_child();
	/*stacktrace(currpid);
	asm("movl %%esp, %0\n" :"=r"(sp));
	asm("movl %%ebp, %0\n" :"=r"(fp));
	//kprintf("EBP = (%08X) ESP = (%08X) prststackbase = (%X)\n", fp, sp, proc->prstkbase);*/ // UNCOMMENT for debug
	if (childPID == SYSERR)
	{
		return SYSERR;
	}

	if (currpid == childPID)
	{
		return NPROC;
	}

	return childPID;

}

pid32 create_child()
{
	uint32		savsp, *pushsp;
	intmask 	mask;    	/* Interrupt mask		*/
	pid32		pid;		/* Stores new process id	*/
	struct	procent	*prptr;		/* Pointer to proc. table entry */
	struct	procent	*parentptr;	
	int32		i;
	uint32		*saddr;		/* Stack address		*/
	uint32 	ssize;
	unsigned long	*fp, *sp;

	parentptr = &proctab[currpid];
	ssize = parentptr->prstklen;
	mask = disable();
	
	if (ssize < MINSTK)
		ssize = MINSTK;
	ssize = (uint32) roundmb(ssize);
	if ( (parentptr->prprio < 1) || ((pid=newpid()) == SYSERR) ||
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
	for (i=0 ; i<PNMLEN-1 && (prptr->prname[i]=parentptr->prname[i])!=NULLCH; i++);
	prptr->prsem = -1;
	prptr->prparent = (pid32)getpid();
	prptr->prhasmsg = FALSE; 

	/* Set up stdin, stdout, and stderr descriptors for the shell	*/
	prptr->prdesc[0] = CONSOLE;
	prptr->prdesc[1] = CONSOLE;
	prptr->prdesc[2] = CONSOLE;

	/* Initialize stack as if the process was called		*/
	//*saddr = STACKMAGIC; // Not necessary as copying will add the stackmagic
	savsp = (uint32)saddr; // the saved sp pointing to the top of child
	// Copy data
	asm("movl %%ebp, %0\n" :"=r"(fp));
	pushsp = (uint32)(parentptr->prstkbase);
	sp = (unsigned long *)(parentptr->prstkbase);
	

	/*DATA (005E3F80) 00000200 (512)
	DATA (005E3F84) 0011F3EC (1176556)
	DATA (005E3F88) 005E3F98 (6176664)
	DATA (005E3F8C) 005E3F8C (6176652)
	DATA (005E3F90) 00116D6E (1142126)
	DATA (005E3F94) 00000008 (8)

	FP   (005E3F98) 005E3FD8 (6176728)
	RET  0x100F6A
	DATA (005E3FA0) 00000005 (5)
	DATA (005E3FA4) 005D3FC8 (6111176)
	DATA (005E3FA8) 00000202 (514)
	DATA (005E3FAC) 0010405C (1065052)
	DATA (005E3FB0) 00000000 (0)
	DATA (005E3FB4) 00320000 (3276800)
	DATA (005E3FB8) 0011F468 (1176680)
	DATA (005E3FBC) 00000200 (512)
	DATA (005E3FC0) 0011359C (1127836)
	DATA (005E3FC4) 00002000 (8192)
	DATA (005E3FC8) 005E3FE8 (6176744)
	DATA (005E3FCC) 00102972 (1059186)
	DATA (005E3FD0) 00000006 (6)
	DATA (005E3FD4) 00000000 (0)

	FP   (005E3FD8) 005E3FE8 (6176744) <- pushsp point to new stkbase i.e Stackmagic
	RET  0x10297A
	DATA (005E3FE0) 00000000 (0)
	DATA (005E3FE4) 005E3FFC (6176764)

	FP   (005E3FE8) 005E3FFC (6176764) <- pushsp replace these references in child
	RET  0x104CB2
	DATA (005E3FF0) 005E3FFC (6176764)
	DATA (005E3FF4) 00102933 (1059123)
	DATA (005E3FF8) 00104CB2 (1068210)
	STACKMAGIC (should be A0AAAA9): A0AAAA9
	EBP = (005E3FD8) ESP = (005E3FB0) prststackbase = (5E3FFC)*/	
	// Copy from STACKMAGIC to EBP 
	while(sp >= fp)
	{
		if (*sp == pushsp) // data pointed by sp is same as location of pushp
		{
			pushsp = sp;
			*saddr = savsp; // save location of top of frame in saddr
			savsp = saddr;
			sp--;
			saddr--;
		}
		else
		{			
			*saddr = *sp; // Copy data
			sp--;
			saddr--;
		}
	}	
	//++saddr; // extra decrement
	// From this point on everything is same as the as the new process creation.
	*saddr = 0x00000200;		
	
	/* Push all instruction from create*/
	*--saddr = NPROC;			/* %eax */
	*--saddr = 0;			/* %ecx */
	*--saddr = 0;			/* %edx */
	*--saddr = 0;			/* %ebx */
	*--saddr = 0;			/* %esp; value filled in below	*/
	pushsp = saddr;			/* Remember this location	*/
	*--saddr = savsp;		/* %ebp (while finishing ctxsw)	*/
	*--saddr = 0;			/* %esi */
	*--saddr = 0;			/* %edi */
	*pushsp = (unsigned long) (prptr->prstkptr = (char *)saddr);
	prptr->prstate = PR_READY;
	insert(pid, readylist, prptr->prprio);
	
	restore(mask);
	return pid;
}

