NAME = Infiltration

SRC = src/

CNT = 	$(SRC)terrain.c\
		$(SRC)gardien.c\
		$(SRC)relique.c\
		$(SRC)personnage.c\
		$(SRC)collision.c\
		$(SRC)graphique.c\
		$(SRC)table.c\
		$(SRC)main.c\

OBJ = $(CNT:.c=.o)

CFLAGS = -Wall -ansi -lMLV
				
LDFLAGS =

HEADER	= include -lMLV -lm

all:$(NAME)

$(NAME): $(OBJ)
	gcc $(CFLAGS) $^ -o $(NAME) $(LDFLAGS) -I $(HEADER) 

%.o:%.c
	gcc $(CFLAGS) -o $@ -c $^ -I $(HEADER)

clean:
	rm -f $(SRC)*.o

mrproper: clean
	rm -f $(NAME)

install:
	make
	make clean
	mv $(NAME) bin/
