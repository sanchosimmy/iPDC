#include <stdio.h> 
#include <time.h> 
#include <sys/time.h>   
#include <sys/resource.h> 
#include"DisturbanceRecorder.h"

///////////////////////////////////
// measure elapsed real time using the "clock_gettime" call. 
// This is one of the most accurate ways to measure wallclock time.
///////////////////////////////////

// struct timespec {                                                                                     
//    time_t   tv_sec;        /* seconds */                                                             
//    long     tv_nsec;       /* nanoseconds */                                                         
// };  

void main () { 
int tt=5;
    struct timespec start, finish; 
while(1)
{
  // chew up some CPU time
    int i,j,k; 
    for (i=0; i<100000000; i++) 
    for (j=0; j<1; j++) 
    { k==i*i; }  
       
 clock_gettime(CLOCK_REALTIME, &start); 
    printf(" %.6lf\n",(double)start.tv_sec+(double)start.tv_nsec/1000000000); 
    printf("%d\n",print_shit(tt));
 } 
 
} 
/*
  // chew up some CPU time
    int i,j,k; 
    for (i=0; i<100000000; i++) 
    for (j=0; j<10; j++) 
    { k==i*i; }     

    clock_gettime(CLOCK_REALTIME, &finish); 

    long seconds = finish.tv_sec - start.tv_sec; 
    long ns = finish.tv_nsec - start.tv_nsec; 
    
    if (start.tv_nsec > finish.tv_nsec) { // clock underflow 
	--seconds; 
	ns += 1000000000; 
    } 
    printf("seconds without ns: %ld\n", seconds); 
    printf("nanoseconds: %ld\n", ns); 
    printf("total seconds: %e\n", (double)seconds + (double)ns/(double)1000000000); 
*/
