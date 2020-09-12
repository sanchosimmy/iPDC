#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include<math.h>
#include <stdint.h> ////for uint16_t
#include "function.h"

/*delete these
     #include <time.h>
     clock_t start, end;
     double cpu_time_used;
     start = clock();
     end = clock();
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;    
     printf("\nTook %f seconds to execute \n", cpu_time_used);   
 */ 
#define max_data_rate 200
#define MAX_STRING_SIZE 5000

struct ConfigurationFrame 
{
	int  cfg_pmuID; 
	int  cfg_fdf; 
	int  cfg_af; 
	int  cfg_pf; 
	int  cfg_pn; 
	int  cfg_phnmr_val; 
	int  cfg_annmr_val; 
	int  cfg_dgnmr_val; 
	int  cfg_fnom; 
	int  cfg_dataRate; 
	char *cfg_STNname; 
	char *cfg_phasor_channels; 
	char *cfg_analog_channels; 
	char *cfg_digital_channels; 
};
struct ConfigurationFrame *cfg_info;

int  PMU_uport;
int  PMU_tport, PMU_mulport;
char *hdr_frame, *markup1, PMU_mulip[20];
unsigned char phunit_final_val[500];
unsigned char anunit_final_val[500];

double t1;
int frmt, fdf, af, pf, pn, phnmr, annmr, dgnmr, num_pmu = 1; 
int cfg2_frm_size, data_frm_size = 18, data_rate, cfgcnt = 0;  		
int i, j, n, pmu_id, indx = 0, global_data_frm_size=0, hdrFrmSize=0;
long int soc, fracsec = 0;
long int phunit = 915527, anunit = 1, digunit = 0;

const long int TB = 16777215;  // roundf(powf(2,24) - 1);
char temp_5[16];
unsigned char temp[2], temp_1[4], temp_6[16];
unsigned char cfg2_frm[MAX_STRING_SIZE];
unsigned char header[MAX_STRING_SIZE];


int bufferlength=50000;       //Can be changed during runtime.Buffer will be reset if length changed.
int buffercount=0;
FILE *fp;
int size_buffer=1000;
int lines;
int option;
float end_sample;
char start_time[50],end_time[50]; //Put proper values later 50 ?

int f;

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
void read_config();
void display_config();
void write_data();
void write_data_helper(char* data,float i,FILE* dat_file);
int c2i (unsigned char temp[]);



//Main program ####################################################    Main program
void main() 
{char temp_val[1024];


fp=fopen("data.csv", "r");
if (!fp) 
	{
        printf("Can't open file\n");
       exit(0);
   	}
   	
if(fgets(temp_val, 1024, fp)!=NULL) //To get approx valueof length for each line and account for -ive signs
      {
       temp_val[strlen(temp_val)-1]='\0';
       size_buffer=strlen(temp_val)+30;//+12 to account for sign
       fseek(fp, 0, SEEK_SET);
       }
/////////////////////////////////////////////////////////      
//printf("\e[1;1H\e[2J");
loop:



printf("\n\n\n************************ MENU ************************\n");
printf("\tEnter choice ");
//printf("\u263A\n");   
printf("\n\t\t1 Copy N lines to buffer \n\t\t2 Print buffer\n\t\t3 Clear buffer\n\t\t4 Change buffer length\n\t\t5 Make comtrade files\n\t\t6 Exit");
printf("\u2620\n");  
printf("******************************************************\n");
scanf("%d", &option); 
printf("\e[1;1H\e[2J");

if(option==1)
	{
	printf("\n Enter Number of lines to read\t");
	scanf("%d", &lines); 
	for(int local_count=1;local_count<lines+1;local_count++)
		{
		char* temp_string = malloc(size_buffer*sizeof(unsigned char));	
 		repeat:
		if(fgets(temp_string,size_buffer, fp)!=NULL)
			{
			//temp_string[strlen(temp_string)]='\0';
        		insert_element(temp_string);
       			}
      		else
       			{fseek(fp, 0, SEEK_SET);
       			goto repeat;
			}
		free(temp_string);
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
	{printf("\n Warning !!! Current buffer will be cleared !!!\t");
	printf("\n Enter new buffer length \t");
	scanf("%d", &bufferlength); 
	delete_all();       		
	}
else if(option==5)
	{ 
         read_config();
         write_data();
         display_config();    		
	}		 
else
       {
       fclose(fp);
       exit(0);
       }
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
//printf("\n++%s++",dat);
buffercount++;
struct node *link = (struct node*) malloc(sizeof(struct node));
link->data = malloc(size_buffer*sizeof(unsigned char));
dat[strlen(dat)-1]=0;
strcpy(link->data,dat);
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
printf("\n");
if(tail != NULL) 
	{
	while(ptr->next != ptr) 
		{     
         	printf("(%s)\n",ptr->data);
         	ptr = ptr->next;
      		}
     	printf("(%s)\n",ptr->data); 
   	}
}

//Display config data
void display_config()
{ int flag_space=0;
FILE *cfg_file;
cfg_file = fopen("config.cfg","w");
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//printf("\n length %d\n",strlen(cfg_info->cfg_STNname));
for(int local_count=0;local_count<strlen(cfg_info->cfg_STNname);local_count++)
	{ flag_space=0;
	       for(int local_count_1=local_count;local_count_1<strlen(cfg_info->cfg_STNname);local_count_1++)  //Checking for space
			{if(cfg_info->cfg_STNname[local_count_1]!=' ') flag_space=1;}
			if(flag_space==0) break;
		
			fprintf(cfg_file,"%c",cfg_info->cfg_STNname[local_count]);
			//printf("%c",cfg_info->cfg_STNname[local_count]);
	}
fprintf(cfg_file,",%d,2013\n",pmu_id);
//printf(",%d,2013\n",pmu_id);
fprintf(cfg_file,"%d,%dA,%dD\n",phnmr+dgnmr*16,phnmr,dgnmr*16);
//printf("%d,%dA,%dD\n",phnmr+dgnmr*16,phnmr,dgnmr*16);
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//printf("\nStation Name:%s",cfg_info->cfg_STNname);
//printf("PMU ID:%d",pmu_id);
//printf("\trev_id:2013");


//printf("\nNo of phasors: %d",phnmr);
//printf("\nNo of analog values: %d",annmr);
//printf("\nNo of digital values: %d",dgnmr);
//printf("\nPhasor Channels\n");
int count=0,analog=1;
for(int local_count=0; local_count< (phnmr); local_count++)
{				
fprintf(cfg_file,"%d,",analog++);	
//printf("%d,",analog-1);
	for(int local_count_1=0; local_count_1< 16; local_count_1++) 
		{
		flag_space=0;
		for(int local_count_2=local_count_1;local_count_2<16;local_count_2++)  //Checking for non-space chara ahead
			{if(cfg_info->cfg_phasor_channels[local_count_2+count*16]!=' ') flag_space=1;}
		if(flag_space==0) break;
		//printf("%c",cfg_info->cfg_phasor_channels[local_count_1+count*16]);
	        fprintf(cfg_file,"%c",cfg_info->cfg_phasor_channels[local_count_1+count*16]);
	        }
 		if(phunit_final_val[count*4]==0)
	        {fprintf(cfg_file,", , ,kV,1,0,0,-3.40282e+38,3.40282e+38,1,1,P\n");
	        //printf(", , ,kV,1,0,0,-3.40282e+38,3.40282e+38,1,1,P\n");}//channel_multiplier=1 channel ocfg_fileset=0
	        }
	        else if(phunit_final_val[count*4]==1)
	        {fprintf(cfg_file,", , ,kA,1,0,0,-3.40282e+38,3.40282e+38,1,1,P\n");
	        //printf(", , ,kA,1,0,0,-3.40282e+38,3.40282e+38,1,1,P\n");}
	        }
	        count++;	    
}

/*
printf("\n\n");
printf("\t%d\t\n",phunit_final_val[0]);
printf("\t%d\t\n",phunit_final_val[4]);
printf("\n\n");
printf("\t%d\t\n",anunit_final_val[0]);
printf("\t%d\t\n",anunit_final_val[4]);
printf("\t%d\t\n",anunit_final_val[8]);
printf("\t%d\t\n",anunit_final_val[12]);
printf("\t%d\t\n",anunit_final_val[16]);
printf("\t%d\t\n",anunit_final_val[20]);

printf("\n\n"); */

//printf("Digital Channels\n");
count=0;
analog=1;
for(int local_count=0; local_count< (dgnmr*16); local_count++)
{
fprintf(cfg_file,"%d,",analog++);
//printf("%d,",analog-1);	
	for(int local_count_1=0; local_count_1< 16; local_count_1++) 
		{ //if(cfg_info->cfg_digital_channels[local_count_1+count*16]!=' ')
		flag_space=0;
		for(int local_count_2=local_count_1;local_count_2<16;local_count_2++)  //Checking for space
			{if(cfg_info->cfg_digital_channels[local_count_2+count*16]!=' ') flag_space=1;}
		if(flag_space==0) break;
	         //printf("%c",cfg_info->cfg_digital_channels[local_count_1+count*16]);
	         fprintf(cfg_file,"%c",cfg_info->cfg_digital_channels[local_count_1+count*16]);
	        }
	        count++;
	        fprintf(cfg_file,", , ,0\n");
	        //printf(", , ,0\n");
}
	        fprintf(cfg_file,"%d\n",f);
	        //printf("%d\n",f);

	        fprintf(cfg_file,"%s\n","1");
	        //printf("%s\n","1");
	        
	        
	        //fprintf(cfg_file,"%d,",cfg_info->cfg_dataRate);
	        //printf("%d,",cfg_info->cfg_dataRate);
	        
	        int datarate_1=1000;
	       fprintf(cfg_file,"%d,",1000);
	       //printf("%d,",1000);
	        
        
	        fprintf(cfg_file,"%.0f\n",end_sample);
	        //printf("%.0f\n",end_sample);
	        
	       fprintf(cfg_file,"%s\n",start_time);
	        //printf("%s\n",start_time);
	        	       
	       fprintf(cfg_file,"%s\n","Time_trigger");
	        //printf("%s\n","Time_trigger");
	        
	        fprintf(cfg_file,"%s\n","float32");
	        //printf("%s\n","float32");
	        	        
	        fprintf(cfg_file,"%s\n","1000");//time_stamp_multiplication_factor
	        //printf("%s\n","1000");
	        	        
	       fprintf(cfg_file,"%s\n","+5h30,+5h30");
	        //printf("%s\n","+5h30,+5h30");
	        
	       fprintf(cfg_file,"%s\n","0000,0");
	        //printf("%s\n","0000,0");	        
fclose(cfg_file);
}

//Read config file
void read_config(){
/* local Variables*/
	int  j, a, x1, tmp_k;
	int tempi, indx = 0;
	char stn[17],*rline = NULL, *d1;
	unsigned char cline[MAX_STRING_SIZE];

	size_t len = 0;
	ssize_t read;
	FILE *fp2;

	/* Open the saved PMU Setup File and read the CFG frame if any? */
	//fp2 = fopen (pmuFilePath,"rb");
	fp2 = fopen ("pmu12345.bin","rb");

	if (fp2 != NULL)
	{
		tempi = 1;
		while(tempi < 6)
		{
			read = getline(&rline, &len, fp2);

			if(read == 0)
				break;

			tempi++;
		}

		if(read > 0)
		{
			d1 = strtok (rline," ");
			d1 = strtok (NULL," ");
			tempi = atoi(d1);

			if (tempi == 1)
			{
				d1 = strtok (NULL,"\n");
				tempi = atoi(d1);

				/* Copy the full Configuration Frame into 'cline' array */
				memset(cline,'\0',sizeof(cline));
				fread(cline, sizeof(unsigned char), tempi, fp2);
				fclose(fp2);

				/* Allocate the memory for ConfigurationFrame object */
				cfg_info = malloc(sizeof(struct ConfigurationFrame));
				cfg_info->cfg_STNname = malloc(17);

				/* Get the CFG size & store globaly */
				temp[0] = cline[2];
				temp[1] = cline[3];
				cfg2_frm_size = c2i(temp);

				/* Get the PMU ID from CFG FRM & store globally */
				temp[0] = cline[4];
				temp[1] = cline[5];
				pmu_id = c2i(temp);
				cfg_info->cfg_pmuID = pmu_id;

				/* Get the PMU ID from CFG FRM & store globally */
				temp_1[0] = cline[14];
				temp_1[1] = cline[15];
				temp_1[2] = cline[16];
				temp_1[3] = cline[17];
				//TB = c2li(temp_1);

				/* Get the Station name from CFG FRM & store globally */
				for(a=0; a<16; a++)
				{
					stn[a] = cline[20+a];
				}
				stn[16] = '\0';
				strcpy(cfg_info->cfg_STNname, stn);

				/* Get the FORMAT word from CFG FRM */
				temp[0] = cline[38];
				temp[1] = cline[39];
				frmt = c2i(temp);

				/* Initialize the frmt bits as in his appropriate global variable */
				if(frmt == 15)
				{
					fdf=1, af=1, pf=1, pn=1;
				}
				else if(frmt == 14)
				{
					fdf=1, af=1, pf=1, pn=0;
				}
				else if(frmt == 13)
				{
					fdf=1, af=1, pf=0, pn=1;
				}
				else if(frmt == 12)
				{
					fdf=1, af=1, pf=0, pn=0;
				}
				else if(frmt == 11)
				{
					fdf=1, af=0, pf=1, pn=1;
				}
				else if(frmt == 10)
				{
					fdf=1, af=0, pf=1, pn=0;
				}
				else if(frmt == 9)
				{
					fdf=1, af=0, pf=0, pn=1;
				}
				else if(frmt == 8)
				{
					fdf=1, af=0, pf=0, pn=0;
				}
				else if(frmt == 7)
				{
					fdf=0, af=1, pf=1, pn=1;
				}
				else if(frmt == 6)
				{
					fdf=0, af=1, pf=1, pn=0;
				}
				else if(frmt == 5)
				{
					fdf=0, af=1, pf=0, pn=1;
				}
				else if(frmt == 4)
				{
					fdf=0, af=1, pf=0, pn=0;
				}
				else if(frmt == 3)
				{
					fdf=0, af=0, pf=1, pn=1;
				}
				else if(frmt == 2)
				{
					fdf=0, af=0, pf=1, pn=0;
				}
				else if(frmt == 1)
				{
					fdf=0, af=0, pf=0, pn=1;
				}
				else
				{
					fdf=0, af=0, pf=0, pn=0;
				}

				/* Store FORMAT in global data structure */
				cfg_info->cfg_fdf = fdf;
				cfg_info->cfg_af = af;
				cfg_info->cfg_pf = pf;
				cfg_info->cfg_pn = pn;

				/* Get the PHNMR from CFG FRM & store globally */
				temp[0] = cline[40];
				temp[1] = cline[41];
				phnmr = c2i(temp);
				cfg_info->cfg_phnmr_val = phnmr;

				/* Get the ANNMR from CFG FRM & store in globally */
				temp[0] = cline[42];
				temp[1] = cline[43];
				annmr = c2i(temp);
				cfg_info->cfg_annmr_val = annmr;

				/* Get the DGNMR from CFG FRM & store globally */
				temp[0] = cline[44];
				temp[1] = cline[45];
				dgnmr = c2i(temp);
				cfg_info->cfg_dgnmr_val = dgnmr;

				/* To escape the some of fields in cfg frame */
				indx = 46 + (16*phnmr) + (16*annmr) + (256*dgnmr) + (4*phnmr) + (4*annmr) + (4*dgnmr); //+ 2;
				
				temp[0] = cline[indx++];
				temp[1] = cline[indx++];
				
				f= c2i(temp);
				if(f==0) f=60;
				else f=50;
				
				
				temp[0] = cline[indx++];
				temp[1] = cline[indx++];
				cfgcnt = c2i(temp);

				/* Get the Data Rate from CFG FRM & store globally */
				temp[0] = cline[indx++];
				temp[1] = cline[indx++];
				data_rate = c2i(temp);
				cfg_info->cfg_dataRate = data_rate;

				/* Seprate the Phasor Channels from CFG FRM & store globally */
				cfg_info->cfg_phasor_channels = (char *)malloc((phnmr*16) * sizeof(char));

				for(x1=0, indx=46; x1< (phnmr*16); x1++,indx++)
				{
					cfg_info->cfg_phasor_channels[x1] = cline[indx];
				}

				/* Seprate the Analog Channels from CFG FRM & store globally */
				cfg_info->cfg_analog_channels = (char *)malloc((annmr*16) * sizeof(char));

				for(x1=0, indx; x1< (annmr*16); x1++,indx++)
				{
					cfg_info->cfg_analog_channels[x1] = cline[indx];
				}

				/* Seprate the Digital Channels from CFG FRM & store globally */
				cfg_info->cfg_digital_channels = (char *)malloc((dgnmr*16*16) * sizeof(char));

				for(x1=0, indx; x1< (dgnmr*16*16); x1++,indx++)
				{
					cfg_info->cfg_digital_channels[x1] = cline[indx];
				}

				/* Insert FACTOR VALUES for Phasor, Analog and Digital in new CFG frame */
				for(j=0, tmp_k=0; j<cfg_info->cfg_phnmr_val; j++)/* FACTOR VALUES for Phasor */
				{
					phunit_final_val[tmp_k++] = cline[indx++];
					phunit_final_val[tmp_k++] = cline[indx++];
					phunit_final_val[tmp_k++] = cline[indx++];
					phunit_final_val[tmp_k++] = cline[indx++];

					//{printf("\n\n%d\n",cline[indx-4]);}
					//{printf("\n%d\n\n",phunit_final_val[tmp_k-4]);}
				}
				for(j=0, tmp_k=0; j<cfg_info->cfg_annmr_val; j++)/* FACTOR VALUES for Analog */
				{
					anunit_final_val[tmp_k++] = cline[indx++];
					anunit_final_val[tmp_k++] = cline[indx++];
					anunit_final_val[tmp_k++] = cline[indx++];
					anunit_final_val[tmp_k++] = cline[indx++];
					//{printf("\n\n%d\n",cline[indx-4]);}
					//{printf("\n%d\n\n",anunit_final_val[tmp_k-4]);}		
				}
			}
		}
	

	}
	else
	{printf("\n%s\n","Config File not fund !!! \n");
	}

}
void write_data()
{FILE *dat_file;
float sampleno=0;
dat_file = fopen("data.dat","wb");
struct node *ptr = tail;
if(tail != NULL) 
	{
	for(int local_count=0;local_count<0.01*bufferlength;local_count++)
	ptr = ptr->next;    //Skipping first few values to prevent overlap with running code
	while(ptr->next != ptr) 
		{sampleno++;     
         	write_data_helper(ptr->data,sampleno,dat_file);
         	ptr = ptr->next;
      		}
      	sampleno++;
     	write_data_helper(ptr->data,sampleno,dat_file);
     	end_sample=sampleno;
   	} 	
fclose(dat_file);
}
void write_data_helper(char* temp,float sampleno,FILE* dat_file)
{ 
int field_count = 0;
float a;
int digitalcount=0;
int dig[100];                
char *field = strtok(temp, ",");
while (field) 
       {
       if(field_count == 0)  
     	    { 
     	     fwrite(&sampleno,sizeof(char),4,dat_file);
     	      if(sampleno==1) strcpy(start_time,field);
     	      // else if(sampleno==bufferlength) end_time=field;
     	     }           
       else if(field_count<=phnmr)
	    {
	    a=strtod(field , NULL);
	    fwrite(&a,sizeof(char),4,dat_file);
            }
       else if(field_count>phnmr)
	    {
	    a=strtod(field , NULL);
	    dig[digitalcount++]=(int)a;
            }
       field = strtok(NULL, ",");	
       field_count++;
       }
for(int local_count_1=0;local_count_1<dgnmr;local_count_1++)
	{
	int b=0;
	for(int local_count=0;local_count<16;local_count++)
    		b=b+dig[local_count_1+local_count]*(1<<local_count);
	fwrite(&b,sizeof(char),2,dat_file);
	}
}
int c2i (unsigned char temp[])
{
	int i;

	i = temp[0];
	i<<=8;
	i |=temp[1];
	return(i);
}

