#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <stdbool.h> 

FILE *fp;
char temp[1024];

int number=40;
//*******************************************************************************************************************




//  PROTOTYPES

int bufferlength=8;
int buffercount=0;

struct node {
unsigned char *data;
struct node *next;
} ;	

struct node *head = NULL;
struct node *tail = NULL;
struct node *current = NULL;



//	if(!aa) {
//
//		printf("No enough memory for cfg\n");
//	}
	



bool is_empty() 
{
   return head == NULL;
}
//delete first item ####################################################    DELETE ONE
void delete_one() 
{
buffercount--;
//save reference to first link
struct node *tempLink =tail;
//tempLink->ref=malloc(number*sizeof(unsigned char));
//tempLink->data = tempLink->ref;
if(tail->next == tail) 
      {
      tail = NULL;
      head=NULL;
      }     
else
   tail = tail->next;
   

free(tempLink);
}
//delete all items ####################################################    DELETE ALL
void delete_all()
{
while(!is_empty()) 
	{            
	delete_one();
	}   
	buffercount=0;
}
//insert link at the first location  ####################################################    Insert Element
void insert_element(char data[]) 
{//printf("\n%s\n",data);

  	  	      
}


//display the elements in the buffer  ####################################################    Display Buffer
void print_buffer() 
{
struct node *ptr = tail;

printf("\n[ ");
if(tail != NULL) 
	{
	while(ptr->next != ptr) 
		{     
         	printf("(%s) ",ptr->data);
         	ptr = ptr->next;
      		}
     	printf("(%s) ",ptr->data); 
   	}
printf(" ]");
}
	//########################################################################################################################################
/*Function to read n lines from the file
fp is declared as a global file
At end of file, it loops back the first line
Accepts number of lines to be read :n 
*/
void readlines(int n)
{    
for(int f=0;f<n;f++)
	{		  

    	repeat:
	if(fgets(temp, 1024, fp))
        {//printf("\n%s\n",temp);

	//struct node *link =(struct node*) malloc(sizeof(struct node));
	struct node *link = malloc(sizeof(struct node));
	link->data = malloc(number*sizeof(unsigned char));

	buffercount++;
      //	  if (!is_empty())	  		printf("\n   hdhdhd      %s    bugaga\n\n\n",tail->data);  
	link->data = temp; //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN

	if (is_empty()) 
		{
		head = link;
		head->next = head;
		tail=link;

		buffercount=1;
		}
	else   {
  			if(buffercount==(bufferlength+1))
  				//delete_one();
  				buffercount--;
 		
     		head->next = link;
      		head = link;
      		head->next=head;

     		} 


       }
       else
       {fseek(fp, 0, SEEK_SET);
       goto repeat;
       }
 if (!is_empty())		printf("\n   hdhdhd   %d     %s    bugaga\n",f,tail->data); 
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
//printf("\e[1;1H\e[2J");
if(option==1)
	{
	printf("\n Enter Number of lines to read\t");
	scanf("%d", &lines); 
	readlines(lines);
 	 //printf("\e[1;1H\e[2J");

 	 }
else if(option==2)
	{
	print_buffer();			
	}
else if(option==3)
	{
	delete_all();			
	}
else
       exit(0);
goto loop;
fclose(fp);
return 0;
}


