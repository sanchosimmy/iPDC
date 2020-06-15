
CC = gcc
CFLAGS = -g

#gcc `pkg-config --cflags gtk+-3.0` -o example-1 example-1.c `pkg-config --libs gtk+-3.0`


CC = gcc
LIBS = -lpthread -lm -lrt
#LDLIBS=`pkg-config --cflags --libs gtk+-3.0`
#CFLAGS=`pkg-config --cflags --cflags gtk+-3.0`
LDLIBS=`pkg-config --cflags --libs gtk+-3.0`
CFLAGS=`pkg-config --cflags --cflags gtk+-3.0` 



OBJECTS =  example-1.o
CLEAN_OBJECTS = example-1.o

PROGRAM = example-1

COMPILE = $(CC) 

$(PROGRAM): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDLIBS) $(LIBS) -g -o $@

%.o: %.c
	$(COMPILE) $(CFLAGS) -c -g $<


clean:
	rm -f $(CLEAN_OBJECTS) $(PROGRAM)
