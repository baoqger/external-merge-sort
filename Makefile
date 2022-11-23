EXSORT = exsort 

SRC = $(wildcard ./*.c)

OBJ = $(SRC:.c=.o)

CC = cc 

RM = rm 

CFLAGS = -g 
LIBS = 
LDFLAGS = 

.PHONY = clean 

all:  $(EXSORT)

debug: CFLAGS += -ggdb -O0 
debug: $(EXSORT)

$(EXSORT): $(OBJ) 
	$(CC) -o $@ $(OBJ) $(CFLAGS) $(LIBS)


.c.o:
	$(CC) -c $< $(CFLAGS)


clean:
	$(RM) ./$(OBJ) ./$(EXSORT)




