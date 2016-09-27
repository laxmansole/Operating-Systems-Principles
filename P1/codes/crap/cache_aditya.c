#include <stdio.h>
#include <stdlib.h>

#define SIZE_1KB (1<<8)
//#define ASIZE (SIZE_1KB*size_itr)
#define ASIZE sizes[size_itr]
#define MAX_SIZE ((1<<13)+1)
#define SIZE_1MB (1<<18)

#define re_read_max 500000
#define stride 32

typedef long long uint64_t;

int main()
{
	unsigned cycles_high, cycles_high1, cycles_low, cycles_low1;
	long long i,j;

	int sizes[] = {
		1*SIZE_1KB, 2*SIZE_1KB, 4*SIZE_1KB, 8*SIZE_1KB, 16*SIZE_1KB, 24*SIZE_1KB, 32*SIZE_1KB, 48*SIZE_1KB, 64*SIZE_1KB, 128*SIZE_1KB, 
		240*SIZE_1KB, 256*SIZE_1KB, 270*SIZE_1KB, 300*SIZE_1KB, 450*SIZE_1KB, 512*SIZE_1KB, 550*SIZE_1KB,
		1*SIZE_1MB, 2*SIZE_1MB, 3*SIZE_1MB, 4*SIZE_1MB, 5*SIZE_1MB, 6*SIZE_1MB, 8*SIZE_1MB, 10*SIZE_1MB, 12*SIZE_1MB, 16*SIZE_1MB
	}
	int total_config = 27;
	
	int k, size_itr=0, t=1, s=0, re_read, return_val, multiplier_size, m_i;
	
	// FILE Open
	FILE * result = fopen("result.txt", "w+");
	if (result==NULL)
	{
		printf("\nCannot open output file. \n");
		exit(0);
	}

	uint64_t start, end;

	for(size_itr=1; size_itr<27; size_itr++){
		
		/*if(size_itr == ((1<<t)*(1+s)) ){
			printf("\nSize = %d\n", ((1<<t)*(1+s)));
			t = (t<15) ? t+1 : t;
			s = (t<15) ? s : s+1;
		}*/
		printf("\nSize = %d\n",sizes[size_itr]/SIZE_1KB);

		fprintf(result, "\nSize = %d,", sizes[size_itr]/SIZE_1KB);
		int *a = (int *) malloc(ASIZE * sizeof(int));

/*		// This is the stride multiplier. 
		multiplier_size = ASIZE/stride;
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
*/
		// Read, Write.
	    for(i=0;i<1;i++) {
			if(i==0) { 
				//printf("\n\twritting..... ");
				asm volatile ("cpuid\n\t"
							"rdtsc\n\t"
							"mov %%edx, %0\n\t"
							"mov %%eax, %1\n\t"
							: "=r" (cycles_high), "=r" (cycles_low)
							:: "%rax", "%rbx", "%rcx", "%rdx");
				
				for(re_read=0; re_read<re_read_max; re_read++){
					for(j=0;j<ASIZE/stride;j+=1)
					{				
						a[stride*j]=j;
					}
					for(j=0;j<ASIZE/stride;j+=1)
					//for(j=0;j<multiplier_size;j+=1)
					{				
						//k+=a[stride*multiplier[j]];
						k+=a[stride*j];
					}
				}
				
				asm volatile ("rdtscp\n\t"
						"mov %%edx, %0\n\t"
						"mov %%eax, %1\n\t"
						"cpuid\n\t"
						: "=r" (cycles_high1), "=r" (cycles_low1)
						:: "%rax", "%rbx", "%rcx", "%rdx");
			
					start = ( ((uint64_t)cycles_high << 32) | cycles_low );
					end =	(((uint64_t)cycles_high1 << 32) | cycles_low1);
					fprintf(result, "%llu,", (end-start)/(re_read_max));
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
		free(a);
		//free(multiplier);
	}

	return return_val;
}
