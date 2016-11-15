#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <time.h>
#include <keyvalue.h>
#include <fcntl.h>

#include <string.h>
#include <unistd.h>

#include <pthread.h>

int main(int argc, char *argv[])
{
	int i=0, number_of_keys, number_of_transactions, a, tid, devfd, updated_key=0, key, delete_this, number_of_threads;
	__u64 size;
	char data[1024]; 

	if(argc < 5) {
		fprintf(stderr, "Usage: %s number_of_keys number_of_transactions\n",argv[0]);
		exit(1);
	}

	number_of_keys = atoi(argv[1]);
	number_of_transactions = atoi(argv[2]);
	updated_key = atoi(argv[3]);
	delete_this = atoi(argv[4]);
	number_of_threads = atoi(argv[4]);

	devfd = open("/dev/keyvalue",O_RDWR);

	if(devfd < 0) {
		fprintf(stderr, "Device open failed");
		exit(1);
	}
	else{
		fprintf(stderr, "Device opened Hurray\n\n");
	}

	srand((int)time(NULL)+(int)getpid());

	// Initializing the keys
	for(i = updated_key; i < updated_key+number_of_keys; i++) {
	// 	// fprintf(stderr, "setting key - %d\n", i);
		memset(data, 0, 1024);
		a = rand();
		sprintf(data, "%d", a);
		key = rand() % 20;

		tid = kv_set(devfd, i, strlen(data), data);
		fprintf(stderr,"S\t\t\t%d\t%d\t%lu\t%s\n", tid, i, strlen(data), data);
	}

	fprintf(stderr,"\n\nDeleting\n");

	for (int i = 0; i < delete_this; ++i) {
		/* code */
		int deleting_node = rand()%number_of_keys;
		tid = kv_delete(devfd, deleting_node);
		if(tid == -1)
			fprintf(stderr,"Cannot delete, \t\t%d\t%d\n", tid, deleting_node);
		else
			fprintf(stderr,"Deleted, \t\t%d\t%d\n", tid, deleting_node);
	}

	fprintf(stderr,"\n\nGetting\n");
/*	for (int i = 10; i >=0; --i) {
		key = rand() % 20;
		tid = kv_delete(devfd, i);
		if(tid == -1)
			fprintf(stderr,"Cannot delete, \t\t%d\t%d\n", tid, i);
		else
			fprintf(stderr,"Deleted, \t\t%d\t%d\n", tid, i);
	}*/

	/*for(i = 0; i < number_of_keys; i++)
	{
		memset(data,0,4096);
		tid = kv_get(devfd, i, &size, &data);
		fprintf(stderr,"G\t%d\t%lu\t%d\n", tid, sizeof(int), a);		
	}*/

	close(devfd);
	return 0;
}

