#include <xinu.h>

void pr_status_syscall_summary()
{
	int i, j;
	char *sys_string[] = {"create", "kill", "ready", "sleepms", "suspend", "wait", "wakeup", "yield"};
	printf("%3s %7s %5s %-14s\n", "pid", "syscall", "count", "average cycles");
	printf("%3s %7s %5s %-14s\n", "---", "-------", "-----", "--------------");
	
	for (i = 0; i < NPROC; i++)
	{
		if (proctab[i].prstate != PR_FREE)
		{
			for (j = 0; j < NSYS; j++)
			{
				if (proctab[i].prnumsys[j] > 0)
				{
					printf("%3d %7s %5d %14d\n", i, sys_string[j], proctab[i].prnumsys[j], proctab[i].pravclkc[j]);
				}
			}
			printf("--------------------------------\n");
		}
	}
}

