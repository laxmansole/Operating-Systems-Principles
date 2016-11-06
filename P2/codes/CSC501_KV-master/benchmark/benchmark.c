#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <time.h>
#include <keyvalue.h>
#include <fcntl.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

int devfd;
pthread_mutex_t mymutex;

void *doset()
{
    long i,tid;
    int a;
    long key;
    long number_of_transactions = 65536;
    char data[1024];
    __u64 size;

    for(i = 0; i < number_of_transactions; i++)
    {
        memset(data, 0, 1024);
        a = rand();
	key = i;// rand()%100;
        sprintf(data,"%d",a);
//        pthread_mutex_lock(&mymutex);
        tid = kv_set(devfd,key,strlen(data)+1,data);
        fprintf(stderr, "S\t%d\t%d\t%d\t%s\n",tid,key,strlen(data)+1,data);
//        pthread_mutex_unlock(&mymutex);
    }
    return 0;
}

void *doget()
{
    int i,tid;
    long number_of_transactions = 65536;
    char data[1024];
    __u64 size;

    for(i = 0; i < number_of_transactions; i++)
    {
        memset(data, 0, 1024);
        tid = kv_get(devfd,i,&size,data);
        fprintf(stderr, "G\t%d\t%d\t%llu\t%s\n",tid,i,size, data );
    //    fprintf(stderr, "G\t%d\t%d\t%llu\t%s\n",tid,i,size,(tid>-1)? data : "NULL");
    }
    return 0;
}



void *dodel()
{
    int i,tid;
    long number_of_transactions = 65536;
    char data[1024];
    __u64 size;

    for(i = 0; i < number_of_transactions; i = i+2)
    {
        memset(data, 0, 1024);
        tid = kv_delete(devfd,i);
        fprintf(stderr, "D\t%d\t%d\t%llu\t%s\n",tid,i,size, data );
        //printf("D\t%d\t%d\t%llu\t%s\n",tid,i,size,(tid>-1)? data : "NULL");
    }
    return 0;
}




int main(int argc, char *argv[])
{
    int i=0,number_of_threads = 1 ; 

    pthread_t pthread[6];

    devfd = open("/dev/keyvalue",O_RDWR);
    pthread_mutex_init(&mymutex, NULL);
    if(devfd < 0)
    {
        printf("Device open failed");
        exit(1);
    }

    pthread_create(&pthread[1],NULL,doset,NULL);
    pthread_create(&pthread[2],NULL,dodel,NULL);
    pthread_create(&pthread[0],NULL,doget,NULL);
    pthread_create(&pthread[3],NULL,doget,NULL);
    pthread_create(&pthread[4],NULL,doset,NULL);
    pthread_create(&pthread[5],NULL,dodel,NULL);
    pthread_create(&pthread[6],NULL,doget,NULL);
    pthread_join(pthread[1],NULL);
    pthread_join(pthread[1],NULL);
    pthread_join(pthread[2],NULL);
    pthread_join(pthread[3],NULL);
    pthread_join(pthread[4],NULL);
    pthread_join(pthread[5],NULL);
    pthread_join(pthread[6],NULL);
   
    close(devfd);
    return 0;
}

