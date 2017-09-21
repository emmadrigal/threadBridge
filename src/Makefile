APP=threadBridge
SRC= controladorEntrada.c generadorCarros.c main.c puente.c entrada.c

CC=gcc
CFLAGS = `pkg-config --cflags glib-2.0`  -Wall 
LIB_FLAGS= -I../include `pkg-config --libs glib-2.0` -lpthread 


all:
	$(CC) -o ../bin/$(APP) $(SRC) $(LIB_FLAGS) $(CFLAGS) 

clean:
	rm ../bin/$(APP)
	
