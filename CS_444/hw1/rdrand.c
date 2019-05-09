#include <stdint.h> 

int rdseed64_step (uint64_t *seed)
{
	unsigned char ok;

	asm volatile ("rdseed %0; setc %1"
		: "=r" (*seed), "=qm" (ok));

	return (int) ok;
}

int rdrand64_step (uint64_t *rand)
{
	unsigned char ok;

	asm volatile ("rdrand %0; setc %1"
		: "=r" (*rand), "=qm" (ok));

	return (int) ok;
}

