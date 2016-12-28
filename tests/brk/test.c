#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

int main()
{
	void *res;
	void *current_brk, *old_brk;
	const size_t offset = 0x1000;

	printf("Checking brk(0) returns -1\n");
	assert(brk(0) == -1);
	printf("PASSED\n\n");

	printf("Checking sbrk(0) returns current break\n");
	current_brk = (void *)(size_t)sbrk(NULL);
	assert(current_brk);
	printf("PASSED\n\n");

	printf("Checking brk(current_brk + offset) returns 0\n");
	res = (void *)(size_t)brk((void *)(current_brk + offset));
	assert(res == 0);
	printf("PASSED\n\n");

	printf("Checking program break was increased\n");
	old_brk = current_brk;
	current_brk = (void *)(size_t)sbrk(NULL);
	printf("old_brk: %p current_brk: %p\n", old_brk, current_brk);
	assert((void *)(old_brk + offset) == current_brk);
	printf("PASSED\n\n");

	printf("Checking sbrk(offset) returned previous break\n");
	old_brk = current_brk;
	res = (void *)(size_t)sbrk(offset);
	assert(res == old_brk);
	printf("PASSED\n\n");

	printf("Checking sbrk(offset) increased program break\n");
	current_brk = (void *)(size_t)sbrk(NULL);
	printf("old_brk: %p, current_brk: %p\n", old_brk, current_brk);
	assert(current_brk >= (old_brk + offset));
	printf("PASSED\n\n");

	return 0;
}
