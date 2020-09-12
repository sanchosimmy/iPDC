
CC = gcc
CFLAGS = -g

#gcc `pkg-config --cflags gtk+-3.0` -o example-1 example-1.c `pkg-config --libs gtk+-3.0`


CC = gcc
LIBS = -lpthread -lm -lrt

LDLIBS=`pkg-config --cflags --libs`
CFLAGS=`pkg-config --cflags --cflags` 

#Sancho

OBJECTS =  fread.o
CLEAN_OBJECTS = fread.o

PROGRAM = fread

COMPILE = $(CC) 

$(PROGRAM): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDLIBS) $(LIBS) -g -o $@
		rm -f $(CLEAN_OBJECTS) 

%.o: %.c
	$(COMPILE) $(CFLAGS) -c -g $<


clean:
	rm -f $(CLEAN_OBJECTS) $(PROGRAM)
