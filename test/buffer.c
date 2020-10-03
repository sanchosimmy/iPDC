
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
#include <pthread.h> 
#include <sys/time.h>
#include <sys/resource.h>

pthread_t thread_id_xyz;
pthread_attr_t tattr;


struct sched_param param;


// A normal C function that is executed as a thread  
// when its name is specified in pthread_create() 
void *myThreadFun1(int a) 
{ int j,k=0;
j=a;
while(k<500)
{
printf("%d J in thread is %d \n",k,j);
k++;}
} 

int main() 
{ int j=0;
pthread_create(&thread_id_xyz,NULL, myThreadFun1,5);
printf("After Thread\n");
while(j<201)
{    printf("                                  j in main %d \n",j); 
j++;} 
pthread_join(thread_id_xyz, NULL); 
    exit(0); 
}

