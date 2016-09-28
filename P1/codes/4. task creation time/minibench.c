#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef long long uint64_t;

int main()
{
	unsigned cycles_high, cycles_high1, cycles_low, cycles_low1;
	uint64_t start, end;

	int pdes[2] = {10, 20};
	int is_child, status;
	char buf[100];
	 
	pipe(pdes);

	asm volatile ("cpuid\n\t"
		"rdtsc\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		: "=r" (cycles_high), "=r" (cycles_low)
		:: "%rax", "%rbx", "%rcx", "%rdx");

	is_child = fork();

	if(is_child != 0){

		wait(&status);
		asm volatile ("rdtscp\n\t"
			"mov %%edx, %0\n\t"
			"mov %%eax, %1\n\t"
			"cpuid\n\t"
			: "=r" (cycles_high1), "=r" (cycles_low1)
			:: "%rax", "%rbx", "%rcx", "%rdx");
	
		start = ( ((uint64_t)cycles_high << 32) | cycles_low );
		end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
		printf("%llu\n", (end-start));
	} else{
		exit(0);
	}
	
	return 0;
}