# Takes any number of command line arguments ($2) and created text file ($1)
# with all of them on a separate line each
make_argfile = $(file >$1,$(subst $S,$L,$2))

LIBCTL_DIR := /usr/share/libctl
CTL_DEFS   := '-DCTL_SCM="$(LIBCTL_DIR)/base/ctl.scm"'
CTL_DEFS   += '-DINCLUDE_SCM="$(LIBCTL_DIR)/base/include.scm"'
CTL_DEFS   += '-DSPEC_SCM="example.scm"'
CTL_DEFS   += '-DVERSION_STRING="example 0.0.0"'
CPPFLAGS   := -I. $(CTL_DEFS)
CFLAGS     := $(shell pkg-config --cflags guile-2.2)
LDLIBS     := $(shell pkg-config --libs guile-2.2) -lctl -lm
VPATH      := . $(LIBCTL_DIR)/base $(LIBCTL_DIR)/utils

include example.d ctl-io.d main.d
.PHONY: run clean index
run: example run.scm
	./$< $(if $(VERBOSE),--verbose) $(word 2,$^)
clean: F := $(wildcard ctl-io.c ctl-io.h example .cflags .ldlibs *.o *.d)
clean:
	$(if $(strip $F),$(RM) -- $F)
index:
	ctags -R .
example: example.o ctl-io.o main.o .ldlibs
	$(CC) -o $@ $(filter %.o,$^) @.ldlibs
%.o: %.c .cflags
	$(CC) @.cflags -c -o $@ $<
%.d: %.c .cflags
	$(CC) @$(word 2,$^) -MG -MM -MF $@ $<
ctl-io.c: example.scm
	gen-ctl-io --code -o $@ $<
	clang-format -i $@
ctl-io.h: example.scm
	gen-ctl-io --header -o $@ $<
	clang-format -i $@
.cflags: Makefile
	$(call make_argfile,$@,$(CPPFLAGS) $(CFLAGS))
.ldlibs: Makefile
	$(call make_argfile,$@,$(LDLIBS))
