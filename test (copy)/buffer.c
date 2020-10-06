
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
#include <string.h> 
#include <sys/time.h>
#include <sys/resource.h>

char buffer[50];


int main() 
{  while(1)
{int k;}
memset(buffer,0,50);
strcat(buffer,"Sancho");
printf("%s\n",buffer);
buffer[2]=k;
printf("%s\n",buffer);
}

