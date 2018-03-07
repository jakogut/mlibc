#include "stdlib.h"
#include "stdint.h"
#include "string.h"

#include "brk.h"

#define ALLOC_INFO_SIZE sizeof(struct alloc_info)
#define info_from_alloc(alloc) (struct alloc_info *)(alloc - sizeof(struct alloc_info))

struct alloc_info {
	size_t size;
};

void *malloc(size_t size)
{
	void *mem = sbrk(size + ALLOC_INFO_SIZE) + ALLOC_INFO_SIZE;
	if ((long)mem == -1)
		return NULL;

	struct alloc_info *header = info_from_alloc(mem);
	header->size = size;

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
	void *buf = malloc(size);
	if (p != NULL) {
		struct alloc_info *header = info_from_alloc(p);
		memcpy(buf, p, header->size);
	}
	return buf;
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


void *memmove(void *dest, const void *src, size_t n)
{
	char *buf = malloc(n);
	memcpy(buf, src, n);
	memcpy(dest, buf, n);
	free(buf);

	return dest;
}	

