SRS = simclist.c
TARGET = $(SRS:.c=)
INC_PATH = ~/simclist/
CFLAGS = -static
INFLAGS = -I $(INC_PATH)
LDFLAGS = -L $(INC_PATH) $(LDLIBS)
LDLIBS = -lsimclist

all : clean $(TARGET)_dynamic $(TARGET)_static style

$(TARGET)_dynamic : $(SRS)
	gcc $< $(LDFLAGS) $(INFLAGS) -o $@

$(TARGET)_static : $(SRS)
	gcc $< $(LDFLAGS) $(INFLAGS) $(CFLAGS) -o $@ 
	
style:  $(SRS)
	astyle --style=linux --indent=tab --pad-oper --unpad-paren $(SRS)

clean:
	rm -f $(TARGET)_dynamic $(TARGET)_static 

