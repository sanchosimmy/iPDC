#include <stdio.h>
#include <stdlib.h>
#include<string.h>
FILE *fp;
char buf[1024];

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
void readlines()
{    int row_count = 0;
    int field_count = 0;
if(fgets(buf, 1024, fp))
{
field_count = 0;
        row_count++;

   /*     if (row_count == 1) {
            continue;
        } */
        float a;

        char *field = strtok(buf, ",");
        while (field) {
            if (field_count == 0) {
                printf("Time\t");
            }
            if (field_count == 1) {
                printf("R\t");
            }
            if (field_count == 2) {
                    printf("Y\t");
            }
            if (field_count == 3) {
                printf("B\t");
            }
            if (field_count == 4) {
                printf("D1\t");
            }
            if (field_count == 5) {
                printf("D2\t");
            }
            if (field_count == 6) {
                    printf("D3\t");
            }
            if (field_count == 7) {
                printf("D4\t");
            }
             if (field_count == 8) {
                printf("D5\t");
            }
            if (field_count == 9) {
                printf("D6\t");
            }
            if (field_count == 10) {
                    printf("D7\t");
            }
            if (field_count == 11) {
                printf("D8\t");
            }           
	    if(field_count != 0)
	    	{a=string2num(field);
            	printf("%lf\n", a);
           	 }
          else
          printf("%s\n", field);
            field = strtok(NULL, ",");

            field_count++;
        }
        printf("\n");
    }


         
}
int main ()
{
fp=fopen("data.csv", "r");
if (!fp) {
        printf("Can't open file\n");
        return 0;
    }
 for(int j=0;j<10;j++)   
readlines();


fclose(fp);
return 0;

}


/* Old cde
#include <stdio.h>
#include <stdlib.h>
FILE *fp;
char buf[1024];

char readlines()
{int x;
            while  ( ( x = fgetc(fp) ) != EOF )
            {
                printf( "%c", x );
            }
}
void main ()
{
fp=fopen("data.csv", "r");
if (!fp) {
        printf("Can't open file\n");
        return 0;
    }
    
readlines();

printf("Ass");
fclose(fp);
  return 0;
}
*/

