APP=threadBridge
SRC= main.c controladorEntrada.c generadorCarros.c puente.c entrada.c carro.c sched.c

CC=gcc
CFLAGS = `pkg-config --cflags glib-2.0 libconfig` -Wall  -Wno-incompatible-pointer-types -Wno-int-conversion -g
LIB_FLAGS= -I../include `pkg-config --libs glib-2.0 libconfig` -lm -lpthread #-L/home/emmanuel/Documents/Operativos/threadBridge/lib/glibc-2.23/build/usr/lib -L./lib/glibc-2.23/build/usr/include


all:
	$(CC) -o ../bin/$(APP) $(SRC) $(LIB_FLAGS) $(CFLAGS) 

clean:
	rm ../bin/$(APP)
	
