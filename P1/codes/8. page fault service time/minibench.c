#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>

typedef long long uint64_t;
int main(int argc, char ** argv) {

  unsigned cycles_high, cycles_high1, cycles_low, cycles_low1;
  uint64_t start, end;
  //int fd = open(argv[1], O_RDONLY);
  int fd = open("../input/pop.txt", O_RDONLY);
  struct stat stats;
  fstat(fd, &stats);
  posix_fadvise(fd, 0, stats.st_size, POSIX_FADV_DONTNEED);
  char * map = (char *) mmap(NULL, stats.st_size, PROT_READ, MAP_SHARED, fd, 0);
  if (map == MAP_FAILED) {
    perror("Failed to mmap");
    return 1;
  }
  int result = 0;
  int i;
  for (i = 0; i < 9; i++) {
    
	asm volatile ("cpuid\n\t"
		"rdtsc\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		: "=r" (cycles_high), "=r" (cycles_low)
		:: "%rax", "%rbx", "%rcx", "%rdx");


		result += map[i*1024*1024];
	asm volatile ("rdtscp\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		"cpuid\n\t"
		: "=r" (cycles_high1), "=r" (cycles_low1)
		:: "%rax", "%rbx", "%rcx", "%rdx");
	start = ( ((uint64_t)cycles_high << 32) | cycles_low );
	end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
	printf("Page fault service time - %llu \n",(end-start));
  }
	//printf("%d result= %d\n",stats.st_size,result);
  munmap(map, stats.st_size);
  return result;
}
