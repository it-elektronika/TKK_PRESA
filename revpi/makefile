CC=gcc
CFLAGS=-g -Wall -Wextra -pedantic -I /usr/local/include/modbus
LIBS= -lm -lmodbus

tkk_presa_revpi:  main.o kunbus.o 
	$(CC) -o tkk_presa_revpi main.o kunbus.o -I. $(LIBS) $(DEPS)

.PHONY:clean

clean:
	find . -name "*.o" -type f -delete
	rm tkk_presa_revpi
