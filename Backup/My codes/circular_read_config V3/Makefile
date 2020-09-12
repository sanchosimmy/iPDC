
CC = gcc
CFLAGS = -g

#gcc `pkg-config --cflags gtk+-3.0` -o buffer buffer.c `pkg-config --libs gtk+-3.0`


CC = gcc
LIBS = -lpthread -lm -lrt
#LDLIBS=`pkg-config --cflags --libs gtk+-3.0`
#CFLAGS=`pkg-config --cflags --cflags gtk+-3.0`
LDLIBS=`pkg-config --cflags --libs gtk+-3.0`
CFLAGS=`pkg-config --cflags --cflags gtk+-3.0` 

#Sancho





OBJECTS =  buffer.o 
CLEAN_OBJECTS = buffer.o 

PROGRAM = buffer

COMPILE = $(CC) 

$(PROGRAM): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDLIBS) $(LIBS) -g -o $@
	
	rm -f $(CLEAN_OBJECTS)

%.o: %.c
	$(COMPILE) $(CFLAGS) -c -g $<


clean:
	rm -f $(CLEAN_OBJECTS) $(PROGRAM)
