#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <time.h>
#include <keyvalue.h>
#include <fcntl.h>
#include <string.h>
int number_of_threads = 1, number_of_keys=1024, number_of_transactions = 65536, number_of_deletes = 10,number_of_reads = 10; 

pthread_t p1,p2,p3,p4;
int devfd;
void* initialize()
{
    int a,i=0,tid;
	__u64 size;
	char data[1024];
	for(i = 0; i < number_of_keys; i++)
    {
        memset(data, 0, 1024);
        a = rand();
        sprintf(data,"%d",a);
        tid = kv_set(devfd,i,strlen(data),data);
        fprintf(stderr,"PID:%d\nS\t%d\t%d\t%d\t%s\n",getpid(),tid,i,strlen(data),data);
    }
}
void* delete()
{
    int a,i=0,tid;
	__u64 size;
	char data[1024];
	for(i=0;i<number_of_deletes;i++)
	{
		a = rand()%number_of_keys;
		tid = kv_delete(devfd,a);
		if(tid==-1)
			fprintf(stderr,"PID:%d\tCould not Delete %d\n",getpid(),a);
		else
			fprintf(stderr,"PID:%d\nDel\t%d\t%d\n",getpid(),tid,a);
	}
}
void* read()
{
    int a,i=0,tid;
	__u64 size;
	char data[1024];
	for(i=0;i<number_of_reads;i++)
	{
		a = rand()%number_of_keys;
		tid = kv_get(devfd,a,&size,&data);
		if(tid==-1)
			fprintf(stderr,"PID:%d\tCould not Read%d\n",getpid(),a);
		else
			fprintf(stderr,"PID:%d\nRead\t%d\t%d\t%d\t%s\n",getpid(),tid,a,strlen(data),data);
	}
}
int main(int argc, char *argv[])
{
    if(argc < 5)
    {
        fprintf(stderr, "Usage: %s number_of_keys number_of_transactions number_of_deletes number_of_reads\n",argv[0]);
        exit(1);
    }
    number_of_keys = atoi(argv[1]);
    number_of_transactions = atoi(argv[2]);
	number_of_deletes = atoi(argv[3]);
	number_of_reads = atoi(argv[4]);
    devfd = open("/dev/keyvalue",O_RDWR);
    if(devfd < 0)
    {
        fprintf(stderr, "Device open failed");
        exit(1);
    }
    srand((int)time(NULL)+(int)getpid());
	int pid=fork();
	int rc=pthread_create(&p1,NULL,initialize,NULL);
	rc=pthread_create(&p2,NULL,initialize,NULL);
	rc=pthread_create(&p3,NULL,delete,NULL);
	rc=pthread_create(&p4,NULL,read,NULL);
    pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	pthread_join(p3,NULL);
	pthread_join(p4,NULL);
	if(pid==0){
		fprintf(stderr,"Child Done\n");
		exit(0);
	}
	// Initializing the keys
/*    for(i = 0; i < number_of_keys; i++)
    {
        memset(data, 0, 1024);
        a = rand();
        sprintf(data,"%d",a);
        tid = kv_set(devfd,i,strlen(data),data);
        fprintf(stderr,"S\t%d\t%d\t%d\t%s\n",tid,i,strlen(data),data);
    }*/
/*    for(i = 0; i < number_of_transactions; i++)
    {
        tid = kv_get(devfd,i,size,&a);
        fprintf(stderr,"G\t%d\t%d\t%d\n",tid,sizeof(int),a);
        
    }*/
/*	for(i=0;i<number_of_deletes;i++)
	{
		a = rand()%number_of_keys;
		tid = kv_delete(devfd,a);
		if(tid==-1)
			fprintf(stderr,"Could not Delete %d\n",a);
		else
			fprintf(stderr,"Deleted %d\n",a);
	}*/
    close(devfd);
	fprintf(stderr,"Parent Done\n");
    return 0;
}

