EXECUTABLE          := nexoid-ut

CHECK_TEST_FILES    := $(wildcard *-$(shell uname --machine).t)
GENERATED_SOURCES   := $(CHECK_TEST_FILES:.t=.c)
SOURCES             := $(GENERATED_SOURCES) common.c

LDLIBS              := -lnexoid
LDLIBS              += $(shell pkg-config --libs check)

CFLAGS              := -ggdb3 -O0 --pipe
CFLAGS              += $(shell pkg-config --cflags check)

LDFLAGS             := -Wl,--unresolved-symbols=ignore-in-shared-libs

CTAGS               := ctags
CHECKMK             := checkmk

.PHONY: all
all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(ASMFLAGS) $(LDFLAGS) $^ $(LDLIBS)

.PHONY: run
run: $(EXECUTABLE)
	./$<

.PHONY: clean
clean: F := $(wildcard $(EXECUTABLE) $(GENERATED_SOURCES) tags)
clean:
	$(if $(strip $F),$(RM) -- $F,)

.PHONY: index
index: tags
tags: $(SOURCES)
	$(CTAGS) -f $@ -R . /usr/local/include

%.c: %.t
	$(CHECKMK) $< >$@

%.i: %.c
	$(CC) -E $(CPPFLAGS) -o $@ $<
