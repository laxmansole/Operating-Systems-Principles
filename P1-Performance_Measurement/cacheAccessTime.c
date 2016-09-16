#include<stdio.h>
#define ASIZE 1572864
typedef long long uint64_t;
int main()
{
	unsigned cycles_high, cycles_high1, cycles_low, cycles_low1;
	unsigned int a[ASIZE];
	long long i,j;
	int k;	
	uint64_t start, end;
    for(i=0;i<2;i++)
	{
		if(i==0)
		{ 
		printf("\n writting.....\n\n");
			for(j=0;j<ASIZE;j++)
			{
				asm volatile ("cpuid\n\t"
					"rdtsc\n\t"
					"mov %%edx, %0\n\t"
					"mov %%eax, %1\n\t"
					: "=r" (cycles_high), "=r" (cycles_low)
					:: "%rax", "%rbx", "%rcx", "%rdx");
				a[j]=j;	
				asm volatile ("rdtscp\n\t"
					"mov %%edx, %0\n\t"
					"mov %%eax, %1\n\t"
					"cpuid\n\t"
					: "=r" (cycles_high1), "=r" (cycles_low1)
					:: "%rax", "%rbx", "%rcx", "%rdx");
		
				start = ( ((uint64_t)cycles_high << 32) | cycles_low );
				end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
				printf("%llu \n", (end-start));
			}
		}
		else
		{
		printf("\n reading.....\n\n");
			for(j=0;j<ASIZE;j++)
			{
				asm volatile ("cpuid\n\t"
					"rdtsc\n\t"
					"mov %%edx, %0\n\t"
					"mov %%eax, %1\n\t"
					: "=r" (cycles_high), "=r" (cycles_low)
					:: "%rax", "%rbx", "%rcx", "%rdx");
				
					k+=a[j];	
				asm volatile ("rdtscp\n\t"
					"mov %%edx, %0\n\t"
					"mov %%eax, %1\n\t"
					"cpuid\n\t"
					: "=r" (cycles_high1), "=r" (cycles_low1)
					:: "%rax", "%rbx", "%rcx", "%rdx");
		
				start = ( ((uint64_t)cycles_high << 32) | cycles_low );
				end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
				printf("%llu\n", (end-start));
			}

		}
	}
		return k;
}
