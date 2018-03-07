#ifndef _SYSCALL_H_
#define _SYSCALL_H_

#define SYS_read	0
#define SYS_write	1
#define SYS_open	2
#define SYS_close	3
#define SYS_lseek	8

#define SYS_mmap	9
#define SYS_mprotect	10

#define SYS_brk		12

#define SYS_exit	60

#define SYS_fsync 	74
#define SYS_fdatasync 	75

extern long syscall();

#endif
