# change application name here (executable output name)
TARGET=appAdmin

# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O6
# warnings
WARN=-Wall

WEXTRA=-Wextra

PTHREAD=-pthread

CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(WEXTRA)  $(PTHREAD) -pipe

GTKLIB=`pkg-config --cflags --libs gtk+-3.0`
MYSQL=`mysql_config --libs --cflags`
# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB)  $(MYSQL) -export-dynamic

OBJS=    main.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)

main.o: src/main.c
	$(CC) -c $(CCFLAGS) src/main.c $(GTKLIB) $(MYSQL) -o main.o

clean:
	rm -f *.o $(TARGET)
