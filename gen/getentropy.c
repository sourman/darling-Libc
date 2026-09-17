/*
 * POSIX getentropy(3). Darwin's vintage libsystem_c only ships
 * $ld$weak$os10.11$_getentropy; the syscall lives in libsystem_kernel.
 * Fill at most 256 bytes via getentropy(2). Do not open /dev/urandom.
 */
#include <errno.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>

#ifndef SYS_getentropy
#define SYS_getentropy 500
#endif

int
getentropy(void *buf, size_t buflen)
{
	if (buflen > 256) {
		errno = EINVAL;
		return -1;
	}
	return syscall(SYS_getentropy, buf, buflen);
}
