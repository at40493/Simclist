SRC = main.c
OBJS = $(SRC:.c=.o)
TARGET = main
INC_PATH = /home/ned/simclist
STATIC_FLAG = -Wl,-Bstatic
DYNAMIC_FLAG = -Wl,-Bdynamic
INFLAGS = -I $(INC_PATH)
LDFLAGS = -L $(INC_PATH)
STATIC_LIB = -lsimclist
DYNAMIC_LIB= -lsimclist
CC = gcc

all : clean $(TARGET)_dynamic $(TARGET)_static style

$(TARGET)_dynamic : $(OBJS)
	$(CC) $< $(LDFLAGS) $(DYNAMIC_FLAG) $(DYNAMIC_LIB) -Wl,-rpath=$(INC_PATH) -o $@

$(TARGET)_static : $(OBJS)
	$(CC) $< $(LDFLAGS) $(STATIC_FLAG) $(STATIC_LIB) $(DYNAMIC_FLAG) -o $@ 

%.o: %.c
	$(CC) $(INFLAGS) -c $<
	
style:  $(SRC)
	astyle --style=linux --indent=tab --pad-oper --unpad-paren $(SRC)

clean:
	rm -f $(TARGET)_dynamic $(TARGET)_static 

