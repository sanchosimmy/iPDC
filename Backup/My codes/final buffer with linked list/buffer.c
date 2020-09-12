#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//constants
int bufferlength=8;       //Can be changed during runtime.Buffer will be reset.
int buffercount=0;
FILE *fp;
int size_buffer=1000;
int lines;
int option;

struct node 
{
   char *data;
   struct node *next;
};

struct node *head = NULL;
struct node *tail = NULL;
struct node *current = NULL;

//function prototypes
bool is_empty();
void delete_one();
void delete_all();
void insert_element(char dat[]);
void print_buffer(); 

//Main program ####################################################    Main program
void main() 
{char temp[1024];
fp=fopen("data.csv", "r");
if (!fp) 
	{
        printf("Can't open file\n");
       exit(0);
   	}
/*/////////////////////////////////////////////////////////
This following part will not me necessary as 
PHNMR,ANNMR,DGNMR values will be available in the main program
//////////////////////////////////////////////////////////*/ 
   	   	
if(fgets(temp, 1024, fp)!=NULL)
      {
       temp[strlen(temp)-1]='\0';
       size_buffer=strlen(temp)+12;//+12 to account for sign
       fseek(fp, 0, SEEK_SET);
       }
/////////////////////////////////////////////////////////      
printf("\e[1;1H\e[2J");
loop:
printf("\n\n\n************************ MENU ************************\n");
printf("\tEnter choice ");
//printf("\u263A\n");   
printf("\n\t\t1 Copy N lines to buffer \n\t\t2 Print buffer\n\t\t3 Clear buffer\n\t\t4 Change buffer length\n\t\t5 Exit");
printf("\u2620\n");  
printf("******************************************************\n");
scanf("%d", &option); 
printf("\e[1;1H\e[2J");
if(option==1)
	{
	printf("\n Enter Number of lines to read\t");
	scanf("%d", &lines); 
	for(int kk=1;kk<lines+1;kk++)
		{	
		repeat:
		if(fgets(temp, 1024, fp)!=NULL)
			{
			temp[strlen(temp)-1]='\0';
        		insert_element(temp);
       			}
      		else
       			{fseek(fp, 0, SEEK_SET);
       			goto repeat;
			}
 	printf("\e[1;1H\e[2J");
		}
 	}
else if(option==2)
	{
	 print_buffer();		
	}
else if(option==3)
	{
	delete_all();		
	}
else if(option==4)
	{
	 printf("\n Enter new buffer length \t");
	 scanf("%d", &bufferlength); 
	delete_all();       		
	}	 
else
       {exit(0);
       fclose(fp);}
goto loop;

}
//check if buffer is empty
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
if(tail->next == tail) 
      {
      tail = NULL;
      head=NULL;
      }     
else
   tail = tail->next;
free(tempLink->data);
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
void insert_element(char dat[]) 
{
buffercount++;
struct node *link = (struct node*) malloc(sizeof(struct node));
link->data = malloc(size_buffer*sizeof(unsigned char));
//link->data = dat;
memcpy(link->data,dat,strlen(dat));
if (is_empty()) 
	{
	head = link;
	head->next = head;
	tail=link;
	buffercount=1;
	}
else   {
   	if(buffercount==(bufferlength+1))
  		delete_one();
 
      head->next = link;

      head = link;
      head->next=head;
      }  
}
//display the elements in the buffer  ####################################################    Display Buffer
void print_buffer() 
{
struct node *ptr = tail;
printf("\n[ \n");
if(tail != NULL) 
	{
	while(ptr->next != ptr) 
		{     
         	printf("(%s) \n",ptr->data);
         	ptr = ptr->next;
      		}
     	printf("(%s) \n",ptr->data); 
   	}
printf(" ]");
}
