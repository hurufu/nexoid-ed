EXECUTABLE          := nexoid-ut

CHECK_SOURCES       := $(wildcard *.t)
SOURCES             := $(CHECK_SOURCES:.t=.c)

LDLIBS              := -lnexoid
LDLIBS              += $(shell pkg-config --libs check)

CFLAGS              := -ggdb3 -O0
CFLAGS              += $(shell pkg-config --cflags check)

LDFLAGS             := -Wl,--unresolved-symbols=ignore-in-shared-libs

.PHONY: all
all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(ASMFLAGS) $(LDFLAGS) $^ $(LDLIBS)

.PHONY: run
run: $(EXECUTABLE)
	./$<

.PHONY: clean
clean: F := $(wildcard $(EXECUTABLE) $(SOURCES) tags)
clean:
	$(if $(strip $F),$(RM) -- $F,)

.PHONY: ddd
ddd: $(EXECUTABLE)
	ddd --args $< $(SCENARIO)

.PHONY: index
index: tags
tags: $(SOURCES)
	ctags -R . /usr/local/include

%.c: %.t
	checkmk $< >$@

%.i: %.c
	$(CC) -E $(CPPFLAGS) -o $@ $<
