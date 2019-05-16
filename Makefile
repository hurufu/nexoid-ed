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
CFLAGS       += $(if $(filter trace,$(MAKECMDGOALS)),-finstrument-functions,)

DRAKON_SQL   := NexoFast.sql
DRAKON_FILES := $(DRAKON_SQL:.sql=.drn)
DRAKON_PATH  ?= /cygdrive/c/opt/Drakon\ Editor/1.31
DRAKON_CFILES:= $(DRAKON_FILES:.drn=.c)
DRAKON_HFILES:= $(DRAKON_FILES:.drn=.h)

SOURCES      := $(sort $(if $(filter trace,$(MAKECMDGOALS)),$(wildcard *.c),$(filter-out instrumentation.c,$(wildcard *.c))) $(DRAKON_CFILES))
HEADERS      := $(sort $(wildcard *.h) $(DRAKON_HFILES))
OBJECTS      := $(SOURCES:.c=.o)
DEPENDS      := $(SOURCES:.c=.d)

CSCOPE_REF   := cscope.out

TIME_RESULT  := time.yaml
TIME_ARGS    := --format=' - { user: %U, system: %S, real: "%E", cpu: "%P", command: "%C" }' --append --output $(TIME_RESULT)

# Commands ####################################################################
TIME         := $(if $(PROFILE_BUILD),$(call assert_cmd,time) $(TIME_ARGS),)
CSCOPE       := $(TIME) $(call assert_cmd,cscope) $(if $(VERBOSE),-v,)
CLANG_FORMAT := $(if $(USE_CLANG_FORMAT),$(call assert_cmd,clang-format),@true)
RM           := rm $(if $(VERBOSE),-v,)
OBJCOPY      := $(TIME) objcopy $(if $(VERBOSE),-v,)
ADDR2LINE    := $(TIME) addr2line
SQLITE3      := $(TIME) $(call assert_cmd,sqlite3)
DDD          := $(TIME) $(call assert_cmd,ddd)
ifdef USE_CCACHE
CCACHE       := $(call assert_cmd,ccache)
endif
CC           := $(TIME) $(if $(USE_CCACHE),$(CCACHE) gcc,gcc)
CFLOW        := $(TIME) $(call assert_cmd,cflow)
DRAKON_GEN   := $(TIME) '$(DRAKON_PATH)/drakon_gen.tcl'

# Targets that do not need *.d dependencies for source files
NOT_DEP      := clean asm pp wipe update

.PRECIOUS: %.drn

.PHONY: all clean asm pp run index update
all: $(EXECUTABLE) index .syntastic_c_config cflow
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
clean: F += $(wildcard $(EXECUTABLE) $(EXECUTABLE).fat $(DRAKON_CFILES) $(DRAKON_HFILES) $(CSCOPE_REF) *.o *.s *.i *.csv trace.log *.cflow *.expand *.png $(TIME_RESULT))
clean:
	-$(if $(strip $F),$(RM) -- $F,)
wipe: F += $(wildcard $(DRAKON_FILES) .syntastic_c_config *.d *.stackdump)
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

.PHONY: ddd
ddd: $(EXECUTABLE)
	$(DDD) $<

.PHONY: trace
trace: trace.log
	$(ADDR2LINE) -spf -e $(EXECUTABLE) <$< | paste $< -
trace.log: $(EXECUTABLE)
	./$<

.PHONY: cflow
cflow: main.cflow
main.cflow:
	$(CFLOW) --no-ansi --omit-symbol-names $(SOURCES) > $@

.PHONY: cg
cg: cg.png
cg.png:
	$(CC) -o main $(CPPFLAGS) $(CFLAGS) -fdump-rtl-expand $(SOURCES)
	egypt *.expand | dot -Tpng > callgraph.png

.PHONY: print-%
print-%:
	@:$(info $($*))
