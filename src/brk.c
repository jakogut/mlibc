#include "stdlib.h"

#include "syscall.h"

int brk(void *addr)
{
	long ret = syscall(SYS_brk, addr);
	if (ret < (long)addr)
		return -1;

	return 0;
}

void *sbrk(intptr_t increment)
{
	long current_brk = syscall(SYS_brk, 0);
	if (!increment) return (void *)current_brk;

	if (brk((void *)(current_brk + increment)) == 0)
		return (void *)current_brk;
	
	return (void *)(-1);
}
