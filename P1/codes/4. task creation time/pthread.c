#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

typedef long long uint64_t;

void *thread_func(){
}

int main()
{
	unsigned cycles_high, cycles_high1, cycles_low, cycles_low1;
	uint64_t start, end;

	pthread_t m;

		asm volatile ("rdtscp\n\t"
			"mov %%edx, %0\n\t"
			"mov %%eax, %1\n\t"
			"cpuid\n\t"
			: "=r" (cycles_high), "=r" (cycles_low)
			:: "%rax", "%rbx", "%rcx", "%rdx");

		// Code here
		pthread_create(&m, NULL, thread_func, NULL);

		asm volatile ("cpuid\n\t"
			"rdtsc\n\t"
			"mov %%edx, %0\n\t"
			"mov %%eax, %1\n\t"
			: "=r" (cycles_high1), "=r" (cycles_low1)
			:: "%rax", "%rbx", "%rcx", "%rdx");

		start = ( ((uint64_t)cycles_high << 32) | cycles_low );
		end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
		printf("%llu\n",(end-start));

		/*if(pthread_join(m, NULL)) {
			printf("Error joining thread\n");
			return 2;
		}*/


	return 0;
}
