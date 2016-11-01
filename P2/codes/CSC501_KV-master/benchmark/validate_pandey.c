#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <time.h>
#include <keyvalue.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int i=0,number_of_threads = 1, number_of_keys=1024; 
    int tid;
    __u64 size;
    __u64 key;
    char data[4096],op;
    char **kv;
	int *tid_in;
    int devfd;
    int error = 0;
    if(argc < 2)
    {
        fprintf(stderr, "Usage: %s number_of_keys\n",argv[0]);
        exit(1);
    }
    number_of_keys = atoi(argv[1]);
    kv = (char **)malloc(number_of_keys*sizeof(char *));
	tid_in = (int *)calloc(number_of_keys,sizeof(int));
    for(i = 0; i < number_of_keys; i++)
    {
        kv[i] = (char *)calloc(4096, sizeof(char));
    }
    // Replay the log
    // Validate
    while(scanf("%c %llu %llu %d %s",&op, &tid,&key, &size, &data)!=EOF)
    {
        if(op == 'S')
        {
			if(tid_in[(int)key]<tid){
				tid_in[(int)key]=tid;
				strcpy(kv[(int)key],data);
				fprintf(stderr,"Key: %d\t data: %s\n",key,kv[(int)key]);
            }
			memset(data,0,4096);
        }
    }
    devfd = open("/dev/keyvalue",O_RDWR);
    if(devfd < 0)
    {
        fprintf(stderr, "Device open failed");
        exit(1);
    }
    for(i = 0; i < number_of_keys; i++)
    {
        memset(data,0,4096);
        tid = kv_get(devfd,i,&size,&data);
		if(tid==-1)
			fprintf(stderr,"Key not found: %d\n",i);
		else{
			if(strcmp(data,kv[i])!=0)
			{
				fprintf(stderr, "Key %i has a wrong value %s v.s. %s\n",i,data,kv[i]);
				error++;
			}
		}
    }
    if(error==0)
            fprintf(stderr, "You passed!\n");
    
    close(devfd);
    return 0;
}

