#include "stdlib.h"

#include "syscall.h"

int brk(void *addr)
{
	long ret = syscall(SYS_brk, addr);
	if (ret != (long)addr)
		return -1;

	return 0;
}

void *sbrk(size_t increment)
{
	void *current_brk = (void *)syscall(SYS_brk, 0);
	if (!increment) return current_brk;

	if (brk(current_brk + increment) == 0)
		return current_brk;
	
	return (void *)(-1);
}
