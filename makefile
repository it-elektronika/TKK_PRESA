CC=gcc
CFLAGS=-Wall -Wextra -pedantic -I /usr/local/include/modbus
LIBS=-lSDL2 -lSDL2_image -lSDL2_ttf -lm -L/usr/local/lib -lmodbus


tkk_presa:  main.o graphics_sdl.o pages.o 
	$(CC) -o tkk_presa main.o graphics_sdl.o pages.o  -I. $(LIBS) $(DEPS)

.PHONY:clean

clean:
	find . -name "*.o" -type f -delete
	
                                      
