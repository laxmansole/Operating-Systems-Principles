#include <stdio.h>
#include <unistd.h>

// This is read

typedef long long uint64_t;

int main()
{
	unsigned cycles_high, cycles_high1, cycles_low, cycles_low1;
	uint64_t start, end, start_read_child=0, start_write_child=0, start_read_parent=0, start_write_parent=0;

	int pdes[2], pdes2[2];
	int i,is_child;
	char buf[100], buf2[100];
	 
	pipe(pdes);
	pipe(pdes2);

	is_child = fork();

	for(i=0; i<10; i++){
		if ( is_child == 0 ){
				close(pdes[1]);

				asm volatile ("cpuid\n\t"
					"rdtsc\n\t"
					"mov %%edx, %0\n\t"
					"mov %%eax, %1\n\t"
					: "=r" (cycles_high), "=r" (cycles_low)
					:: "%rax", "%rbx", "%rcx", "%rdx");
	
				read(pdes[0], &start_read_child, sizeof(uint64_t));
	
				asm volatile ("rdtscp\n\t"
					"mov %%edx, %0\n\t"
					"mov %%eax, %1\n\t"
					"cpuid\n\t"
					: "=r" (cycles_high1), "=r" (cycles_low1)
					:: "%rax", "%rbx", "%rcx", "%rdx");
	
				start_write_child = ( ((uint64_t)cycles_high << 32) | cycles_low );
				end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
				printf("We are in child. Cycles measured = %llu\n",(end-start_write_child));
	
				close(pdes2[0]);
				write(pdes2[1], &start_write_child, sizeof(uint64_t));
	
			} else{
				close(pdes[0]);
				write(pdes[1], &start_write_parent, sizeof(uint64_t));
				close(pdes2[1]);
				read(pdes2[0], &start_read_parent, sizeof(uint64_t));
			}
	}
	return 0;
}
