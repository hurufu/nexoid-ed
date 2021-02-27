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
OL           := 0
DL           := gdb3
STD          := gnu11
WARNINGS     := all extra
WARNINGS     += $(if $(USE_GCC_ANALYZER),analyzer-too-complex,)
PREFIX       := /usr/local
GCC_FEATURES := $(if $(filter trace,$(MAKECMDGOALS)),instrument-functions,)
GCC_FEATURES += $(if $(USE_COLOR),diagnostics-color=always,)
GCC_FEATURES += $(if $(USE_GCC_ANALYZER),analyzer $(if $(USE_GCC_ANALYZER_TAINT),analyzer-checker=taint,))
GCC_FEATURES += $(if $(USE_LTO),lto,)
LD_FEATURES  := $(if $(USE_LTO),lto use-linker-plugin)

# Git inspector config ########################################################
GITINSPECTOR_FORMAT ?= html
GITINSPECTOR_FILE   := gitinspector.$(GITINSPECTOR_FORMAT)

# Project config ##############################################################
NAME         := nexoid
INCLUDE_DIRS := . $(shell find include -type d)
# TODO: Develop proper pkg-config for dependencies
LIBRARIES    := ptmalloc3 pthread

# Toolchain settings ##########################################################
CPPFLAGS     += $(addprefix -I,$(INCLUDE_DIRS))
_CFLAGS      := -O$(OL) $(addprefix -W,$(WARNINGS)) -g$(DL)
_CFLAGS      += $(addprefix -f,$(GCC_FEATURES))
_CFLAGS      += -march=native -mtune=native
CFLAGS       ?= $(_CFLAGS)
CFLAGS       += -std=$(STD)
LDLIBS       := $(addprefix -l,$(LIBRARIES))
LDFLAGS      ?= $(addprefix -f,$(LD_FEATURES))
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
PIC_OBJECTS  := $(SOURCES:.c=.pic.o)

GRAPH_TARGETS := all install uninstall shared
GRAPH_IMAGES  := $(addsuffix .png,$(GRAPH_TARGETS))

HEADERS_INSTALL_DIR := $(PREFIX)/include/$(NAME)
INSTALLED_FILES    := $(addprefix $(PREFIX)/lib/,$(notdir $(LIBNAME).a $(LIBNAME).so))
INSTALLED_FILES    += $(addprefix $(HEADERS_INSTALL_DIR)/,$(notdir $(HEADERS)))

CSCOPE_REF   := cscope.out

TIME_FORMAT    ?= pdb
TIME_RESULT    := time.$(TIME_FORMAT)
TIME_ARGS_yaml := --format=' - { user: %U, system: %S, real: "%E", cpu: "%P", command: "%C" }' --append --output $(TIME_RESULT)
TIME_ARGS_pdb  := --format='pd(user(%U), system(%S), real(%e), command("%C")).' --append --output $(TIME_RESULT)

CPP_ARGFILE    := .cpp.args
C_ARGFILE      := .$(basename $(CC)).args
LD_ARGFILE     := .ld.args
LIB_ARGFILE    := .lib.args

# Commands ####################################################################
TIME         := $(if $(PROFILE_BUILD),$(call assert_cmd,time) $(TIME_ARGS_$(TIME_FORMAT)),)
CSCOPE        = $(TIME) $(call assert_cmd,cscope) $(if $(VERBOSE),-v,)
CLANG_FORMAT := $(if $(USE_CLANG_FORMAT),$(call assert_cmd,clang-format),@true)
RM           := rm $(if $(VERBOSE),-v,)
AR           := gcc-ar
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
DRAKON_GEN   := $(TIME) $(if $(shell which drakon-gen),drakon-gen,'$(DRAKON_PATH)/drakon_gen.tcl')
GITINSPECTOR  = $(TIME) $(call assert_cmd,gitinspector)

# Build time profiling
TIME_PROC.pdb   = $(PROLOG) --consult-file time.pdb --consult-file profiling_build.pdb <profiling_build.pq

# Targets that do not need *.d dependencies for source files
NOT_DEP      := clean asm pp wipe update

.PRECIOUS: %.drn

ifdef PROFILE_BUILD
.PHONY: profile_build
profile_build: all profiling_build.pdb profiling_build.pq
	$(TIME_PROC.$(TIME_FORMAT))
endif

.PHONY: all clean asm pp index update static shared
most_frequent: all install
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

$(LIBNAME.so): $(LD_ARGFILE) $(LIB_ARGFILE) $(PIC_OBJECTS)
	$(CC) -shared -fPIC @$(word 1,$^) -o $@ $(wordlist 3,$(words $^),$^) @$(word 2,$^)

include $(if $(filter $(NOT_DEP),$(MAKECMDGOALS)),,$(DEPENDS))

$(CSCOPE_REF): $(SOURCES) $(wildcard ptmalloc3/*.[ch]) $(HEADERS)
	$(CSCOPE) -R -f $@ -b
clean: F += $(wildcard $(EXECUTABLE) $(EXECUTABLE).fat $(CSCOPE_REF) *.o *.s *.i *.csv trace.log *.cflow *.expand $(TIME_RESULT) $(LIBNAME.a) $(LIBNAME.so) $(LIBNAME.so.debug))
clean:
	-$(if $(strip $F),$(RM) -- $F,)
wipe: F += $(wildcard $(DRAKON_FILES) $(DRAKON_CFILES) $(DRAKON_HFILES) .syntastic_c_config *.d *.stackdump)
wipe: F += $(wildcard $(C_ARGFILE) $(CPP_ARGFILE) $(LD_ARGFILE) $(LIB_ARGFILE))
wipe: clean

.PHONY: install
install: $(INSTALLED_FILES)

$(PREFIX)/lib/$(LIBNAME.a): $(LIBNAME.a)
	install -D -m444 $< $@
$(PREFIX)/lib/$(LIBNAME.so): $(LIBNAME.so)
	install -D -m555 $< $@
$(PREFIX)/include/$(NAME)/%.h: include/%.h
	install -D -m444 $< $@
$(PREFIX)/include/$(NAME)/%.h: %.h
	install -D -m444 $< $@

.PHONY: uninstall
uninstall: F := $(sort $(wildcard $(INSTALLED_FILES)))
uninstall: D := $(sort $(wildcard $(HEADERS_INSTALL_DIR)))
uninstall:
	$(if $(strip $F),$(RM) -f -- $F,)
	$(if $(strip $D),rmdir -- $D,)

.PRECIOUS: %.c %.h
%.c %.h: %.drn
	$(DRAKON_GEN) -in $<
	$(CLANG_FORMAT) -i $*.c $*.h
%.d: %.c $(CPP_ARGFILE)
	$(CC) -MM -MF $@ -MT $*.o -MT $*.pic.o @$(word 2,$^) -o $@ $<
%.s: %.c $(C_ARGFILE)
	$(CC) -S @$(word 2,$^) -fno-lto -fverbose-asm -o $@ $<
%.pic.s: %.c $(C_ARGFILE)
	$(CC) -S @$(word 2,$^) -fno-lto -fPIC -o $@ $<
%.i: %.c $(CPP_ARGFILE)
	$(CC) @$(word 2,$^) -E -o $@ $<
%.drn: DropTables.sql %.sql
	$(if $(strip $(shell lsof $^)),$(error Prior to proceed with '$@', close file(s): $^),)
	cat $^ | $(SQLITE3) -batch $@
	chmod a-x $@
%.pic.o: %.c $(C_ARGFILE)
	$(CC) -c @$(word 2,$^) -fPIC -o $@ $(word 1,$^)
%.o: %.c $(C_ARGFILE)
	$(CC) -c @$(word 2,$^) -o $@ $(word 1,$^)

.syntastic_c_config: $(C_ARGFILE)
	echo @$< -fdiagnostics-color=never | tr ' ' '\n' > $@
$(C_ARGFILE): $(CPP_ARGFILE) $(MAKEFILE_LIST)
	echo $(CFLAGS) @$< | tr ' ' '\n' > $@
$(CPP_ARGFILE):
	echo $(CPPFLAGS) | tr ' ' '\n' > $@
$(LD_ARGFILE): $(MAKEFILE_LIST)
	echo $(LDFLAGS) | tr ' ' '\n' > $@
$(LIB_ARGFILE): $(MAKEFILE_LIST)
	echo $(LDLIBS) | tr ' ' '\n' > $@

.PHONY: csv
csv: $(DRAKON_FILES:.drn=.csv)
%.csv: %.drn SelectItemMsg.sql
	$(SQLITE3) -batch -csv $< <SelectItemMsg.sql >$@

.PHONY: cflow
cflow: $(NAME).cflow
$(NAME).cflow:
	$(CFLOW) --no-ansi --omit-symbol-names $(SOURCES) > $@

.PHONY: cg
cg: cg.png
cg.png: $(CPP_ARGFILE)
	$(CC) -c @$< -fdump-rtl-expand $(SOURCES)
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

.PHONY: inspect
inspect: $(GITINSPECTOR_FILE)
clean: F += $(wildcard $(GITINSPECTOR_FILE))
$(GITINSPECTOR_FILE):
	$(GITINSPECTOR) -HmTr -F $(GITINSPECTOR_FORMAT) >$@
