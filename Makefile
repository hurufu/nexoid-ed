EXECUTABLE   := main

DRAKON_FILES := PaymentCompletion.drn
DRAKON_PATH  := /cygdrive/c/opt/drakon_editor1.31
DRAKON_GEN   := $(DRAKON_PATH)/drakon_gen.tcl
DRAKON_CFILES:= $(DRAKON_FILES:.drn=.c)
DRAKON_HFILES:= $(DRAKON_FILES:.drn=.h)

SOURCES      := $(sort $(wildcard *.c) $(DRAKON_CFILES))
HEADERS      := $(sort $(wildcard *.h) $(DRAKON_HFILES))
OBJECTS      := $(SOURCES:.c=.o)
DEPENDS      := $(SOURCES:.c=.d)

CSCOPE_REF   := cscope.out

NOT_DEP      := clean asm pp
include $(if $(filter $(NOT_DEP),$(MAKECMDGOALS)),,$(DEPENDS))

.PHONY: all clean asm pp run index
all: $(EXECUTABLE) index
asm: $(SOURCES:.c=.s)
pp: $(SOURCES:.c=.i)
run: $(EXECUTABLE)
	./$<
index: $(CSCOPE_REF)
$(CSCOPE_REF): $(SOURCES) $(HEADERS)
	cscope -f$@ -b $^
clean: F := $(wildcard $(EXECUTABLE) $(DRAKON_CFILES) $(DRAKON_HFILES) $(CSCOPE_REF) *.o *.s *.i *.d)
clean:
	-$(if $(strip $F),rm -v -- $F,)

$(EXECUTABLE): $(OBJECTS)
	$(LINK.o) -o $@ $^

# Workaround
main.d: main.c | $(DRAKON_HFILES)

.PRECIOUS: %.c %.h
%.c %.h: %.drn
	$(DRAKON_GEN) -in $< -ext c
%.d: %.c
	$(CC) -MM -MF $@ $(CFLAGS) -o $@ $<
%.s: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -S -o $@ $<
%.i: %.c
	$(CC) $(CPPFLAGS) -E -o $@ $<
