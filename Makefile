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

ifeq ($(BUILD),release)
CFLAGS := -std=c89 -Wall -Wextra -pedantic -O2 -DNDEBUG
OUTDIR := build/release
else
CFLAGS := -std=c89 -Wall -Wextra -pedantic -g -O0
OUTDIR := build/debug
endif

EXERCISES := chapter01/exercise01

TARGETS := $(addsuffix $(EXEEXT),$(addprefix $(OUTDIR)/,$(EXERCISES)))

.PHONY: all debug release clean run-ch01-ex01 list

all: debug

debug:
	$(MAKE) BUILD=debug $(TARGETS)

release:
	$(MAKE) BUILD=release $(TARGETS)

$(OUTDIR)/chapter01/exercise01$(EXEEXT): chapter01/exercise01/main.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) chapter01/exercise01/main.c -o $(OUTDIR)/chapter01/exercise01$(EXEEXT)

run-ch01-ex01: debug
	./build/debug/chapter01/exercise01$(EXEEXT)

list:
	@echo $(EXERCISES)

clean:
	$(RM_RF) build
