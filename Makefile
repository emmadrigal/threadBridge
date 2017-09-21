APP=threadBridge
LIBFLAGS=
SRC=main.c
CC=gcc


all:
		echo "Ejecutable creado"

app:
		cd src && make

clean:
		cd src && make clean
