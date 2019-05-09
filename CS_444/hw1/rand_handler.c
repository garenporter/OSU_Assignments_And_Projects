#include "rdrand.h"
#include "mt19937.h"
#include <stdio.h>
#include <time.h>
#include <limits.h>

#define RDRAND 1
#define MT19937 0

int rand_choice(){

    unsigned int eax;
    unsigned int ebx;
    unsigned int ecx;
    unsigned int edx;

    char vendor[13];
    
    eax = 0x01;

    __asm__ __volatile__(
                         "cpuid;"
                         : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
                         : "a"(eax)
                         );
    
    if(ecx & 0x40000000){
        return RDRAND;
    }
    return MT19937;
}

int get_rand(int alg){
	if(alg == MT19937){
	    unsigned long val = genrand_int32();
	    return (int) val & INT_MAX;

	} else {
		uint64_t val;
		rdseed64_step(&val);
		return (int) val & INT_MAX;
	}
}

void seed_rand(int alg){

	unsigned long seed = (unsigned long) time(0);
	if(alg == MT19937){
	    init_genrand(seed);
	} else {
		rdseed64_step(&seed);
	}
}
