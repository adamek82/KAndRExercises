BUILD ?= debug

ifeq ($(OS),Windows_NT)
export PATH := C:/msys64/ucrt64/bin;C:/msys64/usr/bin;$(PATH)
CC := gcc
CMP := C:/msys64/usr/bin/cmp.exe
EXEEXT := .exe
else
CC := gcc-14
CMP := cmp
EXEEXT :=
endif

MKDIR_P := mkdir -p
RM_RF := rm -rf

CFLAGS_COMMON := -std=c23 -Wall -Wextra -pedantic

ifeq ($(BUILD),release)
CFLAGS := $(CFLAGS_COMMON) -O2 -DNDEBUG
OUTDIR := build/release
else
CFLAGS := $(CFLAGS_COMMON) -g -O0
OUTDIR := build/debug
endif

EXERCISES := $(patsubst %/main.c,%,$(wildcard chapter*/exercise*/main.c chapter*/exercise*/*/main.c))
TARGETS := $(addsuffix $(EXEEXT),$(addprefix $(OUTDIR)/,$(EXERCISES)))

TESTS :=
PHONY_TARGETS :=

all: debug

include $(wildcard chapter*/chapter.mk)

.PHONY: all build debug release clean list run test test-all $(PHONY_TARGETS)

build: $(TARGETS)

debug:
	$(MAKE) BUILD=debug build

release:
	$(MAKE) BUILD=release build

$(OUTDIR)/%$(EXEEXT): %/main.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

run: debug
	@if [ -z "$(EX)" ]; then \
		echo "Usage: make run EX=chapter01/exercise01"; \
		exit 1; \
	fi
	./build/debug/$(EX)$(EXEEXT)

test:
	@if [ -z "$(EX)" ]; then \
		echo "Usage: make test EX=chapter01/exercise09"; \
		exit 1; \
	fi
	@target=$$(echo "$(EX)" | sed \
		-e 's#^chapter\([0-9][0-9]\)/exercise\([0-9][0-9]\)/\([^/][^/]*\)$$#test-ch\1-ex\2-\3#' \
		-e 's#^chapter\([0-9][0-9]\)/exercise\([0-9][0-9]\)$$#test-ch\1-ex\2#'); \
	$(MAKE) $$target

test-all: $(TESTS)

list:
	@printf '%s\n' $(EXERCISES)

clean:
	$(RM_RF) build
