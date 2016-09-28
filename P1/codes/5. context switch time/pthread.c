#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

typedef long long uint64_t;

unsigned cycles_high, cycles_high1, cycles_low, cycles_low1;
int pdes[2], pdes2[2];
char buf[100], buf2[100];
int done=0;

void *thread_func(){

	long long ti, tj, tk;
	printf("\nThis is the new thread. :)\nSad fact, going to die.\n\n");
	close(pdes[1]);
	read(pdes[0], buf, 8);

}

int main()
{
	uint64_t start, end;

	pipe(pdes);
	pipe(pdes2);

	pthread_t mythread;
	if(pthread_create(&mythread, NULL, thread_func, NULL)){
		printf("\nThread not created. Exiting\n");
		exit(0);
	} else {
		printf("\nThread created.\n");
	}

		// Code here
		close(pdes[0]);

		asm volatile ("cpuid\n\t"
			"rdtsc\n\t"
			"mov %%edx, %0\n\t"
			"mov %%eax, %1\n\t"
			: "=r" (cycles_high), "=r" (cycles_low)
			:: "%rax", "%rbx", "%rcx", "%rdx");

		write(pdes[1], "string.", 8);

		pthread_join(mythread, NULL);

		asm volatile ("cpuid\n\t"
			"rdtsc\n\t"
			"mov %%edx, %0\n\t"
			"mov %%eax, %1\n\t"
			: "=r" (cycles_high1), "=r" (cycles_low1)
			:: "%rax", "%rbx", "%rcx", "%rdx");

		start = ( ((uint64_t)cycles_high << 32) | cycles_low );
		end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
		printf("check this out %llu\n",(end-start));

	return 0;
}
