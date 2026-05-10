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

.PHONY: all build debug release clean list \
        run-ch01-ex01 run-ch01-ex02 run-ch01-ex03 run-ch01-ex04 run-ch01-ex05 run-ch01-ex06 run-ch01-ex07 \
        test-ch01-ex06 \
		test-ch01-ex07 \
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

run-ch01-ex01: debug
	./build/debug/chapter01/exercise01$(EXEEXT)

run-ch01-ex02: debug
	./build/debug/chapter01/exercise02$(EXEEXT)

run-ch01-ex03: debug
	./build/debug/chapter01/exercise03$(EXEEXT)

run-ch01-ex04: debug
	./build/debug/chapter01/exercise04$(EXEEXT)

run-ch01-ex05: debug
	./build/debug/chapter01/exercise05$(EXEEXT)

run-ch01-ex06: debug
	./build/debug/chapter01/exercise06$(EXEEXT)

run-ch01-ex07: debug
	./build/debug/chapter01/exercise07$(EXEEXT)

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

list:
	@printf '%s\n' $(EXERCISES)

clean:
	$(RM_RF) build
