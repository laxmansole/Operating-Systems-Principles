#include <stdio.h>
#include <unistd.h>

typedef long long uint64_t;

int main()
{
	unsigned cycles_high, cycles_high1, cycles_low, cycles_low1;
	uint64_t start, end;

	int pdes[2] = {10, 20};
	char buf[100];
	 
	asm volatile ("cpuid\n\t"
		"rdtsc\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		: "=r" (cycles_high), "=r" (cycles_low)
		:: "%rax", "%rbx", "%rcx", "%rdx");

	// Enter Code here
	//pipe(pdes);
	getpid();

	asm volatile ("rdtscp\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		"cpuid\n\t"
		: "=r" (cycles_high1), "=r" (cycles_low1)
		:: "%rax", "%rbx", "%rcx", "%rdx");

	start = ( ((uint64_t)cycles_high << 32) | cycles_low );
	end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
	printf("%llu, ", (end-start));

	int is_child = fork();

	if ( is_child == 0 ){
		// close(pdes[1]); 
		// read(pdes[0], buf, 100); 									/* read from parent */
		//printf("This is the child with pid = %d and is_child = %d\n", getpid(), is_child);
	} else{
		// close(pdes[0]); 
		// write(pdes[1], "this is written\n", 16); 					/* write to child */
		//printf("This is the parent with pid = %d and is_child = %d\n", getpid(), is_child);
	}

	return 0;
}
