# Macros ######################################################################
# FIXME: Remove macros from here and user system-wide `makes` installation
# Define MAKE_DEBUG to any non-empty value in order to debug all variable
# definedness tests
#MAKE_DEBUG := y

# Message to be shown while debuging variables
MAKE_DEBUG_MSG = $(warning $(origin $1) defined variable "$1" is \
                 "$(value $1)" expanded to "$($1)")

debug = $(if $(MAKE_DEBUG),$(MAKE_DEBUG_MSG))

# Call function $1 if variable is not defined
do_ifndef = $(foreach S,$2,$(if $($S),$(call debug,$S),$(call $1,$S is undefined)))

# Stop execution if any variable from the list is undefined
assert_defined = $(call do_ifndef,error,$1)

# Issue a warning if any variable from the list is undefined
check_defined = $(call do_ifndef,warning,$1)


assert_cmd = $(if $(shell which $1),$1,$(error "There is no $1 in $$PATH"))

# User config #################################################################
OL           := g
DL           := gdb3
STD          := gnu11
WARNINGS     := all extra
PREFIX       := /usr/local

# Project config ##############################################################
NAME         := nexoid
INCLUDE_DIRS := . $(shell find include -type d)
# TODO: Develop proper pkg-config for dependencies
LIBRARIES    := ptmalloc3 pthread

# Toolchain settings ##########################################################
CPPFLAGS     := $(addprefix -I,$(INCLUDE_DIRS))
CFLAGS       := -std=$(STD) -O$(OL) $(addprefix -W,$(WARNINGS)) -g$(DL) -fPIC
CFLAGS       += $(if $(filter trace,$(MAKECMDGOALS)),-finstrument-functions,)
CFLAGS       += -fplan9-extensions
#CFLAGS       += -fdiagnostics-color=always
CFLAGS       += -march=native -mtune=native
CFLAGS       += $(if $(INSTRUMENT_FUNCTIONS),-finstrument-functions,)
LDLIBS       := $(addprefix -l,$(LIBRARIES))
VERSION       = $(shell git describe --dirty --broken)

LIBNAME          := lib$(NAME)
LIBNAME.a        := $(LIBNAME).a
LIBNAME.so       := $(LIBNAME).so
LIBNAME.so.debug := $(LIBNAME).so.debug

DRAKON_SQL   := NexoFast.sql
DRAKON_FILES := $(DRAKON_SQL:.sql=.drn)
DRAKON_PATH  ?= /cygdrive/c/opt/Drakon\ Editor/1.31
DRAKON_CFILES:= $(DRAKON_FILES:.drn=.c)
DRAKON_HFILES:= $(DRAKON_FILES:.drn=.h)

SOURCES      := $(sort $(wildcard *.c) $(DRAKON_CFILES))
HEADERS      := $(sort $(wildcard $(addsuffix /*.h,$(INCLUDE_DIRS)) $(DRAKON_HFILES)))
OBJECTS      := $(SOURCES:.c=.o)
DEPENDS      := $(SOURCES:.c=.d)

GRAPH_TARGETS := all install uninstall shared
GRAPH_IMAGES  := $(addsuffix .png,$(GRAPH_TARGETS))

INSTALLED_FILES  := $(addprefix $(PREFIX)/lib/,$(notdir $(LIBNAME).a $(LIBNAME).so))
INSTALLED_FILES  += $(addprefix $(PREFIX)/include/$(NAME)/,$(notdir $(HEADERS)))

CSCOPE_REF   := cscope.out

TIME_FORMAT    ?= pdb
TIME_RESULT    := time.$(TIME_FORMAT)
TIME_ARGS.yaml := --format=' - { user: %U, system: %S, real: "%E", cpu: "%P", command: "%C" }' --append --output $(TIME_RESULT)
TIME_ARGS.pdb  := --format='pd(user(%U), system(%S), real(%e), command("%C")).' --append --output $(TIME_RESULT)

# Commands ####################################################################
TIME         := $(if $(PROFILE_BUILD),$(call assert_cmd,time) $(TIME_ARGS.$(TIME_FORMAT)),)
CSCOPE        = $(TIME) $(call assert_cmd,cscope) $(if $(VERBOSE),-v,)
CLANG_FORMAT := $(if $(USE_CLANG_FORMAT),$(call assert_cmd,clang-format),@true)
RM           := rm $(if $(VERBOSE),-v,)
OBJCOPY      := $(TIME) objcopy $(if $(VERBOSE),-v,)
ADDR2LINE    := $(TIME) addr2line
SQLITE3      := $(TIME) $(call assert_cmd,sqlite3)
DDD           = $(TIME) $(call assert_cmd,ddd)
ifdef USE_CCACHE
CCACHE       := $(call assert_cmd,ccache)
endif
PROLOG        = $(TIME) $(call assert_cmd,gprolog)
CC           := $(TIME) $(if $(USE_CCACHE),$(CCACHE) gcc,gcc)
CFLOW         = $(TIME) $(call assert_cmd,cflow)
DRAKON_GEN   := $(TIME) '$(DRAKON_PATH)/drakon_gen.tcl'

# Build time profiling
TIME_PROC.pdb  := $(PROLOG) --consult-file time.pdb --consult-file profiling_build.pdb <profiling_build.pq

# Targets that do not need *.d dependencies for source files
NOT_DEP      := clean asm pp wipe update

.PRECIOUS: %.drn

ifdef PROFILE_BUILD
.PHONY: profile_build
profile_build: all profiling_build.pdb profiling_build.pq
	$(TIME_PROC.$(TIME_FORMAT))
endif

.PHONY: all clean asm pp index update static shared
all: shared static index .syntastic_c_config cflow
asm: $(SOURCES:.c=.s)
pp: $(SOURCES:.c=.i)
index: $(CSCOPE_REF)
update: $(DRAKON_FILES)
	$(if $(strip $(shell lsof $^)),$(error Prior to proceed with '$@', close file(s): $^),)
	$(SQLITE3) -batch $< '.dump' >$(DRAKON_SQL)
shared: $(LIBNAME.so)
static: $(LIBNAME.a)

$(LIBNAME.a): $(OBJECTS)
	$(AR) rcs $@ $^

$(LIBNAME.so): $(OBJECTS)
	$(CC) -shared -fPIC $(LDFLAGS) -o $@ $^ $(LDLIBS)

include $(if $(filter $(NOT_DEP),$(MAKECMDGOALS)),,$(DEPENDS))

$(CSCOPE_REF): $(SOURCES) $(wildcard ptmalloc3/*.[ch]) $(HEADERS)
	$(CSCOPE) -R -f $@ -b
clean: F += $(wildcard $(EXECUTABLE) $(EXECUTABLE).fat $(CSCOPE_REF) *.o *.s *.i *.csv trace.log *.cflow *.expand $(TIME_RESULT) $(LIBNAME.a) $(LIBNAME.so) $(LIBNAME.so.debug))
clean:
	-$(if $(strip $F),$(RM) -- $F,)
wipe: F += $(wildcard $(DRAKON_FILES) $(DRAKON_CFILES) $(DRAKON_HFILES) .syntastic_c_config *.d *.stackdump)
wipe: clean

.PHONY: install
install: $(INSTALLED_FILES)

$(PREFIX)/lib/$(LIBNAME.a): $(LIBNAME.a)
	install -D $< $@
$(PREFIX)/lib/$(LIBNAME.so): $(LIBNAME.so)
	install -D $< $@
$(PREFIX)/include/$(NAME)/%.h: include/%.h
	install -D $< $@
$(PREFIX)/include/$(NAME)/%.h: %.h
	install -D $< $@
$(PREFIX)/include/$(NAME)/%.h: include/data_types/%.h
	install -D $< $@
$(PREFIX)/include/$(NAME)/%.h: include/interfaces/%.h
	install -D $< $@
$(PREFIX)/include/$(NAME)/%.h: include/configuration/%.h
	install -D $< $@
$(PREFIX)/include/$(NAME)/%.h: include/global_data_elements/%.h
	install -D $< $@
$(PREFIX)/include/$(NAME)/%.h: include/local_data_elements/%.h
	install -D $< $@

.PHONY: uninstall
uninstall:
	rm -- $(INSTALLED_FILES)

.PRECIOUS: %.c %.h
%.c %.h: %.drn
	$(DRAKON_GEN) -in $<
	$(CLANG_FORMAT) -i $*.c $*.h
%.d: %.c
	$(CC) -MM -MF $@ $(CPPFLAGS) $(CFLAGS) -o $@ $<
%.s: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -S -o $@ $<
%.i: %.c
	$(CC) $(CPPFLAGS) -E -o $@ $<
%.drn: %.sql
	$(SQLITE3) -batch $@ <$<
	chmod a-x $@

.syntastic_c_config: Makefile
	echo $(CPPFLAGS) $(CFLAGS) | tr ' ' '\n' > $@

.PHONY: csv
csv: $(DRAKON_FILES:.drn=.csv)
%.csv: %.drn SelectItemMsg.sql
	$(SQLITE3) -batch -csv $< <SelectItemMsg.sql >$@

.PHONY: trace
trace: trace.log
	$(ADDR2LINE) -spf -e $(EXECUTABLE) <$< | paste $< -
trace.log: $(EXECUTABLE) adjust_addr.awk
	./$<
	awk --non-decimal-data -f $(word 2,$^) $@ | sponge $@

.PHONY: cflow
cflow: $(NAME).cflow
$(NAME).cflow:
	$(CFLOW) --no-ansi --omit-symbol-names $(SOURCES) > $@

.PHONY: cg
cg: cg.png
cg.png:
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -fdump-rtl-expand $(SOURCES) $(LDLIBS)
	egypt *.expand | sed '8irankdir="LR"' | dot -Tpng > callgraph.png

# TODO: Move to `makes` library
.PHONY: print-%
print-%:
	@:$(info $($*))

.PHONY: graph
graph: $(GRAPH_IMAGES)
%.png: %.dot
	dot -T png  $< >$@
%.dot: export LC_ALL=C
%.dot: $(lastword $(MAKEFILE_LIST))
	make wipe
	make -Bnd $* | make2graph -b | sed '2irankdir="RL"' >$@
