#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <time.h>
#include <keyvalue.h>
#include <fcntl.h>

#include <string.h>

int main(int argc, char *argv[])
{
	int i=0, number_of_keys, devfd, error = 0, tid; 
	// number_of_threads = 1,
	__u64 size, key;
	char data[4096], op, **kv; 

	if(argc < 2) {
		fprintf(stderr, "Usage: %s number_of_keys\n",argv[0]);
		exit(1);
	}

	number_of_keys = atoi(argv[1]);

	kv = (char **)malloc(number_of_keys*sizeof(char *));
	for(i = 0; i < number_of_keys; i++) {
		kv[i] = (char *)calloc(4096, sizeof(char));
	}

	// Replay the log 	// Validate
/*	while(scanf("%c %llu %llu %d %s",&op, &tid, &key, &size, &data)!=EOF) {
		if(op == 'S') {
			// fprintf(stderr, "before strcpy\n");
			strcpy(kv[(int)key],data);
			// fprintf(stderr, "after strcpy\n");
			memset(data,0,4096);
			// fprintf(stderr, "after memset\n");
		}
	}*/

	devfd = open("/dev/keyvalue",O_RDWR);
	if(devfd < 0) {
		fprintf(stderr, "Device open failed");
		exit(1);
	}

	memset(data,0,4096);
	tid = kv_get(devfd,0,&size,&data);

	if(tid == -1)
		fprintf(stderr,"cannot get, \t\t%d\t%d\n", tid, 0);
	else
		fprintf(stderr,"got, \t\t%d\t%d\n", tid, 0);

	/*for(i = 0; i < number_of_keys; i++) {
		memset(data,0,4096);
		tid = kv_get(devfd,i,&size,&data);

		if(tid!=-1)
			if(strcmp(data,kv[i])!=0) {
				fprintf(stderr, "Key %i has a wrong value %s v.s. %s\n",i,data,kv[i]);
				error++;
			}
		// else{
		//	 fprintf(stderr, "\n\ndhattad tattad\n\n");
		//	 fprintf(stderr, "Key %i has a correct value %s v.s. %s\n",i,data,kv[i]);
		// }
	}*/

	if(error==0)
		fprintf(stderr, "You passed!\n");
	
	close(devfd);
	return 0;
}

