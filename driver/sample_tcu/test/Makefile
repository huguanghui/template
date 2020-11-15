#CC = gcc
#CC=mips_fp_le-gcc
#CC=powerpc-linux-gcc-3.4.3 
#CC=arm-none-linux-gnueabi-gcc
CC=mips-linux-gnu-gcc

CFLAG=  -lpthread -muclibc
INCLUDE = 
#GTK_LIB = `pkg-config --libs gtk+-2.0`
#GTK_INC = `pkg-config --cflags gtk+-2.0`



SRC = $(wildcard *.c)
BIN = test

all:
	$(CC) -g -o $(BIN) $(SRC) $(INCLUDE) $(CFLAG) $(X_CFLAGS) $(X_LIBS) $(GTK_LIB) $(GTK_INC)
	
clean:
	rm -f *.o
	rm -f $(BIN)

