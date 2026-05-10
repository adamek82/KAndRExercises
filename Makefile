BUILD ?= debug

ifeq ($(OS),Windows_NT)
export PATH := C:/msys64/ucrt64/bin;C:/msys64/usr/bin;$(PATH)
CC := gcc
EXEEXT := .exe
else
CC ?= gcc
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

EXERCISES := $(patsubst %/main.c,%,$(wildcard chapter*/exercise*/main.c))
TARGETS := $(addsuffix $(EXEEXT),$(addprefix $(OUTDIR)/,$(EXERCISES)))
TESTS := \
	test-ch01-ex06 \
	test-ch01-ex07 \
	test-ch01-ex08 \
	test-ch01-ex09

.PHONY: all build debug release clean list run test test-all \
        test-ch01-ex06 test-ch01-ex07 test-ch01-ex08 test-ch01-ex09 \
        experiment-ch01-ex02

all: debug

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
	@target=$$(echo "$(EX)" | sed 's#chapter\([0-9][0-9]\)/exercise\([0-9][0-9]\)#test-ch\1-ex\2#'); \
	$(MAKE) $$target

test-all: $(TESTS)

build/debug/chapter01/exercise02-experiment$(EXEEXT): chapter01/exercise02/main.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS_COMMON) -g -O0 -DEXPERIMENT_UNKNOWN_ESCAPE $< -o $@

experiment-ch01-ex02: build/debug/chapter01/exercise02-experiment$(EXEEXT)
	./build/debug/chapter01/exercise02-experiment$(EXEEXT)

test-ch01-ex06: debug
	@printf '%s' 'x' | ./build/debug/chapter01/exercise06$(EXEEXT) | grep -qx '1'
	@printf '%s' '' | ./build/debug/chapter01/exercise06$(EXEEXT) | grep -qx '0'
	@echo "chapter01/exercise06 tests passed"

test-ch01-ex07: debug
	@./build/debug/chapter01/exercise07$(EXEEXT) | grep -Eq '^-?[0-9]+$$'
	@test "$$(./build/debug/chapter01/exercise07$(EXEEXT))" -lt 0
	@echo "chapter01/exercise07 tests passed"

test-ch01-ex08: debug
	@printf '%s' '' | ./build/debug/chapter01/exercise08$(EXEEXT) | grep -qx '0 0 0'
	@printf ' \t\nx\n' | ./build/debug/chapter01/exercise08$(EXEEXT) | grep -qx '1 1 2'
	@printf 'a b\tc\n\n  d' | ./build/debug/chapter01/exercise08$(EXEEXT) | grep -qx '3 1 2'
	@echo "chapter01/exercise08 tests passed"

test-ch01-ex09: debug
	@test "$$(printf '%s' '' | ./build/debug/chapter01/exercise09$(EXEEXT))" = ""
	@test "$$(printf '%s' 'abc' | ./build/debug/chapter01/exercise09$(EXEEXT))" = "abc"
	@test "$$(printf '%s' 'a  b   c' | ./build/debug/chapter01/exercise09$(EXEEXT))" = "a b c"
	@test "$$(printf '%s' '   a    b   ' | ./build/debug/chapter01/exercise09$(EXEEXT))" = " a b "
	@echo "chapter01/exercise09 tests passed"

list:
	@printf '%s\n' $(EXERCISES)

clean:
	$(RM_RF) build
