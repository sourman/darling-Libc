#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
 * Symbols Chromium's Comet Framework binds from libSystem that this libc
 * does not otherwise export. The bodies are enough for dyld to finish
 * loading; they are not a sandbox or responsibility implementation.
 */

void comet_atomic_load(size_t size, void *ptr, void *ret, int model) __asm__("___atomic_load");
void comet_atomic_store(size_t size, void *ptr, void *val, int model) __asm__("___atomic_store");

void comet_atomic_load(size_t size, void *ptr, void *ret, int model)
{
	volatile unsigned char *src = ptr;
	volatile unsigned char *dst = ret;
	size_t i;

	(void)model;
	for (i = 0; i < size; i++)
		dst[i] = src[i];
}

void comet_atomic_store(size_t size, void *ptr, void *val, int model)
{
	volatile unsigned char *dst = ptr;
	volatile unsigned char *src = val;
	size_t i;

	(void)model;
	for (i = 0; i < size; i++)
		dst[i] = src[i];
}

void memset_pattern16(void *b, const void *pattern16, size_t len)
{
	unsigned char *dst = b;
	const unsigned char *pat = pattern16;
	size_t i;

	for (i = 0; i < len; i++)
		dst[i] = pat[i & 15];
}

int64_t sandbox_extension_consume(const char *extension_token)
{
	(void)extension_token;
	return 0;
}

int sandbox_extension_release(int64_t extension_handle)
{
	(void)extension_handle;
	return 0;
}

char *sandbox_extension_issue_file(const char *extension_class, const char *path, uint32_t flags)
{
	(void)extension_class;
	(void)path;
	(void)flags;
	return strdup("");
}

int responsibility_get_pid_responsible_for_pid(int pid, int *responsible_pid)
{
	if (responsible_pid)
		*responsible_pid = pid;
	return 0;
}

int responsibility_spawnattrs_setdisclaim(void *attrs, int disclaim)
{
	(void)attrs;
	(void)disclaim;
	return 0;
}
