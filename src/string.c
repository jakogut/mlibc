#include "stdlib.h"

/*int printf(const char *format, ...)
{
	return 0;
}
*/

char *strcat(char *dest, const char *src)
{
	char *dp = dest, *sp = (char *)src;
	while (*(dp+1)) dp++;
	while (*(sp+1)) *(dp++) = *(sp++);
	return dest;
}

char *strchr(const char *s, int c)
{
	while (*s != (char)c)
		if (!*s++) return NULL;

	return (char *)s;
}

int strcmp(const char *a, const char *b)
{
	int pos = 0;
	while (a[pos] != '\0') {
		if (b[pos] == '\0') return 1;
		else if (a[pos] < b[pos]) return -1;
		else if (a[pos] > b[pos]) return 1;
		pos++;
	}

	return 0;
}

char *strcpy(char *dest, const char *src)
{
	int pos = 0;

	while (1) {
		dest[pos] = src[pos];
		if (!dest[pos]) break;
		pos++;
	}

	return dest;
}

size_t strlen(const char *str)
{
	size_t n = 0;
	while (str[n+1]) n++;
	return n;
}

char *strstr(const char *haystack, const char *needle)
{
	char *hpos = (char *)haystack;

	if (!*needle) return (char *)haystack;
	while (*hpos && strlen(hpos) >= strlen(needle)) {
		char *a = hpos, *b = (char *)needle;
		while (*a && *b && *a == *b) {
			a++;
			b++;
		}

		if (*b == '\0')
			return hpos;

		hpos++;
	}

	return NULL;
}

/*
char *strtok(char *str, const char *delim)
{
	return NULL;
}

unsigned long strtoul(char *nptr, char **endptr, int base)
{
	return 0;
}
*/


