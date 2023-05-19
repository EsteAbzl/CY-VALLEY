all: main

CC = clang
override CFLAGS += -g -Wno-everything -pthread -lm -lncursesw

##ajout pour compiler les fichier de src directement
DIR_SRC = src/
DIR_INC = src/
SRCS = $(wildcard $(DIR_SRC)*.c)
HEADERS = $(wildcard $(DIR_INC)*.h)


main: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o "$@"	

main-debug: $(SRCS) $(HEADERS)
	$(CC) -c $(CFLAGS) -O0 $(SRCS) -o "$@"

clean:
	rm -f main main-debug