		.text
		.globl	test_and_set

test_and_set:
	/* Initial*/
	pushl	%ebp		// Save EBP on stack as it will be modified
	movl	8(%esp), %ebp	// Load old value to to ebp
	/* exchange */
	movl	12(%esp), %eax	// Load new value to eax
	xchg	(%ebp), %eax	// exchange ebp and eax
	popl	%ebp		// Restore ebp
	ret			// return
	
