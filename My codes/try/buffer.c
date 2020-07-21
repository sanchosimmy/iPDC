#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int bufferlength=8;
int buffercount=0;
FILE *fp;
int size_buffer=1000;

struct node {
   char *data;
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
{//printf("\n \t #%s# \n",dat);
buffercount++;
struct node *link = (struct node*) malloc(sizeof(struct node));

link->data = malloc(size_buffer*sizeof(unsigned char));
	
//link->data = dat;
memcpy(link->data,dat,strlen(dat));
       //printf("\n dat  %s  \t",dat);
             // printf("\n Next line  %s  \n\n",link->data);
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
         	//printf("\n Next address  %x  \n",ptr->next);
         	ptr = ptr->next;
      		}
     	printf("(%s) \n",ptr->data); 
   	}
printf(" ]");
}

void main() 
{char temp[1024];

fp=fopen("data.csv", "r");
if (!fp) 
	{
        printf("Can't open file\n");
       exit(0);
   	}
   	      if(fgets(temp, 1024, fp)!=NULL)
      {
             temp[strlen(temp)-1]='\0';
       size_buffer=strlen(temp);
       fseek(fp, 0, SEEK_SET);
       }
printf("\e[1;1H\e[2J");
int lines;
int option;

//char *temp= malloc(1000*sizeof(unsigned char));

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
		{//printf("\n Enter value %d\t",kk);
	      // scanf("%d", &option); 
/*
if(kk==1)    insert_element("1,100.924527742283,-319.461668656724,218.537140914442,0,0,0,1,0,0,0,0");
else if(kk==2)    insert_element("2,191.969859526618,-324.809490890383,132.839631363765,0,1,0,0,1,1,0,0");
else if(kk==3)    insert_element("3,264.223843927828,-298.362697074895,34.1388531470675,0,0,0,1,0,1,1,1");
else if(kk==4)    insert_element("4,191.969859526618,-324.809490890383,132.839631363765,0,1,0,0,1,1,0,0");
else if(kk==5)    insert_element("5,191.969859526618,-324.809490890383,132.839631363765,0,1,0,0,1,1,0,0");
else if(kk==6)    insert_element("6,191.969859526618,-324.809490890383,132.839631363765,0,1,0,0,1,1,0,0");
else if(kk==7)    insert_element("7,264.223843927828,-298.362697074895,34.1388531470675,0,0,0,1,0,1,1,1");
else if(kk==lines)   insert_element("8,264.223843927828,-298.362697074895,34.1388531470675,0,0,0,1,0,1,1,1");
else   insert_element("##");

*/	


//######################## 


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
 	 //printf("\e[1;1H\e[2J");
 
	
 	// ######################
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
