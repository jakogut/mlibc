#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include "syscall.h"

#include <fcntl.h>

FILE *fopen(const char *path, const char *mode)
{
	int o_flags = 0;

	size_t mode_size = strlen(mode);
	for (int i = 0; i < mode_size; i++) {
		switch(mode[i]) {
			case 'r':
				if (i < mode_size-1 && mode[i+1] == '+')
					o_flags = O_RDWR;
				else
					o_flags = O_RDONLY;
				break;
			case 'w':
				if (i < mode_size-1 && mode[i+1] == '+')
					o_flags = O_RDWR;
				else
					o_flags = O_WRONLY;

				o_flags |= O_TRUNC | O_CREAT;
				break;
			case 'a':
				if (i < mode_size-1 && mode[i+1] == '+')
					o_flags = O_WRONLY | O_APPEND;
				else
					o_flags = O_RDWR | O_APPEND;

				o_flags |= O_CREAT;
				break;
		};
	}

	FILE *stream = malloc(sizeof(FILE));
	stream->fd = syscall(SYS_open, path, o_flags);
	stream->eof = 0;

	return stream;
}

int fclose(FILE *stream)
{
	syscall(SYS_close, stream->fd);
	free(stream);
	return 0;
}

int feof(FILE *stream)
{
	return stream->eof;
}

long int ftell(FILE *stream)
{
	return stream->pos;
}

int fseek(FILE *stream, long int offset, int whence)
{
	if (whence == SEEK_SET) {
		syscall(SYS_lseek, stream->fd, offset, whence);
		stream->pos = offset;
		stream->eof = 0;
	} else {
		return -1;
	}
	// tinyvm doesn't need other origins
	return 0;
}

int fgetc(FILE *stream)
{
	char buf;
	int read = syscall(SYS_read, stream->fd, &buf, 1);
	if (!read)
		stream->eof = 1;
	else
		stream->pos += read;
	return (int)buf;
}

char *fgets(char *str, int num, FILE *stream)
{
	return NULL;
}

int fputs(const char *str, FILE *stream)
{
	return 0;
}
