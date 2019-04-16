EXECUTABLE   := main
OL           := 3
DL           := gdb3
CFLAGS       := -std=c11 -O$(OL) -Wall -Wextra -g$(DL)

DRAKON_FILES := $(wildcard *.drn)
DRAKON_PATH  := /cygdrive/c/opt/Drakon\ Editor/1.31
DRAKON_GEN   := $(DRAKON_PATH)/drakon_gen.tcl
DRAKON_CFILES:= $(DRAKON_FILES:.drn=.c)
DRAKON_HFILES:= $(DRAKON_FILES:.drn=.h)

SOURCES      := $(sort $(wildcard *.c) $(DRAKON_CFILES))
HEADERS      := $(sort $(wildcard *.h) $(DRAKON_HFILES))
OBJECTS      := $(SOURCES:.c=.o)
DEPENDS      := $(SOURCES:.c=.d)

CSCOPE_REF   := cscope.out
CSCOPE       := cscope
CLANG_FORMAT := $(if $(USE_CLANG_FORMAT),clang-format,@true)
RM           := $(if $(VERBOSE),rm -vf,rm -f)
OBJCOPY      := objcopy

NOT_DEP      := clean asm pp

.PHONY: all clean asm pp run index
all: $(EXECUTABLE) index
asm: $(SOURCES:.c=.s)
pp: $(SOURCES:.c=.i)
run: $(EXECUTABLE)
	./$<
index: $(CSCOPE_REF)

include $(if $(filter $(NOT_DEP),$(MAKECMDGOALS)),,$(DEPENDS))

$(CSCOPE_REF): $(SOURCES) $(HEADERS)
	$(CSCOPE) -f$@ -b $^
clean: F := $(wildcard $(EXECUTABLE) $(EXECUTABLE).fat $(DRAKON_CFILES) $(DRAKON_HFILES) $(CSCOPE_REF) *.o *.s *.i *.d)
clean:
	-$(if $(strip $F),$(RM) -- $F,)

$(EXECUTABLE).fat: $(OBJECTS)
	$(LINK.o) -o $@ $^
$(EXECUTABLE): $(EXECUTABLE).fat
	$(OBJCOPY) --strip-unneeded --add-gnu-debuglink=$(<D)/$< $< $@

# Workaround
main.d: main.c | $(DRAKON_HFILES)

.PRECIOUS: %.c %.h
%.c %.h: %.drn
	$(DRAKON_GEN) -in $<
	$(CLANG_FORMAT) -i $*.c $*.h
	chmod a-w $*.c $*.h
%.d: %.c
	$(CC) -MM -MF $@ $(CFLAGS) -o $@ $<
%.s: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -S -o $@ $<
%.i: %.c
	$(CC) $(CPPFLAGS) -E -o $@ $<

.syntastic_c_config: Makefile
	echo $(CFLAGS) | tr ' ' '\n' > $@
