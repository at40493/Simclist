SRC = main.c
TARGET = $(SRC:.c=)
INC_PATH = ~/simclist/
CFLAGS = -Wl,-Bstatic
INFLAGS = -I $(INC_PATH)
LDFLAGS = -L $(INC_PATH)
LDLIBS = -lsimclist
CC = gcc

all : clean $(TARGET)_dynamic $(TARGET)_static style

$(TARGET)_dynamic : $(SRC)
	$(CC) $< $(LDFLAGS) $(LDLIBS) $(INFLAGS) -o $@

$(TARGET)_static : $(SRC)
	$(CC) $< $(LDFLAGS) $(CFLAGS) $(LDLIBS) -Wl,-Bdynamic -lgcc_s $(INFLAGS) -o $@ 
	
style:  $(SRC)
	astyle --style=linux --indent=tab --pad-oper --unpad-paren $(SRC)

clean:
	rm -f $(TARGET)_dynamic $(TARGET)_static 

