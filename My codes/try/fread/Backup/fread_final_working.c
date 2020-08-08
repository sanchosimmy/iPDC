#include <stdio.h>
#include <stdlib.h>
#include<string.h>
FILE *fp;
char temp[1024];


//Function to return signed 
float string2num(char *field )
{float a;
int j;
int sign;
sign=1;
j=strlen(field);
if(field[0]=='-')
	{sign=-1;
	for(int k=0;k<j;k++)
		field[k]=field[k+1];
	}
if(field[0]=='+')
	{
	for(int k=0;k<j;k++)
		field[k]=field[k+1];
	}
return(sign*strtod(field , NULL));
}




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
					{printf("Time\t");}
  				break;
   				case 1:
					{printf("R\t");}
      				break;      
    				case 2:
					{printf("Y\t");}
      				break;   
    				case 3:
					{printf("B\t");}
      				break;   
    				case 4:
					{printf("D1\t");}
      				break;
    				case 5:
					{printf("D2\t");}
      				break;      
    				case 6:
					{printf("D3\t");}
      				break;   
    				case 7:
					{printf("D4\t");}
      				break;   
    				case 8:
					{printf("D5\t");}
      				break;
    				case 9:
					{printf("D6\t");}
      				break;      
    				case 10:
					{printf("D7\t");}
				break;
    				case 11:
					{printf("D8\t");}
      				break;   
				}
     			if(field_count == 0)  
     	          		printf("%s\n", field); 	             
     			else if(field_count<4)
	    			{//a=string2num(field);
	    			a=strtod(field , NULL);
            			printf("%lf\n", a);}
         		else
          			printf("%s\n", field);
           		field = strtok(NULL, ",");	
            		field_count++;
        		}
        printf("\n");
               }
               else
               {fseek(fp, 0, SEEK_SET);
               goto repeat;
               }


	}         
}



int main ()
{int lines;
fp=fopen("data.csv", "r");
if (!fp) {
        printf("Can't open file\n");
        return 0;
    }
printf("\n Enter Number of lines to read\t");
scanf("%d", &lines); 
readlines(lines);


fclose(fp);
return 0;

}


