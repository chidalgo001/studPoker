#makefile variables

CC = gcc
OUT_EXE = poker.out
FILES = main.c cards.c studPoker.c

#---

all: $(FILES)
	$(CC) $(FILES) -o $(OUT_EXE)

clean:	
	rm -rf *o $(OUT_EXE)

rebuild: clean all
