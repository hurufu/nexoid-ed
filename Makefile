EXECUTABLE   := main

DRAKON_FILES := PaymentCompletion.drn
DRAKON_PATH  := /cygdrive/c/opt/drakon_editor1.31
DRAKON_GEN   := $(DRAKON_PATH)/drakon_gen.tcl

SOURCES      := $(DRAKON_FILES:.drn=.c) main.c
OBJECTS      := $(SOURCES:.c=.o)

.PHONY: all clean asm pp
all: $(EXECUTABLE)
asm: $(SOURCES:.c=.s)
pp: $(SOURCES:.c=.i)
clean:
	rm -- $(DRAKON_FILES:.drn=.c) $(DRAKON_FILES:.drn=.h) *.o $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(LINK.o) -o $@ $^

%.c %.h: %.drn
	$(DRAKON_GEN) -in $< -folder $(*D) -ext c

%.s: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -S -o $@ $<
%.i: %.c
	$(CC) $(CPPFLAGS) -E -o $@ $<
