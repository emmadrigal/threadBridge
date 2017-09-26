APP=threadBridge
LIBFLAGS=
SRC=main.c
CC=gcc


all: app
		echo "Ejecutable creado"

app:
		cd src && make

clean:
		cd src && make clean
