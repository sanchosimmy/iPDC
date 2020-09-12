#include <stdio.h> 
#include <time.h> 
#include <sys/time.h>   
#include <sys/resource.h> 
#include"DisturbanceRecorder.h"
#include<string.h>
#include <stdlib.h>

///////////////////////////////////
// measure elapsed real time using the "clock_gettime" call. 
// This is one of the most accurate ways to measure wallclock time.
///////////////////////////////////

// struct timespec {                                                                                     
//    time_t   tv_sec;        /* seconds */                                                             
//    long     tv_nsec;       /* nanoseconds */                                                         
// };  

void main() 
{ FILE *cfg_file;
cfg_file = fopen("pmu.cfg","r");
fseek(cfg_file, 0, SEEK_END);
long fsize = ftell(cfg_file );
fseek(cfg_file, 0, SEEK_SET);  // same as rewind(f); 

char *string_cfg_file = malloc(fsize + 1);
fread(string_cfg_file, 1, fsize,cfg_file);
string_cfg_file[fsize] = 0;
fclose(cfg_file);
printf("\n Size :  %ld \t Text :  %s  END\n",fsize,string_cfg_file);

return;
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
