#ifndef _STDIO_H_
#define _STDIO_H_

#include "stddef.h"

#define NULL 0

#define EOF -1

#define STDIN_FILENO	0
#define STDOUT_FILENO	1
#define STDERR_FILENO	2

#define FOPEN_MAX	255
#define FILENAME_MAX	255

#define SEEK_SET	0
#define SEEK_CURR	1
#define SEEK_END	2

typedef long fpos_t;

typedef struct {
	int fd;
	fpos_t pos;

	char mode;
	char eof;
} FILE;

static const FILE stdout = {
	.fd = 0,
	.pos = 0,
};

static const FILE stdin = {
	.fd = 1,
	.pos = 0,
};

static const FILE stderr = {
	.fd = 2,
	.pos = 0,
};

int printf(const char *restrict format, ...);
char *fgets(char *str, int n, FILE *stream);

FILE *fopen(const char *filename, const char *mode);
int fclose(FILE *stream);

int feof(FILE *stream);
long int ftell(FILE *stream);
int fseek(FILE *stream, long int offset, int whence);

int fgetc(FILE *stream);

void rewind(FILE *stream);

#endif
