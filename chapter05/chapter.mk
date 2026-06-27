CHAPTER05_TESTS := \
	test-ch05-ex01 \
	test-ch05-ex02 \
	test-ch05-ex03 \
	test-ch05-ex04 \
	test-ch05-ex05 \
	test-ch05-ex06 \
	test-ch05-ex07 \
	test-ch05-ex08

TESTS += $(CHAPTER05_TESTS)
PHONY_TARGETS += $(CHAPTER05_TESTS)

ifeq ($(BUILD),release)
CH05_EX07_BENCH_FLAGS := -DMAXLINES=8000 -DMAXSTOR=800000 -DBENCH_LINES=5000 -DBENCH_REPEAT=2000
else
CH05_EX07_BENCH_FLAGS := -DMAXLINES=2000 -DMAXSTOR=200000 -DBENCH_LINES=1000 -DBENCH_REPEAT=50
endif

$(OUTDIR)/chapter05/exercise07$(EXEEXT): chapter05/exercise07/main.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) $(CH05_EX07_BENCH_FLAGS) $< -o $@

test-ch05-ex01: debug
	@$(RM_RF) build/debug/chapter05/exercise01.out

	@printf '' | ./build/debug/chapter05/exercise01$(EXEEXT) | tr -d '\r' > build/debug/chapter05/exercise01.out
	@grep -Fxq 'getint("123x"): status=1 value=123 next=x' build/debug/chapter05/exercise01.out
	@grep -Fxq 'getint("-42x"): status=1 value=-42 next=x' build/debug/chapter05/exercise01.out
	@grep -Fxq 'getint("+x"): status=0 next=+x' build/debug/chapter05/exercise01.out
	@grep -Fxq 'getint checks: ok' build/debug/chapter05/exercise01.out

	@$(RM_RF) build/debug/chapter05/exercise01.out
	@echo "chapter05/exercise01 tests passed"

test-ch05-ex02: debug
	@$(RM_RF) build/debug/chapter05/exercise02.out

	@printf '' | ./build/debug/chapter05/exercise02$(EXEEXT) | tr -d '\r' > build/debug/chapter05/exercise02.out
	@grep -Fxq 'getfloat("123.45x"): status=1 value=123.45 next=x' build/debug/chapter05/exercise02.out
	@grep -Fxq 'getfloat("-.5x"): status=1 value=-0.5 next=x' build/debug/chapter05/exercise02.out
	@grep -Fxq 'getfloat("+x"): status=0 next=+x' build/debug/chapter05/exercise02.out
	@grep -Fxq 'getfloat checks: ok' build/debug/chapter05/exercise02.out

	@$(RM_RF) build/debug/chapter05/exercise02.out
	@echo "chapter05/exercise02 tests passed"

test-ch05-ex03: debug
	@$(RM_RF) build/debug/chapter05/exercise03.out

	@./build/debug/chapter05/exercise03$(EXEEXT) | tr -d '\r' > build/debug/chapter05/exercise03.out
	@grep -Fxq 'strcat_pointer("hello", " world") = hello world' build/debug/chapter05/exercise03.out
	@grep -Fxq 'strcat_pointer("", "empty destination") = empty destination' build/debug/chapter05/exercise03.out
	@grep -Fxq 'strcat_pointer("K&R", "") = K&R' build/debug/chapter05/exercise03.out
	@grep -Fxq 'strcat_pointer checks: ok' build/debug/chapter05/exercise03.out

	@$(RM_RF) build/debug/chapter05/exercise03.out
	@echo "chapter05/exercise03 tests passed"

test-ch05-ex04: debug
	@$(RM_RF) build/debug/chapter05/exercise04.out

	@./build/debug/chapter05/exercise04$(EXEEXT) | tr -d '\r' > build/debug/chapter05/exercise04.out
	@grep -Fxq 'strend("hello world", "world") = 1' build/debug/chapter05/exercise04.out
	@grep -Fxq 'strend("hello world", "hello") = 0' build/debug/chapter05/exercise04.out
	@grep -Fxq 'strend("abc", "abc") = 1' build/debug/chapter05/exercise04.out
	@grep -Fxq 'strend("abc", "") = 1' build/debug/chapter05/exercise04.out
	@grep -Fxq 'strend checks: ok' build/debug/chapter05/exercise04.out

	@$(RM_RF) build/debug/chapter05/exercise04.out
	@echo "chapter05/exercise04 tests passed"

test-ch05-ex05: debug
	@$(RM_RF) build/debug/chapter05/exercise05.out

	@./build/debug/chapter05/exercise05$(EXEEXT) | tr -d '\r' > build/debug/chapter05/exercise05.out
	@grep -Fxq 'kr_strncat("hello", " world", 3) = hello wo' build/debug/chapter05/exercise05.out
	@grep -Fxq 'kr_strncpy("abc", "xy", 5) = xy' build/debug/chapter05/exercise05.out
	@grep -Fxq 'kr_strncpy("", "abcdef", 3) prefix = abc' build/debug/chapter05/exercise05.out
	@grep -Fxq 'kr_strncmp("abc", "abd", 2) = 0' build/debug/chapter05/exercise05.out
	@grep -Fxq 'string function checks: ok' build/debug/chapter05/exercise05.out

	@$(RM_RF) build/debug/chapter05/exercise05.out
	@echo "chapter05/exercise05 tests passed"

test-ch05-ex06: debug
	@$(RM_RF) build/debug/chapter05/exercise06.out

	@printf 'hello line\n' | ./build/debug/chapter05/exercise06$(EXEEXT) | tr -d '\r' > build/debug/chapter05/exercise06.out
	@grep -Fxq 'get_line = hello line' build/debug/chapter05/exercise06.out
	@grep -Fxq 'kr_atoi("  -123x") = -123' build/debug/chapter05/exercise06.out
	@grep -Fxq 'kr_itoa(INT_MIN) = -2147483648' build/debug/chapter05/exercise06.out
	@grep -Fxq 'reverse("hello") = olleh' build/debug/chapter05/exercise06.out
	@grep -Fxq 'strindex("hello world", "world") = 6' build/debug/chapter05/exercise06.out
	@grep -Fxq 'pointer function checks: ok' build/debug/chapter05/exercise06.out

	@$(RM_RF) build/debug/chapter05/exercise06.out
	@echo "chapter05/exercise06 tests passed"

test-ch05-ex07: debug
	@$(RM_RF) build/debug/chapter05/exercise07.out

	@./build/debug/chapter05/exercise07$(EXEEXT) | tr -d '\r' > build/debug/chapter05/exercise07.out
	@grep -Fxq 'readlines_store sample count: 3' build/debug/chapter05/exercise07.out
	@grep -Fxq 'first sample line: line 00000: quick brown fox jumps 000' build/debug/chapter05/exercise07.out
	@grep -Fxq 'last sample line: line 00002: quick brown fox jumps 002' build/debug/chapter05/exercise07.out
	@grep -Fxq 'readlines checks: ok' build/debug/chapter05/exercise07.out
	@grep -Fxq 'benchmark lines: 1000' build/debug/chapter05/exercise07.out
	@grep -Fxq 'benchmark repeats: 50' build/debug/chapter05/exercise07.out

	@$(RM_RF) build/debug/chapter05/exercise07.out
	@echo "chapter05/exercise07 tests passed"

test-ch05-ex08: debug
	@$(RM_RF) build/debug/chapter05/exercise08.out

	@./build/debug/chapter05/exercise08$(EXEEXT) | tr -d '\r' > build/debug/chapter05/exercise08.out
	@grep -Fq 'day_of_year(1988, 2, 29) = 60: PASS' build/debug/chapter05/exercise08.out
	@grep -Fq 'day_of_year(1989, 2, 29) = -1: PASS' build/debug/chapter05/exercise08.out
	@grep -Fq 'month_day(1988, 60) = 2/29: PASS' build/debug/chapter05/exercise08.out
	@grep -Fq 'month_day(1989, 366) = -1/-1: PASS' build/debug/chapter05/exercise08.out

	@$(RM_RF) build/debug/chapter05/exercise08.out
	@echo "chapter05/exercise08 tests passed"
