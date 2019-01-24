EXECUTABLE   := main

DRAKON_FILES := PaymentCompletion.drn
DRAKON_PATH  := /cygdrive/c/opt/drakon_editor1.31
DRAKON_GEN   := $(DRAKON_PATH)/drakon_gen.tcl
DRAKON_CFILES:= $(DRAKON_FILES:.drn=.c)
DRAKON_HFILES:= $(DRAKON_FILES:.drn=.h)

SOURCES      := main.c $(DRAKON_CFILES)
OBJECTS      := $(SOURCES:.c=.o)
DEPENDS      := $(SOURCES:.c=.d)

NOT_DEP      := clean asm pp
include $(if $(filter $(NOT_DEP),$(MAKECMDGOALS)),,$(DEPENDS))

.PHONY: all clean asm pp run
all: $(EXECUTABLE)
asm: $(SOURCES:.c=.s)
pp: $(SOURCES:.c=.i)
run: $(EXECUTABLE)
	./$<
clean: F := $(wildcard $(EXECUTABLE) $(DRAKON_CFILES) $(DRAKON_HFILES) *.o *.s *.i *.d)
clean:
	-$(if $(strip $F),rm -v -- $F,)

$(EXECUTABLE): $(OBJECTS)
	$(LINK.o) -o $@ $^

.PRECIOUS: %.c %.h
%.c %.h: %.drn
	$(DRAKON_GEN) -in $< -ext c
%.d: %.c
	$(CC) -MM -MF $@ $(CFLAGS) -o $@ $<
%.s: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -S -o $@ $<
%.i: %.c
	$(CC) $(CPPFLAGS) -E -o $@ $<
