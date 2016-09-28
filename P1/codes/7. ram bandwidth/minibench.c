#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef long long uint64_t;
#define ARRSIZE 10*1024*1024 
int main()
{
	unsigned cycles_high, cycles_high1, cycles_low, cycles_low1;
	uint64_t start, end;
	int i;
	char *src_array;
	src_array=(char *)malloc(ARRSIZE*sizeof(char));
	char *dst_array;
	dst_array=(char *)malloc(ARRSIZE*sizeof(char));
	/*for(i=0;i<ARRSIZE;i++){
		src_array[i]=i;
	}*/
	//for(i=0;i<100;i++)printf("src[%d]= %d\n",i,src_array[i]);
	//for(i=0;i<100;i++)printf("dst[%d]= %d\n",i,dst_array[i]);
	//for(i=0;i<1000;i++)
	//{
		asm volatile ("cpuid\n\t"
			"rdtsc\n\t"
			"mov %%edx, %0\n\t"
			"mov %%eax, %1\n\t"
			: "=r" (cycles_high), "=r" (cycles_low)
			:: "%rax", "%rbx", "%rcx", "%rdx");
	
		// Enter Code here
		memset(src_array,50,ARRSIZE);
		asm volatile ("rdtscp\n\t"
			"mov %%edx, %0\n\t"
			"mov %%eax, %1\n\t"
			"cpuid\n\t"
			: "=r" (cycles_high1), "=r" (cycles_low1)
			:: "%rax", "%rbx", "%rcx", "%rdx");
	
		start = ( ((uint64_t)cycles_high << 32) | cycles_low );
		end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
		printf("%llu,", (end-start));
		//for(i=0;i<100;i++)printf("dst[%d]= %d\n",i,dst_array[i]);
	//}
	//for(i=0;i<1000;i++)
	//{
		asm volatile ("cpuid\n\t"
			"rdtsc\n\t"
			"mov %%edx, %0\n\t"
			"mov %%eax, %1\n\t"
			: "=r" (cycles_high), "=r" (cycles_low)
			:: "%rax", "%rbx", "%rcx", "%rdx");
	
		// Enter Code here
		memcpy(dst_array, src_array,ARRSIZE);
		asm volatile ("rdtscp\n\t"
			"mov %%edx, %0\n\t"
			"mov %%eax, %1\n\t"
			"cpuid\n\t"
			: "=r" (cycles_high1), "=r" (cycles_low1)
			:: "%rax", "%rbx", "%rcx", "%rdx");
	
		start = ( ((uint64_t)cycles_high << 32) | cycles_low );
		end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
		printf("%llu\n", (end-start));
	//	for(i=0;i<100;i++)printf("dst[%d]= %d\n",i,dst_array[i]);
	//}
	return 0;

}
