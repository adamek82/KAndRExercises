BUILD ?= debug

ifeq ($(OS),Windows_NT)
export PATH := C:/msys64/ucrt64/bin;C:/msys64/usr/bin;$(PATH)
CC := gcc
CMP := C:/msys64/usr/bin/cmp.exe
EXEEXT := .exe
else
CC ?= gcc
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
TESTS := \
	test-ch01-ex06 \
	test-ch01-ex07 \
	test-ch01-ex08 \
	test-ch01-ex09 \
	test-ch01-ex10 \
	test-ch01-ex11 \
	test-ch01-ex12 \
	test-ch01-ex13-horizontal \
	test-ch01-ex13-vertical \
	test-ch01-ex14 \
	test-ch01-ex15 \
	test-ch01-ex16 \
	test-ch01-ex17

.PHONY: all build debug release clean list run test test-all \
        test-ch01-ex06 test-ch01-ex07 test-ch01-ex08 test-ch01-ex09 test-ch01-ex10 test-ch01-ex11 test-ch01-ex12 \
        test-ch01-ex13-horizontal test-ch01-ex13-vertical test-ch01-ex14 test-ch01-ex15 test-ch01-ex16 test-ch01-ex17 \
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
	@target=$$(echo "$(EX)" | sed \
		-e 's#^chapter\([0-9][0-9]\)/exercise\([0-9][0-9]\)/\([^/][^/]*\)$$#test-ch\1-ex\2-\3#' \
		-e 's#^chapter\([0-9][0-9]\)/exercise\([0-9][0-9]\)$$#test-ch\1-ex\2#'); \
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

# Use octal byte values here to avoid ambiguity between real control
# characters such as TAB/BACKSPACE and their visible escaped forms
# such as \t, \b, and \\.
test-ch01-ex10: debug
	@$(RM_RF) build/debug/chapter01/exercise10.out build/debug/chapter01/exercise10.expected

	@printf '%s' 'abc' | ./build/debug/chapter01/exercise10$(EXEEXT) > build/debug/chapter01/exercise10.out
	@printf '%s' 'abc' > build/debug/chapter01/exercise10.expected
	@$(CMP) -s build/debug/chapter01/exercise10.out build/debug/chapter01/exercise10.expected

	@printf '\141\011\142\010\134\143' | ./build/debug/chapter01/exercise10$(EXEEXT) > build/debug/chapter01/exercise10.out
	@printf '\141\134\164\142\134\142\134\134\143' > build/debug/chapter01/exercise10.expected
	@$(CMP) -s build/debug/chapter01/exercise10.out build/debug/chapter01/exercise10.expected

	@printf '\011\134\010' | ./build/debug/chapter01/exercise10$(EXEEXT) > build/debug/chapter01/exercise10.out
	@printf '\134\164\134\134\134\142' > build/debug/chapter01/exercise10.expected
	@$(CMP) -s build/debug/chapter01/exercise10.out build/debug/chapter01/exercise10.expected

	@$(RM_RF) build/debug/chapter01/exercise10.out build/debug/chapter01/exercise10.expected
	@echo "chapter01/exercise10 tests passed"

# Normalize CRLF to LF before comparing output. MinGW-built .exe programs
# may translate '\n' to '\r\n' on Windows, while our expected outputs use LF.
test-ch01-ex11: debug
	@printf '%s' '' | ./build/debug/chapter01/exercise11$(EXEEXT) | tr -d '\r' | grep -Fxq '0 0 0'
	@printf '%s' 'one' | ./build/debug/chapter01/exercise11$(EXEEXT) | tr -d '\r' | grep -Fxq '0 1 3'
	@printf 'a\n' | ./build/debug/chapter01/exercise11$(EXEEXT) | tr -d '\r' | grep -Fxq '1 1 2'
	@printf 'ab\n' | ./build/debug/chapter01/exercise11$(EXEEXT) | tr -d '\r' | grep -Fxq '1 1 3'
	@printf 'a b\n' | ./build/debug/chapter01/exercise11$(EXEEXT) | tr -d '\r' | grep -Fxq '1 2 4'
	@printf 'a\nb\n' | ./build/debug/chapter01/exercise11$(EXEEXT) | tr -d '\r' | grep -Fxq '2 2 4'
	@printf '\n\t \n' | ./build/debug/chapter01/exercise11$(EXEEXT) | tr -d '\r' | grep -Fxq '2 0 4'
	@printf '%s' '   word' | ./build/debug/chapter01/exercise11$(EXEEXT) | tr -d '\r' | grep -Fxq '0 1 7'
	@printf '%s' 'word   word' | ./build/debug/chapter01/exercise11$(EXEEXT) | tr -d '\r' | grep -Fxq '0 2 11'
	@printf '\tword\n\nsecond\tthird' | ./build/debug/chapter01/exercise11$(EXEEXT) | tr -d '\r' | grep -Fxq '2 3 19'
	@echo "chapter01/exercise11 tests passed"

test-ch01-ex12: debug
	@$(RM_RF) build/debug/chapter01/exercise12.out build/debug/chapter01/exercise12.expected

	@printf '%s' '' | ./build/debug/chapter01/exercise12$(EXEEXT) | tr -d '\r' > build/debug/chapter01/exercise12.out
	@printf '%s' '' > build/debug/chapter01/exercise12.expected
	@$(CMP) -s build/debug/chapter01/exercise12.out build/debug/chapter01/exercise12.expected

	@printf '%s' 'one' | ./build/debug/chapter01/exercise12$(EXEEXT) | tr -d '\r' > build/debug/chapter01/exercise12.out
	@printf '%s' 'one' > build/debug/chapter01/exercise12.expected
	@$(CMP) -s build/debug/chapter01/exercise12.out build/debug/chapter01/exercise12.expected

	@printf 'one two three' | ./build/debug/chapter01/exercise12$(EXEEXT) | tr -d '\r' > build/debug/chapter01/exercise12.out
	@printf 'one\ntwo\nthree' > build/debug/chapter01/exercise12.expected
	@$(CMP) -s build/debug/chapter01/exercise12.out build/debug/chapter01/exercise12.expected

	@printf '  one   two\tthree  ' | ./build/debug/chapter01/exercise12$(EXEEXT) | tr -d '\r' > build/debug/chapter01/exercise12.out
	@printf 'one\ntwo\nthree\n' > build/debug/chapter01/exercise12.expected
	@$(CMP) -s build/debug/chapter01/exercise12.out build/debug/chapter01/exercise12.expected

	@printf 'one\ntwo\tthree\n' | ./build/debug/chapter01/exercise12$(EXEEXT) | tr -d '\r' > build/debug/chapter01/exercise12.out
	@printf 'one\ntwo\nthree\n' > build/debug/chapter01/exercise12.expected
	@$(CMP) -s build/debug/chapter01/exercise12.out build/debug/chapter01/exercise12.expected

	@printf '\n\t  \n' | ./build/debug/chapter01/exercise12$(EXEEXT) | tr -d '\r' > build/debug/chapter01/exercise12.out
	@printf '%s' '' > build/debug/chapter01/exercise12.expected
	@$(CMP) -s build/debug/chapter01/exercise12.out build/debug/chapter01/exercise12.expected

	@$(RM_RF) build/debug/chapter01/exercise12.out build/debug/chapter01/exercise12.expected
	@echo "chapter01/exercise12 tests passed"

test-ch01-ex13-horizontal: debug
	@$(RM_RF) build/debug/chapter01/exercise13/horizontal.out build/debug/chapter01/exercise13/horizontal.expected

	@printf '%s' 'a bb ccc bb' | ./build/debug/chapter01/exercise13/horizontal$(EXEEXT) | tr -d '\r' > build/debug/chapter01/exercise13/horizontal.out
	@printf '%s\n' 'Length Count Histogram' > build/debug/chapter01/exercise13/horizontal.expected
	@printf '%s\n' '     1     1 *****' >> build/debug/chapter01/exercise13/horizontal.expected
	@printf '%s\n' '     2     2 **********' >> build/debug/chapter01/exercise13/horizontal.expected
	@printf '%s\n' '     3     1 *****' >> build/debug/chapter01/exercise13/horizontal.expected
	@printf '%s\n' '     4     0' >> build/debug/chapter01/exercise13/horizontal.expected
	@printf '%s\n' '     5     0' >> build/debug/chapter01/exercise13/horizontal.expected
	@printf '%s\n' '     6     0' >> build/debug/chapter01/exercise13/horizontal.expected
	@printf '%s\n' '     7     0' >> build/debug/chapter01/exercise13/horizontal.expected
	@printf '%s\n' '     8     0' >> build/debug/chapter01/exercise13/horizontal.expected
	@printf '%s\n' '     9     0' >> build/debug/chapter01/exercise13/horizontal.expected
	@printf '%s\n' '    10     0' >> build/debug/chapter01/exercise13/horizontal.expected
	@printf '%s\n' '   >10     0' >> build/debug/chapter01/exercise13/horizontal.expected
	@$(CMP) -s build/debug/chapter01/exercise13/horizontal.out build/debug/chapter01/exercise13/horizontal.expected

	@printf '%s' 'abcdefghijk' | ./build/debug/chapter01/exercise13/horizontal$(EXEEXT) | tr -d '\r' > build/debug/chapter01/exercise13/horizontal.out
	@printf '%s\n' 'Length Count Histogram' > build/debug/chapter01/exercise13/horizontal.expected
	@printf '%s\n' '     1     0' >> build/debug/chapter01/exercise13/horizontal.expected
	@printf '%s\n' '     2     0' >> build/debug/chapter01/exercise13/horizontal.expected
	@printf '%s\n' '     3     0' >> build/debug/chapter01/exercise13/horizontal.expected
	@printf '%s\n' '     4     0' >> build/debug/chapter01/exercise13/horizontal.expected
	@printf '%s\n' '     5     0' >> build/debug/chapter01/exercise13/horizontal.expected
	@printf '%s\n' '     6     0' >> build/debug/chapter01/exercise13/horizontal.expected
	@printf '%s\n' '     7     0' >> build/debug/chapter01/exercise13/horizontal.expected
	@printf '%s\n' '     8     0' >> build/debug/chapter01/exercise13/horizontal.expected
	@printf '%s\n' '     9     0' >> build/debug/chapter01/exercise13/horizontal.expected
	@printf '%s\n' '    10     0' >> build/debug/chapter01/exercise13/horizontal.expected
	@printf '%s\n' '   >10     1 **********' >> build/debug/chapter01/exercise13/horizontal.expected
	@$(CMP) -s build/debug/chapter01/exercise13/horizontal.out build/debug/chapter01/exercise13/horizontal.expected

	@$(RM_RF) build/debug/chapter01/exercise13/horizontal.out build/debug/chapter01/exercise13/horizontal.expected
	@echo "chapter01/exercise13/horizontal tests passed"

test-ch01-ex13-vertical: debug
	@$(RM_RF) build/debug/chapter01/exercise13/vertical.out build/debug/chapter01/exercise13/vertical.expected

	@printf '%s' 'a bb ccc bb' | ./build/debug/chapter01/exercise13/vertical$(EXEEXT) | tr -d '\r' | sed 's/[[:space:]]*$$//' > build/debug/chapter01/exercise13/vertical.out
	@printf '%s\n' 'Length Histogram' > build/debug/chapter01/exercise13/vertical.expected
	@printf '%s\n' '       *' >> build/debug/chapter01/exercise13/vertical.expected
	@printf '%s\n' '       *' >> build/debug/chapter01/exercise13/vertical.expected
	@printf '%s\n' '       *' >> build/debug/chapter01/exercise13/vertical.expected
	@printf '%s\n' '       *' >> build/debug/chapter01/exercise13/vertical.expected
	@printf '%s\n' '       *' >> build/debug/chapter01/exercise13/vertical.expected
	@printf '%s\n' '   *   *   *' >> build/debug/chapter01/exercise13/vertical.expected
	@printf '%s\n' '   *   *   *' >> build/debug/chapter01/exercise13/vertical.expected
	@printf '%s\n' '   *   *   *' >> build/debug/chapter01/exercise13/vertical.expected
	@printf '%s\n' '   *   *   *' >> build/debug/chapter01/exercise13/vertical.expected
	@printf '%s\n' '   *   *   *' >> build/debug/chapter01/exercise13/vertical.expected
	@printf '%s\n' '   1   2   3   4   5   6   7   8   9  10 >10' >> build/debug/chapter01/exercise13/vertical.expected
	@printf '%s\n' '   1   2   1   0   0   0   0   0   0   0   0' >> build/debug/chapter01/exercise13/vertical.expected
	@$(CMP) -s build/debug/chapter01/exercise13/vertical.out build/debug/chapter01/exercise13/vertical.expected

	@printf '%s' 'abcdefghijk' | ./build/debug/chapter01/exercise13/vertical$(EXEEXT) | tr -d '\r' | sed 's/[[:space:]]*$$//' > build/debug/chapter01/exercise13/vertical.out
	@printf '%s\n' 'Length Histogram' > build/debug/chapter01/exercise13/vertical.expected
	@printf '%s\n' '                                           *' >> build/debug/chapter01/exercise13/vertical.expected
	@printf '%s\n' '                                           *' >> build/debug/chapter01/exercise13/vertical.expected
	@printf '%s\n' '                                           *' >> build/debug/chapter01/exercise13/vertical.expected
	@printf '%s\n' '                                           *' >> build/debug/chapter01/exercise13/vertical.expected
	@printf '%s\n' '                                           *' >> build/debug/chapter01/exercise13/vertical.expected
	@printf '%s\n' '                                           *' >> build/debug/chapter01/exercise13/vertical.expected
	@printf '%s\n' '                                           *' >> build/debug/chapter01/exercise13/vertical.expected
	@printf '%s\n' '                                           *' >> build/debug/chapter01/exercise13/vertical.expected
	@printf '%s\n' '                                           *' >> build/debug/chapter01/exercise13/vertical.expected
	@printf '%s\n' '                                           *' >> build/debug/chapter01/exercise13/vertical.expected
	@printf '%s\n' '   1   2   3   4   5   6   7   8   9  10 >10' >> build/debug/chapter01/exercise13/vertical.expected
	@printf '%s\n' '   0   0   0   0   0   0   0   0   0   0   1' >> build/debug/chapter01/exercise13/vertical.expected
	@$(CMP) -s build/debug/chapter01/exercise13/vertical.out build/debug/chapter01/exercise13/vertical.expected

	@$(RM_RF) build/debug/chapter01/exercise13/vertical.out build/debug/chapter01/exercise13/vertical.expected
	@echo "chapter01/exercise13/vertical tests passed"

test-ch01-ex14: debug
	@$(RM_RF) build/debug/chapter01/exercise14.out build/debug/chapter01/exercise14.expected

	@printf '%s' 'aab' | ./build/debug/chapter01/exercise14$(EXEEXT) | tr -d '\r' > build/debug/chapter01/exercise14.out
	@printf '%s\n' 'Code Char Count Histogram' > build/debug/chapter01/exercise14.expected
	@printf '%s\n' '  97    a     2 **********' >> build/debug/chapter01/exercise14.expected
	@printf '%s\n' '  98    b     1 *****' >> build/debug/chapter01/exercise14.expected
	@$(CMP) -s build/debug/chapter01/exercise14.out build/debug/chapter01/exercise14.expected

	@printf '\040\011\134\012' | ./build/debug/chapter01/exercise14$(EXEEXT) | tr -d '\r' > build/debug/chapter01/exercise14.out
	@printf '%s\n' 'Code Char Count Histogram' > build/debug/chapter01/exercise14.expected
	@printf '%s\n' '   9   \t     1 **********' >> build/debug/chapter01/exercise14.expected
	@printf '%s\n' '  10   \n     1 **********' >> build/debug/chapter01/exercise14.expected
	@printf '%s\n' '  32   sp     1 **********' >> build/debug/chapter01/exercise14.expected
	@printf '%s\n' '  92   \\\\     1 **********' >> build/debug/chapter01/exercise14.expected
	@$(CMP) -s build/debug/chapter01/exercise14.out build/debug/chapter01/exercise14.expected

	@$(RM_RF) build/debug/chapter01/exercise14.out build/debug/chapter01/exercise14.expected
	@echo "chapter01/exercise14 tests passed"

test-ch01-ex15: debug
	@./build/debug/chapter01/exercise15$(EXEEXT) | tr -d '\r' > build/debug/chapter01/exercise15.out
	@grep -Fxq 'Fahr Celsius' build/debug/chapter01/exercise15.out
	@grep -Fxq '   0   -17.8' build/debug/chapter01/exercise15.out
	@grep -Fxq ' 100    37.8' build/debug/chapter01/exercise15.out
	@grep -Fxq ' 300   148.9' build/debug/chapter01/exercise15.out
	@$(RM_RF) build/debug/chapter01/exercise15.out
	@echo "chapter01/exercise15 tests passed"

test-ch01-ex16: debug
	@$(RM_RF) build/debug/chapter01/exercise16.out build/debug/chapter01/exercise16.expected

	@printf 'short\nlonger\nx\n' | ./build/debug/chapter01/exercise16$(EXEEXT) | tr -d '\r' > build/debug/chapter01/exercise16.out
	@printf '7\nlonger\n' > build/debug/chapter01/exercise16.expected
	@$(CMP) -s build/debug/chapter01/exercise16.out build/debug/chapter01/exercise16.expected

	@(i=0; while [ $$i -lt 1001 ]; do printf x; i=$$((i + 1)); done; printf '\n') | ./build/debug/chapter01/exercise16$(EXEEXT) | tr -d '\r' > build/debug/chapter01/exercise16.out
	@printf '1002\n' > build/debug/chapter01/exercise16.expected
	@(i=0; while [ $$i -lt 999 ]; do printf x; i=$$((i + 1)); done) >> build/debug/chapter01/exercise16.expected
	@$(CMP) -s build/debug/chapter01/exercise16.out build/debug/chapter01/exercise16.expected

	@(i=0; while [ $$i -lt 1001 ]; do printf y; i=$$((i + 1)); done) | ./build/debug/chapter01/exercise16$(EXEEXT) | tr -d '\r' > build/debug/chapter01/exercise16.out
	@printf '1001\n' > build/debug/chapter01/exercise16.expected
	@(i=0; while [ $$i -lt 999 ]; do printf y; i=$$((i + 1)); done) >> build/debug/chapter01/exercise16.expected
	@$(CMP) -s build/debug/chapter01/exercise16.out build/debug/chapter01/exercise16.expected

	@$(RM_RF) build/debug/chapter01/exercise16.out build/debug/chapter01/exercise16.expected
	@echo "chapter01/exercise16 tests passed"

test-ch01-ex17: debug
	@$(RM_RF) build/debug/chapter01/exercise17.out build/debug/chapter01/exercise17.expected

	@printf 'short\n' | ./build/debug/chapter01/exercise17$(EXEEXT) | tr -d '\r' > build/debug/chapter01/exercise17.out
	@printf '%s' '' > build/debug/chapter01/exercise17.expected
	@$(CMP) -s build/debug/chapter01/exercise17.out build/debug/chapter01/exercise17.expected

	@(i=0; while [ $$i -lt 79 ]; do printf a; i=$$((i + 1)); done; printf '\n') | ./build/debug/chapter01/exercise17$(EXEEXT) | tr -d '\r' > build/debug/chapter01/exercise17.out
	@printf '%s' '' > build/debug/chapter01/exercise17.expected
	@$(CMP) -s build/debug/chapter01/exercise17.out build/debug/chapter01/exercise17.expected

	@(i=0; while [ $$i -lt 80 ]; do printf b; i=$$((i + 1)); done; printf '\n') | ./build/debug/chapter01/exercise17$(EXEEXT) | tr -d '\r' > build/debug/chapter01/exercise17.out
	@(i=0; while [ $$i -lt 80 ]; do printf b; i=$$((i + 1)); done; printf '\n') > build/debug/chapter01/exercise17.expected
	@$(CMP) -s build/debug/chapter01/exercise17.out build/debug/chapter01/exercise17.expected

	@printf 'short\n' > build/debug/chapter01/exercise17.input
	@(i=0; while [ $$i -lt 80 ]; do printf c; i=$$((i + 1)); done; printf '\n') >> build/debug/chapter01/exercise17.input
	@printf 'tiny\n' >> build/debug/chapter01/exercise17.input
	@(i=0; while [ $$i -lt 81 ]; do printf d; i=$$((i + 1)); done; printf '\n') >> build/debug/chapter01/exercise17.input
	@./build/debug/chapter01/exercise17$(EXEEXT) < build/debug/chapter01/exercise17.input | tr -d '\r' > build/debug/chapter01/exercise17.out
	@(i=0; while [ $$i -lt 80 ]; do printf c; i=$$((i + 1)); done; printf '\n') > build/debug/chapter01/exercise17.expected
	@(i=0; while [ $$i -lt 81 ]; do printf d; i=$$((i + 1)); done; printf '\n') >> build/debug/chapter01/exercise17.expected
	@$(CMP) -s build/debug/chapter01/exercise17.out build/debug/chapter01/exercise17.expected

	@(i=0; while [ $$i -lt 1001 ]; do printf x; i=$$((i + 1)); done; printf '\n') | ./build/debug/chapter01/exercise17$(EXEEXT) | tr -d '\r' > build/debug/chapter01/exercise17.out
	@(i=0; while [ $$i -lt 999 ]; do printf x; i=$$((i + 1)); done) > build/debug/chapter01/exercise17.expected
	@$(CMP) -s build/debug/chapter01/exercise17.out build/debug/chapter01/exercise17.expected

	@$(RM_RF) build/debug/chapter01/exercise17.out build/debug/chapter01/exercise17.expected build/debug/chapter01/exercise17.input
	@echo "chapter01/exercise17 tests passed"

list:
	@printf '%s\n' $(EXERCISES)

clean:
	$(RM_RF) build
