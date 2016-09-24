#include <stdio.h>
#include <stdlib.h>

#define SIZE_1KB (1<<8)
#define ASIZE (SIZE_1KB*size_itr)
#define MAX_SIZE (1<<9)

//#define MAX_SIZE 2

#define re_read_max 1
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

	for(size_itr=1; size_itr<MAX_SIZE; size_itr++){
		
		if(size_itr == ((1<<t)*(1+s)) ){
			printf("\nSize = %d\n", ((1<<t)*(1+s)));
			t = (t<7) ? t+1 : t;
			s = (t<7) ? s : s+1;
		}

		fprintf(result, "\nSize = %d,", size_itr);
		int *a = (int *) calloc(ASIZE, sizeof(int));

		// This is the stride multiplier. 
		multiplier_size = ASIZE/16;
		//printf("\nSize = %d\tMultiplier_size = %d\t", ASIZE, multiplier_size);

		int *multiplier = (int *)calloc(multiplier_size, sizeof(int));
		for(m_i=0; m_i<multiplier_size; m_i++)
			multiplier[m_i] = m_i;

		for(m_i=0; m_i<multiplier_size; m_i++){
			int temp = multiplier[m_i];
			int random_index = rand() % multiplier_size;

			multiplier[m_i] = multiplier[random_index];
			multiplier[random_index] = temp;
		}

		// Read, Write.
	    for(i=0;i<2;i++) {
			if(i==0) { 
				//printf("\n\twritting..... ");
				asm volatile ("cpuid\n\t"
							"rdtsc\n\t"
							"mov %%edx, %0\n\t"
							"mov %%eax, %1\n\t"
							: "=r" (cycles_high), "=r" (cycles_low)
							:: "%rax", "%rbx", "%rcx", "%rdx");
				
				for(re_read=0; re_read<re_read_max; re_read++){
					for(j=0;j<multiplier_size;j+=1)
					{				
						k+=a[16*multiplier[j]];
					}
				}
				
				asm volatile ("rdtscp\n\t"
						"mov %%edx, %0\n\t"
						"mov %%eax, %1\n\t"
						"cpuid\n\t"
						: "=r" (cycles_high1), "=r" (cycles_low1)
						:: "%rax", "%rbx", "%rcx", "%rdx");
			
					start = ( ((uint64_t)cycles_high << 32) | cycles_low );
					end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
					fprintf(result, "%llu,", (end-start)/(multiplier_size));
			} 
			else {
				//printf("\n\treading.....");
	
				asm volatile ("cpuid\n\t"
							"rdtsc\n\t"
							"mov %%edx, %0\n\t"
							"mov %%eax, %1\n\t"
							: "=r" (cycles_high), "=r" (cycles_low)
							:: "%rax", "%rbx", "%rcx", "%rdx");
				for(re_read=0; re_read<re_read_max; re_read++){
					for(j=0;j<multiplier_size;j+=1)
					{				
						a[j]=j;
					}
				}
				asm volatile ("rdtscp\n\t"
						"mov %%edx, %0\n\t"
						"mov %%eax, %1\n\t"
						"cpuid\n\t"
						: "=r" (cycles_high1), "=r" (cycles_low1)
						:: "%rax", "%rbx", "%rcx", "%rdx");
			
					start = ( ((uint64_t)cycles_high << 32) | cycles_low );
					end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
					fprintf(result, "%llu", (end-start)/(multiplier_size));
	
	
			}
		}
		return_val+=k;
		//free(a);
	}

	return k;
}
