# Macros ######################################################################
assert_cmd = $(if $(shell where $1),$1,$(error "There is no $1 in $$PATH"))

# User config #################################################################
EXECUTABLE   := main
OL           := 3
DL           := gdb3
STD          := c11
WARNINGS     := all extra

# Project config ##############################################################
CFLAGS       := -std=$(STD) -O$(OL) $(addprefix -W,$(WARNINGS)) -g$(DL)

DRAKON_SQL   := CardValidityCheck.sql
DRAKON_FILES := $(DRAKON_SQL:.sql=.drn)
DRAKON_PATH  := /cygdrive/c/opt/Drakon\ Editor/1.31
DRAKON_GEN   := $(DRAKON_PATH)/drakon_gen.tcl
DRAKON_CFILES:= $(DRAKON_FILES:.drn=.c)
DRAKON_HFILES:= $(DRAKON_FILES:.drn=.h)

SOURCES      := $(sort $(wildcard *.c) $(DRAKON_CFILES))
HEADERS      := $(sort $(wildcard *.h) $(DRAKON_HFILES))
OBJECTS      := $(SOURCES:.c=.o)
DEPENDS      := $(SOURCES:.c=.d)

CSCOPE_REF   := cscope.out

# Commands ####################################################################
CSCOPE       := $(call assert_cmd,cscope) $(if $(VERBOSE),-v,)
CLANG_FORMAT := $(if $(USE_CLANG_FORMAT),$(call assert_cmd,clang-format),@true)
RM           := rm $(if $(VERBOSE),-v,)
OBJCOPY      := objcopy $(if $(VERBOSE),-v,)
SQLITE3      := $(call assert_cmd,sqlite3)

# Targets that do not need *.d dependencies for source files
NOT_DEP      := clean asm pp wipe update

.PRECIOUS: %.drn

.PHONY: all clean asm pp run index update
all: $(EXECUTABLE) index .syntastic_c_config
asm: $(SOURCES:.c=.s)
pp: $(SOURCES:.c=.i)
run: $(EXECUTABLE)
	./$<
index: $(CSCOPE_REF)
update: $(DRAKON_FILES)
	$(SQLITE3) -batch $< '.dump' >$(DRAKON_SQL)

include $(if $(filter $(NOT_DEP),$(MAKECMDGOALS)),,$(DEPENDS))

$(CSCOPE_REF): $(SOURCES) $(HEADERS)
	$(CSCOPE) -f$@ -b $^
clean: F += $(wildcard $(EXECUTABLE) $(EXECUTABLE).fat $(DRAKON_CFILES) $(DRAKON_HFILES) $(CSCOPE_REF) *.o *.s *.i *.d *.csv)
clean:
	-$(if $(strip $F),$(RM) -- $F,)
wipe: F += $(wildcard $(DRAKON_FILES) .syntastic_c_config)
wipe: clean

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
%.d: %.c
	$(CC) -MM -MF $@ $(CFLAGS) -o $@ $<
%.s: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -S -o $@ $<
%.i: %.c
	$(CC) $(CPPFLAGS) -E -o $@ $<
%.drn: %.sql
	$(SQLITE3) -batch $@ <$<
	chmod a-x $@

.syntastic_c_config: Makefile
	echo $(CFLAGS) | tr ' ' '\n' > $@

.PHONY: csv
csv: $(DRAKON_FILES:.drn=.csv)
%.csv: %.drn SelectItemMsg.sql
	$(SQLITE3) -batch -csv $< <SelectItemMsg.sql >$@
