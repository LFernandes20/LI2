CFLAGS=-Wall -Wextra -ansi -pedantic -O2
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))

battleship: $(OBJS)
	$(CC) $(CFLAGS) -o battleship $(OBJS) $(LIBS)

limpar:
	rm battleship *.o
