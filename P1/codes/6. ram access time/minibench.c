#include <stdio.h>
#include <stdlib.h>
#define SIZE_1KB (1<<7)
#define ASIZE (SIZE_1KB*size_itr)
#define MAX_SIZE (1<<15)


#define re_read_max 10000 

typedef long long uint64_t;

int main()
{
	unsigned cycles_high, cycles_high1, cycles_low, cycles_low1;
	long long i,j;
	long long * p;
	
	int k, size_itr=0, t=1, s=0, re_read, return_val, multiplier_size, m_i;
	FILE * result = fopen("result.txt", "w+");
	if (result==NULL)
	{
		printf("\nCannot open output file. \n");
		exit(0);
	}

	uint64_t start, end;
	int st =0;

	//for(size_itr=3072; size_itr<=3073; size_itr*=2){
	for(size_itr=8; size_itr<=MAX_SIZE; size_itr*=2){
		fprintf(result, "\nSize = %dkB, ", size_itr);

		for(st=1;st<ASIZE;st*=2)
		{
			printf("\nSize = %dkB", size_itr);
			printf("\tstride = %d",st); 

			long long *arr = (long long *) malloc(ASIZE * sizeof(long long));
			int steps = 80000;//64 * 1024 * 1024; // Arbitrary number of steps
			long long lengthMod = ASIZE - 1;

			for(i=0;i<ASIZE;i+=st) {
				arr[i]=(long long)&arr[(i+st) & lengthMod];
			}

			p = &arr[0];

				asm volatile ("cpuid\n\t"
								"rdtsc\n\t"
								"mov %%edx, %0\n\t"
								"mov %%eax, %1\n\t"
								: "=r" (cycles_high), "=r" (cycles_low)
								:: "%rax", "%rbx", "%rcx", "%rdx");

				for(i=0; i<steps; i++){
					p=(long long *)*p;
				}

				asm volatile ("rdtscp\n\t"
								"mov %%edx, %0\n\t"
								"mov %%eax, %1\n\t"
								"cpuid\n\t"
								: "=r" (cycles_high1), "=r" (cycles_low1)
								:: "%rax", "%rbx", "%rcx", "%rdx");

			start = ( ((uint64_t)cycles_high << 32) | cycles_low );
			end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );

			fprintf(result, "%llu, ", (end-start)/(steps));

			free(arr);			

		}
	}

	return return_val;
}
