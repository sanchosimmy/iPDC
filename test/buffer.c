
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
#include <pthread.h> 
#include <sys/time.h>
#include <sys/resource.h>

int j=0,k=0;
pthread_t thread_id_xyz;
pthread_attr_t tattr;


struct sched_param param;


// A normal C function that is executed as a thread  
// when its name is specified in pthread_create() 
void *myThreadFun1(void *vargp) 
{ 

    while(j<100)
    {
    printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA %d \n",j); 
    j++;}
    return NULL; 
} 

int main() 
{ 
pthread_attr_init (&tattr);
pthread_attr_getschedparam (&tattr, &param);
param.sched_priority =param.sched_priority+11;
//pthread_attr_setschedparam (&tattr, &param);


pthread_create(&thread_id_xyz, &tattr, myThreadFun1, NULL);
printf("After Thread\n");
while(k<201)
{    printf("___%d \n",k); 
k++;} 
pthread_join(thread_id_xyz, NULL); 
    exit(0); 
}

