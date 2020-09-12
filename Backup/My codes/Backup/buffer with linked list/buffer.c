#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int bufferlength=8;
int buffercount=0;

struct node {
   int data;
   struct node *next;
};

struct node *head = NULL;
struct node *tail = NULL;
struct node *current = NULL;

bool is_empty() {
   return head == NULL;
}

int length() {
   int length = 0;

   //if list is empty
   if(head == NULL) {
      return 0;
   }

   current = head->next;

   while(current != head) {
      length++;
      current = current->next;   
   }
	
   return length;
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
void insert_element(int data) 
{
buffercount++;
struct node *link = (struct node*) malloc(sizeof(struct node));
link->data = data;
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
printf("\n[ ");
if(tail != NULL) 
	{
	while(ptr->next != ptr) 
		{     
         	printf("(%d) ",ptr->data);
         	ptr = ptr->next;
      		}
     	printf("(%d) ",ptr->data); 
   	}
printf(" ]");
}

void main() 
{
printf("\e[1;1H\e[2J");
int lines;
int option;

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
		{printf("\n Enter value %d\t",kk);
	        scanf("%d", &option); 
	        insert_element(option);
	        }
 	 printf("\e[1;1H\e[2J");}
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
       exit(0);
goto loop;

}
