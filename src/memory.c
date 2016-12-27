#include "stdlib.h"
#include "stdint.h"
#include "string.h"

#include "brk.h"

void *malloc(size_t size)
{
	void *mem = sbrk(size);
	if ((long)mem == -1)
		return NULL;

	return (void *)mem;
}


void *calloc(size_t count, size_t size)
{
	void *mem = malloc(count * size);
	if ((long)mem == -1)
		return NULL;

	memset(mem, 0, (count * size));
	return mem;
}

void *realloc(void *p, size_t size)
{
	return NULL;
}


void free(void *p)
{
}

void *memcpy(void *dest, const void *src, size_t n)
{
	for (int i = 0; i < n; i++)
		((uint8_t *)dest)[i] = ((uint8_t *)src)[i];

	return dest;
}


void *memset(void *s, int c, size_t n)
{
	for (int i = 0; i < n; i++)
		((uint8_t *)s)[i] = (uint8_t)c;

	return s;
}

/*
void *memmove(void *dest, const void *src, size_t n)
{
	return dest;
}	
*/
