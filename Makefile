# Macros ######################################################################
# FIXME: Remove macros from here and user system-wide `makes` installation

# Define MAKE_DEBUG to any non-empty value in order to debug all variable
# definedness tests
#MAKE_DEBUG := y

# Special characters
N :=
S := $N $N
C := ,
define L


endef

MAKEFILE = $(firstword $(MAKEFILE_LIST))

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

# Takes any number of command line arguments ($2) and created text file ($1)
# with all of them on a separate line each
make_argfile = $(file >$1,$(subst $S,$L,$2))

# Simply expanded variable (:=) on Cygwin is actually 30x faster then
# recursively expanded.
# TODO: Maybe there is a way to speed-up targets that don't use $(UNAME_OS)
# even more, by implementing some sort of memoization.
UNAME_OS  := $(shell uname -o)
HOST_OS_CYGWIN   := $(if $(findstring Cygwin,$(UNAME_OS)),y)
HOST_OS_LINUX    := $(if $(findstring Linux,$(UNAME_OS)),y)
TARGET_OS_CYGWIN :=
TARGET_OS_LINUX  := y

# There is a program similar to lsof for windows - handle, but it's too slow even for a single file
# https://docs.microsoft.com/en-us/sysinternals/downloads/handle
LSOF       = $(if $(HOST_OS_LINUX),$(call assert_cmd,lsof))
lsof_guard = $(if $(LSOF),$(if $(strip $(shell $(LSOF) $1)),$(error Prior to proceed with '$@', close file(s): $1)))

# Automatically set prerequisites search path to the main Makefile location
VPATH     += $(dir $(firstword $(MAKEFILE_LIST)))

# User config #################################################################
OL           := 0
DL           := gdb3
STD          := gnu11
WARNINGS     := all extra
WARNINGS     += $(if $(USE_GCC_ANALYZER),analyzer-too-complex,)
DESTDIR      :=
PREFIX       := /usr/local
INSTALL_DIR  := $(shell echo $(DESTDIR)/$(PREFIX) | sed -E 's:/+:/:' )
GCC_FEATURES := $(if $(filter trace,$(MAKECMDGOALS)),instrument-functions,)
GCC_FEATURES += $(if $(USE_COLOR),diagnostics-color=always,)
GCC_FEATURES += $(if $(USE_GCC_ANALYZER),analyzer $(if $(USE_GCC_ANALYZER_TAINT),analyzer-checker=taint,))
GCC_FEATURES += no-plt
GCC_FEATURES += $(if $(USE_LTO),lto,)
LD_FEATURES  := $(if $(USE_LTO),lto use-linker-plugin)

# Git inspector config ########################################################
GITINSPECTOR_FORMAT ?= html
GITINSPECTOR_FILE   := gitinspector.$(GITINSPECTOR_FORMAT)

# Project config ##############################################################
NAME         := nexoid
INCLUDE_DIRS := . include
SRCDIR       := src
# TODO: Develop proper pkg-config for dependencies
LIBRARIES    := pthread

# Unit tests settings #########################################################
UT_EXECUTABLE        := ut/$(NAME)
UT_CHECK_TEST_FILES  := $(sort $(wildcard ut/*.t))
UT_GENERATED_SOURCES := ut/ut.c
UT_SOURCES           := $(UT_GENERATED_SOURCES) ut/common.c
UT_OBJECTS           := $(UT_SOURCES:.c=.o)
UT_LDLIBS            := $(shell pkg-config --libs check)
UT_LDFLAGS           := -Wl,--unresolved-symbols=ignore-in-object-files -pthread

# Toolchain settings ##########################################################
CPPFLAGS     += -pthread
_CFLAGS      := -O$(OL) $(addprefix -W,$(WARNINGS)) -g$(DL)
_CFLAGS      += $(addprefix -f,$(GCC_FEATURES))
_CFLAGS      += -march=native -mtune=native
CFLAGS       ?= $(_CFLAGS)
CFLAGS       += -std=$(STD)
LDLIBS       := $(addprefix -l,$(LIBRARIES))
LDFLAGS      ?= $(addprefix -f,$(LD_FEATURES))
LDFLAGS      += -pthread
# TODO: Clearify what those flags are doing
IMPLIB        = $(if $(TARGET_OS_CYGWIN),$(LIBNAME)_dll.a)
LDFLAGS      += $(if $(TARGET_OS_CYGWIN),$(addprefix -Wl$C,--out-implib$C$(IMPLIB) --export-all-symbols --enable-auto-import))
VERSION       = $(shell git describe --dirty --broken)

LIBPREFIX        := $(if $(TARGET_OS_CYGWIN),cyg,lib)
SHARED_LIB_EXT   := $(if $(TARGET_OS_LINUX),so,$(if $(TARGET_OS_CYGWIN),dll,$(error Can't determine appropriate shared library extension for you OS: "$(UNAME_OS)")))
LIBNAME          := $(LIBPREFIX)$(NAME)
LIBNAME.a        := $(LIBNAME).a
LIBNAME.so       := $(LIBNAME).$(SHARED_LIB_EXT)
LIBNAME.so.debug := $(LIBNAME.so).debug

DRAKON_SQL   := $(SRCDIR)/NexoFast.sql
DRAKON_FILES := $(DRAKON_SQL:.sql=.drn)
DRAKON_PATH  ?= /cygdrive/c/opt/DrakonEditor/1.31
DRAKON_CFILES:= $(DRAKON_FILES:.drn=.c)
DRAKON_HFILES:= $(DRAKON_FILES:.drn=.h)

SOURCES      := $(sort $(DRAKON_CFILES) $(addprefix $(SRCDIR)/,common.c tag_retrival.c $(if $(TARGET_OS_CYGWIN),stubs.c)))
HEADERS      := $(DRAKON_HFILES)
HEADERS      += $(addprefix $(SRCDIR)/,bool.h cxx_macros.h local.h nexo.h tag_retrival.h)
HEADERS      += ut/common.h
HEADERS      += $(addprefix include/,dmapi.h eapi.h gtd.h hapi.h macro.h papi.h pklr.h scapi.h tmapi.h types.h utils.h)
OBJECTS      := $(SOURCES:.c=.o)
DEPENDS      := $(SOURCES:.c=.d)
PIC_OBJECTS  := $(SOURCES:.c=.pic.o)

GRAPH_TARGETS := all install uninstall shared most_frequent
GRAPH_IMAGES  := $(addsuffix .png,$(GRAPH_TARGETS))

HEADERS_INSTALL_DIR := $(INSTALL_DIR)/include/$(NAME)
INSTALLED_FILES     := $(addprefix $(INSTALL_DIR)/lib/,$(notdir $(LIBNAME.a) $(LIBNAME.so)))
INSTALLED_FILES     += $(addprefix $(HEADERS_INSTALL_DIR)/,$(notdir $(filter-out %/common.h,$(HEADERS))))

CSCOPE_REF   := cscope.out

TIME_FORMAT    ?= pdb
TIME_RESULT    := time.$(TIME_FORMAT)
TIME_ARGS_json := --format='{ "user": %U, "system": %S, "real": %e, "cpu": "%P", "command": "%C" }' --append --output $(TIME_RESULT)
TIME_ARGS_yaml := --format=' - { user: %U, system: %S, real: %e, cpu: "%P", command: "%C" }' --append --output $(TIME_RESULT)
TIME_ARGS_pdb  := --format='pd(user(%U), system(%S), real(%e), command("%C")).' --append --output $(TIME_RESULT)

CPP_ARGFILE    := .cpp.args
C_ARGFILE      := .$(basename $(CC)).args
LD_ARGFILE     := .ld.args
LIB_ARGFILE    := .lib.args
UT_LD_ARGFILE  := .ut-ld.args
UT_LIB_ARGFILE := .ut-lib.args

# Commands ####################################################################
TIME         := $(if $(PROFILE_BUILD),$(call assert_cmd,time) $(TIME_ARGS_$(TIME_FORMAT)),)
CSCOPE        = $(TIME) $(call assert_cmd,cscope) $(if $(VERBOSE),-v,)
CLANG_FORMAT := $(if $(USE_CLANG_FORMAT),$(call assert_cmd,clang-format),@true)
RM           := rm $(if $(VERBOSE),-v,)
AR           := $(TIME) gcc-ar
OBJCOPY      := $(TIME) objcopy $(if $(VERBOSE),-v,)
ADDR2LINE    := $(TIME) addr2line
SQLITE3      := $(TIME) $(call assert_cmd,sqlite3)
DDD           = $(TIME) $(call assert_cmd,ddd)
ifdef USE_CCACHE
CCACHE       := $(call assert_cmd,ccache)
endif
# Tested with gprolog, swipl, and scryer-prolog
PROLOG        = $(TIME) $(call assert_cmd,gprolog)
YQ            = $(call assert_cmd,yq)
JQ            = $(call assert_cmd,jq)
CC           := $(TIME) $(if $(USE_CCACHE),$(CCACHE) gcc,gcc)
CFLOW         = $(TIME) $(call assert_cmd,cflow)
DRAKON_GEN    = $(TIME) $(if $(shell which drakon-gen),drakon-gen,'$(DRAKON_PATH)/drakon_gen.tcl')
GITINSPECTOR  = $(TIME) $(call assert_cmd,gitinspector)
CHECKMK       = $(TIME) $(call assert_cmd,checkmk)

# Targets that do not need *.d dependencies for source files
NOT_DEP      := clean asm pp wipe update

ifdef PROFILE_BUILD
.PHONY: profile_build profile_build_pdb profile_build_yaml
profile_build: profile_build_$(TIME_FORMAT)
profile_build_pdb: profiling_build.pdb all
	echo "['$(TIME_RESULT)']. ['$<']. prof(User, System, Real, CPU)." | $(PROLOG)
profile_build_yaml: profiling_build.jq all
	$(YQ) -y '$(strip $(file <$<))' $(TIME_RESULT)
profile_build_json: profiling_build.jq all
	$(JQ) -s '$(strip $(file <$<))' $(TIME_RESULT)
endif

.PHONY: all clean asm pp index update static shared test
most_frequent: all install test
all: shared static index .syntastic_c_config
asm: $(SOURCES:.c=.s)
pp: $(SOURCES:.c=.i)
index: $(CSCOPE_REF)
update: $(DRAKON_FILES)
	$(call lsof_guard,$^)
	$(SQLITE3) -batch $< '.dump' >$(DRAKON_SQL)
shared: $(LIBNAME.so)
static: $(LIBNAME.a)
test: $(UT_EXECUTABLE)
	./$<

$(UT_EXECUTABLE): $(UT_LD_ARGFILE) $(UT_LIB_ARGFILE) $(UT_OBJECTS) $(LIBNAME.a)
	$(CC) -o $@ @$(word 1,$^) $(wordlist 3,$(words $^),$^) @$(word 2,$^)

$(LIBNAME.a): $(OBJECTS)
	$(AR) rcs $@ $^

$(LIBNAME.so): $(LD_ARGFILE) $(LIB_ARGFILE) $(PIC_OBJECTS)
	$(CC) -shared -fPIC @$(word 1,$^) -o $@ $(wordlist 3,$(words $^),$^) @$(word 2,$^)

include $(if $(filter $(NOT_DEP),$(MAKECMDGOALS)),,$(DEPENDS))

$(CSCOPE_REF): $(SOURCES) $(HEADERS)
	$(CSCOPE) -R -f $@ -b
clean: F += $(wildcard $(EXECUTABLE) $(EXECUTABLE).fat $(CSCOPE_REF) $(OBJECTS) $(PIC_OBJECTS) *.s *.i *.csv trace.log *.cflow *.expand $(TIME_RESULT) $(LIBNAME.a) $(LIBNAME.so) $(LIBNAME.so.debug))
clean: F += $(wildcard $(UT_EXECUTABLE) $(UT_GENERATED_SOURCES) $(UT_OBJECTS))
clean: F += $(wildcard $(IMPLIB))
clean:
	-$(if $(strip $F),$(RM) -- $F,)
wipe: F += $(wildcard $(DRAKON_FILES) $(DRAKON_CFILES) $(DRAKON_HFILES) .syntastic_c_config $(DEPENDS) *.stackdump)
wipe: F += $(wildcard $(C_ARGFILE) $(CPP_ARGFILE) $(LD_ARGFILE) $(LIB_ARGFILE))
wipe: F += $(wildcard $(UT_LIB_ARGFILE) $(UT_LD_ARGFILE))
wipe: clean

.PHONY: install
install: $(INSTALLED_FILES)

$(INSTALL_DIR)/lib/$(LIBNAME.a): $(LIBNAME.a)
	install -D -m444 $< $@
$(INSTALL_DIR)/lib/$(LIBNAME.so): $(LIBNAME.so)
	install -D -m555 $< $@
$(HEADERS_INSTALL_DIR)/%.h: include/%.h
	install -D -m444 $< $@
$(HEADERS_INSTALL_DIR)/%.h: %.h
	install -D -m444 $< $@
$(HEADERS_INSTALL_DIR)/%.h: $(SRCDIR)/%.h
	install -D -m444 $< $@

.PHONY: uninstall
uninstall: F := $(sort $(wildcard $(INSTALLED_FILES)))
uninstall: D := $(sort $(wildcard $(HEADERS_INSTALL_DIR)))
uninstall:
	$(if $(strip $F),$(RM) -f -- $F,)
	$(if $(strip $D),rmdir -- $D,)

.PRECIOUS: %.c %.h %.drn
%.c %.h: %.drn
	$(DRAKON_GEN) -in $<
	$(CLANG_FORMAT) -i $*.c $*.h
%.d: %.c $(CPP_ARGFILE)
	mkdir -p $(*D)
	$(CC) -MM -MF $@ -MT $*.o -MT $*.pic.o @$(word 2,$^) -o $@ $<
%.s: %.c $(C_ARGFILE)
	$(CC) -S @$(word 2,$^) -fno-lto -fverbose-asm -o $@ $<
%.pic.s: %.c $(C_ARGFILE)
	$(CC) -S @$(word 2,$^) -fno-lto -fPIC -o $@ $<
%.i: %.c $(CPP_ARGFILE)
	$(CC) @$(word 2,$^) -E -o $@ $<
%.drn: DropTables.sql %.sql
	$(call lsof_guard,$^)
	mkdir -p $(*D)
	cat $^ | $(SQLITE3) -batch $@
	chmod a-x $@
%.pic.o: %.c $(C_ARGFILE)
	$(CC) -c @$(word 2,$^) -fPIC -o $@ $(word 1,$^)
%.o: %.c $(C_ARGFILE)
	$(CC) -c @$(word 2,$^) -o $@ $(word 1,$^)
ut/ut.c: $(UT_CHECK_TEST_FILES)
	# FIXME: Create all directories as '|' dependencies
	mkdir -p -- $(*D)
	$(CHECKMK) $^ >$@

.syntastic_c_config: $(C_ARGFILE)
	$(call make_argfile,$@,@$< -fdiagnostics-color=never)
$(C_ARGFILE): $(CPP_ARGFILE) $(MAKEFILE)
	$(call make_argfile,$@,@$< $(CFLAGS))
$(CPP_ARGFILE): $(HEADERS)
	$(call make_argfile,$@,$(CPPFLAGS) $(addprefix -I,$(sort $(^D))))
$(LD_ARGFILE): $(MAKEFILE)
	$(call make_argfile,$@,$(LDFLAGS))
$(LIB_ARGFILE): $(MAKEFILE)
	$(call make_argfile,$@,$(LDLIBS))
$(UT_LD_ARGFILE): $(MAKEFILE)
	$(call make_argfile,$@,$(UT_LDFLAGS))
$(UT_LIB_ARGFILE): $(MAKEFILE)
	$(call make_argfile,$@,$(UT_LDLIBS))

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
cg.png: $(CPP_ARGFILE) $(SOURCES)
	$(CC) -c -fdump-rtl-expand @$^
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
