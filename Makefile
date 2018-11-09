INC_PATH= /home/ned/simclist
LDLIBS=-lsimclist
LDFLAGS= -L $(INC_PATH)
TARGET= main_dynamic main_static
CC=gcc

all:
	
	#build static
	make main_static LDLIBS="-Wl,-Bstatic $(LDLIBS) -Wl,-Bdynamic "
	
	#build dynamic
	make main_dynamic LDLIBS="-Wl,-Bdynamic $(LDLIBS) -Wl,-rpath=$(INC_PATH) "
	
	#clean
	make clean
	
$(TARGET):%:main.o
	$(CC) $< $(LDFLAGS) $(LDLIBS) -o $@

style:  main.c
	astyle --style=linux --indent=tab --pad-oper --unpad-paren main.c

clean:
	rm -f *.o 
