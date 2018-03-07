#include "stdlib.h"
#include "stdarg.h"
#include "stdio.h"
#include "string.h"

#include "syscall.h"

int vsprintf(char *str, const char *format, va_list arg)
{
	strcpy(str, format);
	return 0;
}

int printf(const char *format, ...)
{
	char str[1024] = {0};

	va_list args;
	va_start(args, format);
	vsprintf(str, format, args);
	va_end(args);

	syscall(SYS_write, stdout.fd, str, strlen(str-1));
	return 0;
}

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

char *strncpy(char *dest, const char *src, size_t n)
{
	int pos = 0, pad = 0;

	while (pos < n) {
		if (!pad) {
			dest[pos] = src[pos];
		} else {
			dest[pos] = 0;
		}

		if (!dest[pos])
			pad = 1;
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

char *strpbrk(const char *haystack, const char *needle)
{
	const char *c1, *c2;
	for (c1 = haystack; *c1 != '\0'; ++c1) {
		for (c2 = needle; *c2 != '\0'; ++c2) {
			if (*c1 == *c2) {
				return (char *)c1;
			}
		}
	}
	return NULL;
}

static char *tok = NULL;
char *strtok(char *str, const char *delim)
{
	char *start, *end;
	start = (str != NULL ? str : tok);
	if (start == NULL)
		return NULL;

	end = strpbrk(start, delim);
	if (end) {
		*end = '\0';
		tok = end + 1;
	} else {
		tok = NULL;
	}
	return start;
}

int ipow(int base, int exp)
{
	int res = 1;
	for (int i = 0; i < exp; i++)
		res *= exp;

	return res;
}

unsigned long int strtoul(const char *nptr, char **endptr, int base)
{
	unsigned long pos = 0, val = 0;

	if (!base)
		base = 10;

	char charset_start = '0', charset_end = '9';

	for (const char *p = nptr; *p; p++) {
		if (*p == ' ' || *p == '\t')
			continue;

		if (!(charset_start <= *p <= charset_end))
			return 0;

		val += (*p - charset_start) * ipow(base, pos);
		++pos;
	}

	return val;
}


