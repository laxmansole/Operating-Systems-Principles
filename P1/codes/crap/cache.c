#include <stdio.h>
#include <stdlib.h>

#define SIZE_1KB (1<<8)
#define ASIZE (SIZE_1KB*size_itr)
#define MAX_SIZE (1<<13)

//#define MAX_SIZE 2

#define re_read_max 10000 
#define stride 16

typedef long long uint64_t;

int main()
{
	unsigned cycles_high, cycles_high1, cycles_low, cycles_low1;
	long long i,j;
	
	int k, size_itr=0, t=1, s=0, re_read, return_val, multiplier_size, m_i;
	// FILE Open
	FILE * result = fopen("result.txt", "w+");
	if (result==NULL)
	{
		printf("\nCannot open output file. \n");
		exit(0);
	}

	uint64_t start, end;

	for(size_itr=1; size_itr<MAX_SIZE; ((size_itr<1000)?(size_itr*=2):(size_itr=size_itr+1024)))
	{
		

		fprintf(result, "\nSize = %d,", size_itr);
		int *arr = (int *) malloc(ASIZE * sizeof(int));

		int steps = 64 * 1024 * 1024; // Arbitrary number of steps
		int lengthMod = ASIZE - 1;
			asm volatile ("cpuid\n\t"
							"rdtsc\n\t"
							"mov %%edx, %0\n\t"
							"mov %%eax, %1\n\t"
							: "=r" (cycles_high), "=r" (cycles_low)
							:: "%rax", "%rbx", "%rcx", "%rdx");
				
		for ( i = 0; i < steps; i++)
		{

			arr[(i * 16) & lengthMod]++; // (x & lengthMod) is equal to (x % arr.Length)
		}
	asm volatile ("rdtscp\n\t"
					"mov %%edx, %0\n\t"
					"mov %%eax, %1\n\t"
					"cpuid\n\t"
					: "=r" (cycles_high1), "=r" (cycles_low1)
					:: "%rax", "%rbx", "%rcx", "%rdx");
			
			start = ( ((uint64_t)cycles_high << 32) | cycles_low );
			end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
			fprintf(result, "%llu\n", (end-start));
	     
		free(arr);
	}

	return return_val;
}
