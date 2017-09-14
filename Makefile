APP=threadBridge
LIBFLAGS=
SRC=main.c
CC=gcc


all:
		$(CC) -o bin/$(APP) src/$(SRC)

clean:
		rm bin/$(APP)
