CP = clang

ifndef DEBUG
	CFLAGS := -O3 -fno-rtti -fno-exceptions \
		-fmerge-all-constants \
		-Wall -W -Wshadow -Wpointer-arith \
		-Wcast-qual -Wcast-align \
		-Wconversion -Wwrite-strings -pedantic

else
	CFLAGS := -Wall -W -g -DDEBUG 
endif

LIB_OBJ := bin2c.c

all: $(LIB_OBJ)
	$(CP) $(CFLAGS) $(LIB_OBJ) -o bin2c

.SUFFIXES: .c .o
.c.o:
	$(CP) -c $(CFLAGS) $< -o $@

