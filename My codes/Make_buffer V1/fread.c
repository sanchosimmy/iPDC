#include <stdio.h>
#include <stdlib.h>
#include<string.h>
FILE *fp;
char temp[1024];


//  CONSTANTS
#define		SIZE_OF_BUFFER		    20000	// Maximum size of buffer



//*********************************************************************************************************************
//DO MALLOC LATER                                                IMPORTANT
//*********************************************************************************************************************

//  PROTOTYPES

int	getNumber(int* pNumber);
int	getfloat(float* pNumber);

struct data_buffer {
char time[50];
float R;
float Y;   
float B;
float D1;
float D2;
float D3;
float D4;
float D5;
float  D6;
float  D7;
float  D8;
} circularBuffer[SIZE_OF_BUFFER] = { 0 };	// Empty circular buffer

	int	writeIndex	    =	0;	// Index of the write pointer
	int	bufferLength	=	0;	// Number of values in circular buffer
	
	
void clearbuffer(void)
{      writeIndex	    =	0;	
	bufferLength	=	0;
}	

//#######################################################################################################################################
//Function to print the contents of the buffer

void printbuffer(void)
{if (bufferLength == 0)
	{
	printf("\n    Buffer is empty!\n\n    ");
	getchar();
	return;
	}
printf("\n");
int k;
if (bufferLength != SIZE_OF_BUFFER) 
	{
	for (k=0;k<bufferLength;k++)
	printf("\n %s %f %f %f %f %f %f %f %f %f %f %f ", circularBuffer[k].time, circularBuffer[k].R, circularBuffer[k].Y, circularBuffer[k].B, circularBuffer[k].D1, circularBuffer[k].D2, circularBuffer[k].D3, circularBuffer[k].D4, circularBuffer[k].D5, circularBuffer[k].D6, circularBuffer[k].D7, circularBuffer[k].D8);
	}
			
else
	{int m=0;
	if(writeIndex!=(SIZE_OF_BUFFER-1))
		k=writeIndex;	
		else
		k=0;		
		for (;m<bufferLength;k)
			{
			printf("\n %s %f %f %f %f %f %f %f %f %f %f %f ", circularBuffer[k].time, circularBuffer[k].R, circularBuffer[k].Y, circularBuffer[k].B, circularBuffer[k].D1, circularBuffer[k].D2, circularBuffer[k].D3, circularBuffer[k].D4, circularBuffer[k].D5, circularBuffer[k].D6, circularBuffer[k].D7, circularBuffer[k].D8);
			m++;
				if(k<(SIZE_OF_BUFFER-1))
				k++;
				else
				k=0;
			}
	}
}
//#######################################################################################################################################
/*Function to read n lines from the file
fp is declared as a global file
At end of file, it loops back the first line
Accepts number of lines to be read :n 
*/
void readlines(int n)
{    
for(int f=0;f<n;f++)
	{
	int row_count = 0;
    	int field_count = 0;
    	repeat:
	if(fgets(temp, 1024, fp))
		{
		field_count = 0;
        	row_count++;
        	float a;

        	char *field = strtok(temp, ",");
        	while (field) {
        		switch (field_count)
        			{
        			case 0:
					{strcpy( circularBuffer[writeIndex].time, field);}
  				break;
   				case 1:
					{circularBuffer[writeIndex].R=strtod(field , NULL);}
      				break;      
    				case 2:
					{circularBuffer[writeIndex].Y=strtod(field , NULL);}
      				break;   
    				case 3:
					{circularBuffer[writeIndex].B=strtod(field , NULL);}
      				break;   
    				case 4:
					{circularBuffer[writeIndex].D1=strtod(field , NULL);}
      				break;
    				case 5:
					{circularBuffer[writeIndex].D2=strtod(field , NULL);}
      				break;      
    				case 6:
					{circularBuffer[writeIndex].D3=strtod(field , NULL);}
      				break;   
    				case 7:
					{circularBuffer[writeIndex].D4=strtod(field , NULL);}
      				break;   
    				case 8:
					{circularBuffer[writeIndex].D5=strtod(field , NULL);}
      				break;
    				case 9:
					{circularBuffer[writeIndex].D6=strtod(field , NULL);}
      				break;      
    				case 10:
					{circularBuffer[writeIndex].D7=strtod(field , NULL);}
				break;
    				case 11:
					{circularBuffer[writeIndex].D8=strtod(field , NULL);}
      				break;   
				}

           		field = strtok(NULL, ",");	
            		field_count++;
        		}

               }
               else
               {fseek(fp, 0, SEEK_SET);
               goto repeat;
               }

			if (bufferLength != SIZE_OF_BUFFER) 
			{
				bufferLength++;
			}
				
				if(writeIndex<(SIZE_OF_BUFFER-1))
				{writeIndex++;	}
				else
				{writeIndex=0;}

	}         
}



int main ()
{
printf("\e[1;1H\e[2J");
int lines;
int option;
fp=fopen("data.csv", "r");
if (!fp) 
	{
        printf("Can't open file\n");
        return 0;
   	}
loop:

printf("\n\n\n************************ MENU ************************\n");
printf("\tEnter choice ");
//printf("\u263A\n");   
printf("\n\t\t1 Copy N lines to buffer \n\t\t2 Print buffer\n\t\t3 Clear buffer\n\t\t4 Exit");
printf("\u2620\n");  
printf("******************************************************\n");
scanf("%d", &option); 
printf("\e[1;1H\e[2J");
if(option==1)
	{
	printf("\n Enter Number of lines to read\t");
	scanf("%d", &lines); 
	readlines(lines);
 	 printf("\e[1;1H\e[2J");}
else if(option==2)
	{
	printbuffer();			
	}
else if(option==3)
	{
	clearbuffer();			
	}
else
       exit(0);
goto loop;
fclose(fp);
return 0;
}


