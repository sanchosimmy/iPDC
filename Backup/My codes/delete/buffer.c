#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include<math.h>


#include <stdint.h> ////for uint16_t



float ReverseFloat( const float inFloat );
void reverseprint(float inFloat );


//Main program ####################################################    Main program
void main() 
{
//unsigned aaaa=0x12345678;
//printf("%02x%02x%02x%02x ", aaaa & 255, (aaaa / 256) & 255, (aaaa / (256*256)) & 255, (aaaa / (256*256*256)) & 255); 
FILE *ff;
ff = fopen("dat.dat","wb");
float aaaa=120.05;
//reverseprint(aaaa);
fwrite(&aaaa,sizeof(char),4,ff);	        
fclose(ff);


//printf("%a\n",aaaa);
 //printf("%02x%02x%02x%02x ", aaaa & 255, (aaaa / 256) & 255, (aaaa / (256*256)) & 255, (aaaa / (256*256*256)) & 255); 
//printf("%a\n",ReverseFloat(aaaa));
//printf("%a\n",ReverseFloat(ReverseFloat(aaaa)));
}
void reverseprint(float inFloat)
{char *floatToConvert = (char* ) & inFloat;


  printf("%c ",*(floatToConvert));
  printf("%c ",*(floatToConvert+1));
    printf("%c ",*(floatToConvert+2));
      printf("%c ",*(floatToConvert+3));
}
float ReverseFloat( const float inFloat )
{
   float retVal;
   char *floatToConvert = ( char* ) & inFloat;
   char *returnFloat = ( char* ) & retVal;



   // swap the bytes into a temporary buffer
  // memcpy(returnFloat,floatToConvert+3,sizeof(char));
  // memcpy(returnFloat+1,floatToConvert+2,sizeof(char));
  // memcpy(returnFloat+2,floatToConvert+1,sizeof(char));
  // memcpy(returnFloat+3,floatToConvert,sizeof(char));

   *(returnFloat)=*(floatToConvert+3);
   *(returnFloat+1)=*(floatToConvert+2);
   *(returnFloat+2)=*(floatToConvert+1);
   *(returnFloat+3)=*(floatToConvert);


   return retVal;
}

