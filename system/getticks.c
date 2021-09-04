/* getticks.c - getticks */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getticks  -  Retrieve the number of clock ticks since CPU reset
 *------------------------------------------------------------------------
 */
uint64	getticks()
{
	uint64 ret;
	asm volatile ( "rdtsc" : "=A"(ret) );
	return ret;
}


// Get RTDSC time from timer
uint32	getRTDSC()
{
	uint64 ret;
	unsigned low, high;
	
	asm volatile (
		"RDTSC\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t": "=r" (high), "=r" (low));
	ret = (((uint64)high << 32) | low);
	return (uint32)ret;
}


