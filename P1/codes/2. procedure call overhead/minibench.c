#include<stdio.h>
typedef long long uint64_t;
void foo(){
}
void foo1(int k){
}

void foo2(int i, int j){
}
void foo3( int i, int j, int k){
}

int main()
{
	unsigned cycles_high, cycles_high1, cycles_low, cycles_low1;
	uint64_t start, end;

	asm volatile ("cpuid\n\t"
		"rdtsc\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		: "=r" (cycles_high), "=r" (cycles_low)
		:: "%rax", "%rbx", "%rcx", "%rdx");

	// Enter Code here
	foo2(1729,1729);//Ramanujan Number: Aditya's request.
	asm volatile ("rdtscp\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		"cpuid\n\t"
		: "=r" (cycles_high1), "=r" (cycles_low1)
		:: "%rax", "%rbx", "%rcx", "%rdx");

	start = ( ((uint64_t)cycles_high << 32) | cycles_low );
	end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
	printf("%llu \n", (end-start));

	return 0;

}
