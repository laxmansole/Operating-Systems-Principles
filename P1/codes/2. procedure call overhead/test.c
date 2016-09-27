#include<stdio.h>
typedef long long uint64_t;

#ifndef _foo0_DEFINED 
#define _foo0_DEFINED 0
#endif

#ifndef _foo1_DEFINED 
#define _foo1_DEFINED 0
#endif

#ifndef _foo2_DEFINED 
#define _foo2_DEFINED 0
#endif

#ifndef _foo3_DEFINED 
#define _foo3_DEFINED 0
#endif

#ifndef _foo4_DEFINED 
#define _foo4_DEFINED 0
#endif

#ifndef _foo5_DEFINED 
#define _foo5_DEFINED 0
#endif

#ifndef _foo6_DEFINED 
#define _foo6_DEFINED 0
#endif

#ifndef _foo7_DEFINED 
#define _foo7_DEFINED 0
#endif


typedef struct mystruct
{	
	char buf[10000];
	int arr[10000];
	long long larr[1000];
}mystruct;

void foo(){
}

void foo1(mystruct k){
}

void foo2(mystruct i, mystruct j){
}

void foo3(mystruct i, mystruct j, mystruct k){
}

void foo4(mystruct i, mystruct j, mystruct k, mystruct l){
}

void foo5(mystruct i, mystruct j, mystruct k, mystruct l, mystruct m ){
}

void foo6(mystruct i, mystruct j, mystruct k, mystruct l, mystruct m, mystruct n) {
}

void foo7(mystruct i, mystruct j, mystruct k, mystruct l, mystruct m, mystruct n, mystruct o){
}

int main()
{
	unsigned cycles_high, cycles_high1, cycles_low, cycles_low1;
	uint64_t start, end;

	mystruct m1;


#if _foo0_DEFINED
	asm volatile ("cpuid\n\t"
		"rdtsc\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		: "=r" (cycles_high), "=r" (cycles_low)
		:: "%rax", "%rbx", "%rcx", "%rdx");

	// Enter Code here	
	foo();

	asm volatile ("rdtscp\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		"cpuid\n\t"
		: "=r" (cycles_high1), "=r" (cycles_low1)
		:: "%rax", "%rbx", "%rcx", "%rdx");

	start = ( ((uint64_t)cycles_high << 32) | cycles_low );
	end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
	printf("\n%llu, ", (end-start));
#endif

/***********************************************************************/


#if _foo1_DEFINED
	asm volatile ("cpuid\n\t"
		"rdtsc\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		: "=r" (cycles_high), "=r" (cycles_low)
		:: "%rax", "%rbx", "%rcx", "%rdx");

	// Enter Code here
	foo1(m1) ;//Ramanujan Number: Aditya's request.

	asm volatile ("rdtscp\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		"cpuid\n\t"
		: "=r" (cycles_high1), "=r" (cycles_low1)
		:: "%rax", "%rbx", "%rcx", "%rdx");

	start = ( ((uint64_t)cycles_high << 32) | cycles_low );
	end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
	printf("%llu, ", (end-start));
#endif

/***********************************************************************/


#if _foo2_DEFINED
	asm volatile ("cpuid\n\t"
		"rdtsc\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		: "=r" (cycles_high), "=r" (cycles_low)
		:: "%rax", "%rbx", "%rcx", "%rdx");

	// Enter Code here
	foo2(m1, m1) ;//Ramanujan Number: Aditya's request.

	asm volatile ("rdtscp\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		"cpuid\n\t"
		: "=r" (cycles_high1), "=r" (cycles_low1)
		:: "%rax", "%rbx", "%rcx", "%rdx");

	start = ( ((uint64_t)cycles_high << 32) | cycles_low );
	end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
	printf("%llu, ", (end-start));
#endif


/***********************************************************************/

#if _foo3_DEFINED
	asm volatile ("cpuid\n\t"
		"rdtsc\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		: "=r" (cycles_high), "=r" (cycles_low)
		:: "%rax", "%rbx", "%rcx", "%rdx");

	// Enter Code here
	foo3(m1, m1, m1) ;//Ramanujan Number: Aditya's request.

	asm volatile ("rdtscp\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		"cpuid\n\t"
		: "=r" (cycles_high1), "=r" (cycles_low1)
		:: "%rax", "%rbx", "%rcx", "%rdx");

	start = ( ((uint64_t)cycles_high << 32) | cycles_low );
	end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
	printf("%llu, ", (end-start));
#endif

/***********************************************************************/

#if _foo4_DEFINED
	asm volatile ("cpuid\n\t"
		"rdtsc\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		: "=r" (cycles_high), "=r" (cycles_low)
		:: "%rax", "%rbx", "%rcx", "%rdx");

	// Enter Code here
	foo4(m1, m1, m1, m1) ;//Ramanujan Number: Aditya's request.

	asm volatile ("rdtscp\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		"cpuid\n\t"
		: "=r" (cycles_high1), "=r" (cycles_low1)
		:: "%rax", "%rbx", "%rcx", "%rdx");

	start = ( ((uint64_t)cycles_high << 32) | cycles_low );
	end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
	printf("%llu, ", (end-start));
#endif

/***********************************************************************/

#if _foo5_DEFINED
	asm volatile ("cpuid\n\t"
		"rdtsc\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		: "=r" (cycles_high), "=r" (cycles_low)
		:: "%rax", "%rbx", "%rcx", "%rdx");

	// Enter Code here
	foo5(m1, m1, m1, m1, m1) ;//Ramanujan Number: Aditya's request.

	asm volatile ("rdtscp\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		"cpuid\n\t"
		: "=r" (cycles_high1), "=r" (cycles_low1)
		:: "%rax", "%rbx", "%rcx", "%rdx");

	start = ( ((uint64_t)cycles_high << 32) | cycles_low );
	end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
	printf("%llu, ", (end-start));
#endif

/***********************************************************************/

#if _foo6_DEFINED
	asm volatile ("cpuid\n\t"
		"rdtsc\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		: "=r" (cycles_high), "=r" (cycles_low)
		:: "%rax", "%rbx", "%rcx", "%rdx");

	// Enter Code here
	foo6(m1, m1, m1, m1, m1, m1) ;//Ramanujan Number: Aditya's request.

	asm volatile ("rdtscp\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		"cpuid\n\t"
		: "=r" (cycles_high1), "=r" (cycles_low1)
		:: "%rax", "%rbx", "%rcx", "%rdx");

	start = ( ((uint64_t)cycles_high << 32) | cycles_low );
	end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
	printf("%llu, ", (end-start));
#endif

/***********************************************************************/

#if _foo7_DEFINED
	asm volatile ("cpuid\n\t"
		"rdtsc\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		: "=r" (cycles_high), "=r" (cycles_low)
		:: "%rax", "%rbx", "%rcx", "%rdx");

	// Enter Code here
	foo7(m1, m1, m1, m1, m1, m1, m1) ;//Ramanujan Number: Aditya's request.

	asm volatile ("rdtscp\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		"cpuid\n\t"
		: "=r" (cycles_high1), "=r" (cycles_low1)
		:: "%rax", "%rbx", "%rcx", "%rdx");

	start = ( ((uint64_t)cycles_high << 32) | cycles_low );
	end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
	printf("%llu ", (end-start));
#endif

/***********************************************************************/
	return 0;

}
