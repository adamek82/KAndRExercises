CHAPTER05_TESTS := \
	test-ch05-ex01 \
	test-ch05-ex02 \
	test-ch05-ex03 \
	test-ch05-ex04 \
	test-ch05-ex05 \
	test-ch05-ex06 \
	test-ch05-ex07 \
	test-ch05-ex08 \
	test-ch05-ex09 \
	test-ch05-ex10 \
	test-ch05-ex11-entab \
	test-ch05-ex11-detab \
	test-ch05-ex12-entab \
	test-ch05-ex12-detab \
	test-ch05-ex13 \
	test-ch05-ex14 \
	test-ch05-ex15 \
	test-ch05-ex16 \
	test-ch05-ex17

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

test-ch05-ex09: debug
	@$(RM_RF) build/debug/chapter05/exercise09.out

	@./build/debug/chapter05/exercise09$(EXEEXT) | tr -d '\r' > build/debug/chapter05/exercise09.out
	@grep -Fq 'day_of_year(1988, 2, 29) = 60: PASS' build/debug/chapter05/exercise09.out
	@grep -Fq 'day_of_year(1989, 2, 29) = -1: PASS' build/debug/chapter05/exercise09.out
	@grep -Fq 'month_day(1988, 60) = 2/29: PASS' build/debug/chapter05/exercise09.out
	@grep -Fq 'month_day(1989, 366) = -1/-1: PASS' build/debug/chapter05/exercise09.out

	@$(RM_RF) build/debug/chapter05/exercise09.out
	@echo "chapter05/exercise09 tests passed"

test-ch05-ex10: debug
	@$(RM_RF) build/debug/chapter05/exercise10.out

	@./build/debug/chapter05/exercise10$(EXEEXT) 2 3 4 + '*' | tr -d '\r' > build/debug/chapter05/exercise10.out
	@grep -Fxq '14' build/debug/chapter05/exercise10.out
	@./build/debug/chapter05/exercise10$(EXEEXT) 5 2 - | tr -d '\r' > build/debug/chapter05/exercise10.out
	@grep -Fxq '3' build/debug/chapter05/exercise10.out
	@./build/debug/chapter05/exercise10$(EXEEXT) -2 3 '*' | tr -d '\r' > build/debug/chapter05/exercise10.out
	@grep -Fxq -- '-6' build/debug/chapter05/exercise10.out
	@MSYS2_ARG_CONV_EXCL=/ ./build/debug/chapter05/exercise10$(EXEEXT) 7 2 / | tr -d '\r' > build/debug/chapter05/exercise10.out
	@grep -Fxq '3.5' build/debug/chapter05/exercise10.out

	@$(RM_RF) build/debug/chapter05/exercise10.out
	@echo "chapter05/exercise10 tests passed"

test-ch05-ex11-entab: debug
	@$(RM_RF) build/debug/chapter05/exercise11/entab.out build/debug/chapter05/exercise11/entab.expected

	@printf 'ab  cd\n' | ./build/debug/chapter05/exercise11/entab$(EXEEXT) 4 8 | tr -d '\r' > build/debug/chapter05/exercise11/entab.out
	@printf 'ab\tcd\n' > build/debug/chapter05/exercise11/entab.expected
	@$(CMP) -s build/debug/chapter05/exercise11/entab.out build/debug/chapter05/exercise11/entab.expected

	@printf 'ab      cd\n' | ./build/debug/chapter05/exercise11/entab$(EXEEXT) | tr -d '\r' > build/debug/chapter05/exercise11/entab.out
	@printf 'ab\tcd\n' > build/debug/chapter05/exercise11/entab.expected
	@$(CMP) -s build/debug/chapter05/exercise11/entab.out build/debug/chapter05/exercise11/entab.expected

	@$(RM_RF) build/debug/chapter05/exercise11/entab.out build/debug/chapter05/exercise11/entab.expected
	@echo "chapter05/exercise11/entab tests passed"

test-ch05-ex11-detab: debug
	@$(RM_RF) build/debug/chapter05/exercise11/detab.out build/debug/chapter05/exercise11/detab.expected

	@printf 'ab\tcd\n' | ./build/debug/chapter05/exercise11/detab$(EXEEXT) 4 8 | tr -d '\r' > build/debug/chapter05/exercise11/detab.out
	@printf 'ab  cd\n' > build/debug/chapter05/exercise11/detab.expected
	@$(CMP) -s build/debug/chapter05/exercise11/detab.out build/debug/chapter05/exercise11/detab.expected

	@printf 'ab\tcd\n' | ./build/debug/chapter05/exercise11/detab$(EXEEXT) | tr -d '\r' > build/debug/chapter05/exercise11/detab.out
	@printf 'ab      cd\n' > build/debug/chapter05/exercise11/detab.expected
	@$(CMP) -s build/debug/chapter05/exercise11/detab.out build/debug/chapter05/exercise11/detab.expected

	@$(RM_RF) build/debug/chapter05/exercise11/detab.out build/debug/chapter05/exercise11/detab.expected
	@echo "chapter05/exercise11/detab tests passed"

test-ch05-ex12-entab: debug
	@$(RM_RF) build/debug/chapter05/exercise12/entab.out build/debug/chapter05/exercise12/entab.expected

	@printf 'ab  cd\n' | ./build/debug/chapter05/exercise12/entab$(EXEEXT) -4 +4 | tr -d '\r' > build/debug/chapter05/exercise12/entab.out
	@printf 'ab\tcd\n' > build/debug/chapter05/exercise12/entab.expected
	@$(CMP) -s build/debug/chapter05/exercise12/entab.out build/debug/chapter05/exercise12/entab.expected

	@printf 'ab   cd\n' | ./build/debug/chapter05/exercise12/entab$(EXEEXT) -5 +3 | tr -d '\r' > build/debug/chapter05/exercise12/entab.out
	@printf 'ab\tcd\n' > build/debug/chapter05/exercise12/entab.expected
	@$(CMP) -s build/debug/chapter05/exercise12/entab.out build/debug/chapter05/exercise12/entab.expected

	@printf 'ab  cd\n' | ./build/debug/chapter05/exercise12/entab$(EXEEXT) +4 | tr -d '\r' > build/debug/chapter05/exercise12/entab.out
	@printf 'ab\tcd\n' > build/debug/chapter05/exercise12/entab.expected
	@$(CMP) -s build/debug/chapter05/exercise12/entab.out build/debug/chapter05/exercise12/entab.expected

	@$(RM_RF) build/debug/chapter05/exercise12/entab.out build/debug/chapter05/exercise12/entab.expected
	@echo "chapter05/exercise12/entab tests passed"

test-ch05-ex12-detab: debug
	@$(RM_RF) build/debug/chapter05/exercise12/detab.out build/debug/chapter05/exercise12/detab.expected

	@printf 'ab\tcd\n' | ./build/debug/chapter05/exercise12/detab$(EXEEXT) -4 +4 | tr -d '\r' > build/debug/chapter05/exercise12/detab.out
	@printf 'ab  cd\n' > build/debug/chapter05/exercise12/detab.expected
	@$(CMP) -s build/debug/chapter05/exercise12/detab.out build/debug/chapter05/exercise12/detab.expected

	@printf 'ab\tcd\n' | ./build/debug/chapter05/exercise12/detab$(EXEEXT) -5 +3 | tr -d '\r' > build/debug/chapter05/exercise12/detab.out
	@printf 'ab   cd\n' > build/debug/chapter05/exercise12/detab.expected
	@$(CMP) -s build/debug/chapter05/exercise12/detab.out build/debug/chapter05/exercise12/detab.expected

	@printf 'ab\tcd\n' | ./build/debug/chapter05/exercise12/detab$(EXEEXT) +4 | tr -d '\r' > build/debug/chapter05/exercise12/detab.out
	@printf 'ab  cd\n' > build/debug/chapter05/exercise12/detab.expected
	@$(CMP) -s build/debug/chapter05/exercise12/detab.out build/debug/chapter05/exercise12/detab.expected

	@$(RM_RF) build/debug/chapter05/exercise12/detab.out build/debug/chapter05/exercise12/detab.expected
	@echo "chapter05/exercise12/detab tests passed"

test-ch05-ex13: debug
	@$(RM_RF) build/debug/chapter05/exercise13.out build/debug/chapter05/exercise13.expected

	@printf '%s\n' one two three four five | ./build/debug/chapter05/exercise13$(EXEEXT) -3 | tr -d '\r' > build/debug/chapter05/exercise13.out
	@printf '%s\n' three four five > build/debug/chapter05/exercise13.expected
	@$(CMP) -s build/debug/chapter05/exercise13.out build/debug/chapter05/exercise13.expected

	@printf '%s\n' one two three | ./build/debug/chapter05/exercise13$(EXEEXT) -10 | tr -d '\r' > build/debug/chapter05/exercise13.out
	@printf '%s\n' one two three > build/debug/chapter05/exercise13.expected
	@$(CMP) -s build/debug/chapter05/exercise13.out build/debug/chapter05/exercise13.expected

	@printf '%s\n' one two three | ./build/debug/chapter05/exercise13$(EXEEXT) -0 | tr -d '\r' > build/debug/chapter05/exercise13.out
	@printf '%s' '' > build/debug/chapter05/exercise13.expected
	@$(CMP) -s build/debug/chapter05/exercise13.out build/debug/chapter05/exercise13.expected

	@$(RM_RF) build/debug/chapter05/exercise13.out build/debug/chapter05/exercise13.expected
	@echo "chapter05/exercise13 tests passed"

test-ch05-ex14: debug
	@$(RM_RF) build/debug/chapter05/exercise14.out build/debug/chapter05/exercise14.expected

	@printf '%s\n' banana apple cherry | ./build/debug/chapter05/exercise14$(EXEEXT) | tr -d '\r' > build/debug/chapter05/exercise14.out
	@printf '%s\n' apple banana cherry > build/debug/chapter05/exercise14.expected
	@$(CMP) -s build/debug/chapter05/exercise14.out build/debug/chapter05/exercise14.expected

	@printf '%s\n' banana apple cherry | ./build/debug/chapter05/exercise14$(EXEEXT) -r | tr -d '\r' > build/debug/chapter05/exercise14.out
	@printf '%s\n' cherry banana apple > build/debug/chapter05/exercise14.expected
	@$(CMP) -s build/debug/chapter05/exercise14.out build/debug/chapter05/exercise14.expected

	@printf '%s\n' 2 10 -5 3 | ./build/debug/chapter05/exercise14$(EXEEXT) -n | tr -d '\r' > build/debug/chapter05/exercise14.out
	@printf '%s\n' -5 2 3 10 > build/debug/chapter05/exercise14.expected
	@$(CMP) -s build/debug/chapter05/exercise14.out build/debug/chapter05/exercise14.expected

	@printf '%s\n' 2 10 -5 3 | ./build/debug/chapter05/exercise14$(EXEEXT) -n -r | tr -d '\r' > build/debug/chapter05/exercise14.out
	@printf '%s\n' 10 3 2 -5 > build/debug/chapter05/exercise14.expected
	@$(CMP) -s build/debug/chapter05/exercise14.out build/debug/chapter05/exercise14.expected

	@printf '%s\n' 2 10 -5 3 | ./build/debug/chapter05/exercise14$(EXEEXT) -rn | tr -d '\r' > build/debug/chapter05/exercise14.out
	@printf '%s\n' 10 3 2 -5 > build/debug/chapter05/exercise14.expected
	@$(CMP) -s build/debug/chapter05/exercise14.out build/debug/chapter05/exercise14.expected

	@printf 'b\na' | ./build/debug/chapter05/exercise14$(EXEEXT) | tr -d '\r' > build/debug/chapter05/exercise14.out
	@printf 'a\nb\n' > build/debug/chapter05/exercise14.expected
	@$(CMP) -s build/debug/chapter05/exercise14.out build/debug/chapter05/exercise14.expected

	@$(RM_RF) build/debug/chapter05/exercise14.out build/debug/chapter05/exercise14.expected
	@echo "chapter05/exercise14 tests passed"

test-ch05-ex15: debug
	@$(RM_RF) build/debug/chapter05/exercise15.out build/debug/chapter05/exercise15.expected

	@printf '%s\n' Zebra apple Banana cherry | ./build/debug/chapter05/exercise15$(EXEEXT) | tr -d '\r' > build/debug/chapter05/exercise15.out
	@printf '%s\n' Banana Zebra apple cherry > build/debug/chapter05/exercise15.expected
	@$(CMP) -s build/debug/chapter05/exercise15.out build/debug/chapter05/exercise15.expected

	@printf '%s\n' Zebra apple Banana cherry | ./build/debug/chapter05/exercise15$(EXEEXT) -f | tr -d '\r' > build/debug/chapter05/exercise15.out
	@printf '%s\n' apple Banana cherry Zebra > build/debug/chapter05/exercise15.expected
	@$(CMP) -s build/debug/chapter05/exercise15.out build/debug/chapter05/exercise15.expected

	@printf '%s\n' Zebra apple Banana cherry | ./build/debug/chapter05/exercise15$(EXEEXT) -rf | tr -d '\r' > build/debug/chapter05/exercise15.out
	@printf '%s\n' Zebra cherry Banana apple > build/debug/chapter05/exercise15.expected
	@$(CMP) -s build/debug/chapter05/exercise15.out build/debug/chapter05/exercise15.expected

	@printf '%s\n' 2 10 -5 3 | ./build/debug/chapter05/exercise15$(EXEEXT) -nrf | tr -d '\r' > build/debug/chapter05/exercise15.out
	@printf '%s\n' 10 3 2 -5 > build/debug/chapter05/exercise15.expected
	@$(CMP) -s build/debug/chapter05/exercise15.out build/debug/chapter05/exercise15.expected

	@$(RM_RF) build/debug/chapter05/exercise15.out build/debug/chapter05/exercise15.expected
	@echo "chapter05/exercise15 tests passed"

test-ch05-ex16: debug
	@$(RM_RF) build/debug/chapter05/exercise16.out build/debug/chapter05/exercise16.expected

	@printf '%s\n' a-b a1 'a b' 'a?z' | ./build/debug/chapter05/exercise16$(EXEEXT) | tr -d '\r' > build/debug/chapter05/exercise16.out
	@printf '%s\n' 'a b' a-b a1 'a?z' > build/debug/chapter05/exercise16.expected
	@$(CMP) -s build/debug/chapter05/exercise16.out build/debug/chapter05/exercise16.expected

	@printf '%s\n' a-b a1 'a b' 'a?z' | ./build/debug/chapter05/exercise16$(EXEEXT) -d | tr -d '\r' > build/debug/chapter05/exercise16.out
	@printf '%s\n' 'a b' a1 a-b 'a?z' > build/debug/chapter05/exercise16.expected
	@$(CMP) -s build/debug/chapter05/exercise16.out build/debug/chapter05/exercise16.expected

	@printf '%s\n' Zebra apple Banana cherry | ./build/debug/chapter05/exercise16$(EXEEXT) -f | tr -d '\r' > build/debug/chapter05/exercise16.out
	@printf '%s\n' apple Banana cherry Zebra > build/debug/chapter05/exercise16.expected
	@$(CMP) -s build/debug/chapter05/exercise16.out build/debug/chapter05/exercise16.expected

	@printf '%s\n' B-a a_9 'A 2' 'a#1' | ./build/debug/chapter05/exercise16$(EXEEXT) -df | tr -d '\r' > build/debug/chapter05/exercise16.out
	@printf '%s\n' 'A 2' 'a#1' a_9 B-a > build/debug/chapter05/exercise16.expected
	@$(CMP) -s build/debug/chapter05/exercise16.out build/debug/chapter05/exercise16.expected

	@printf '%s\n' B-a a_9 'A 2' 'a#1' | ./build/debug/chapter05/exercise16$(EXEEXT) -r -d -f | tr -d '\r' > build/debug/chapter05/exercise16.out
	@printf '%s\n' B-a a_9 'a#1' 'A 2' > build/debug/chapter05/exercise16.expected
	@$(CMP) -s build/debug/chapter05/exercise16.out build/debug/chapter05/exercise16.expected

	@printf '%s\n' 2 10 -5 3 | ./build/debug/chapter05/exercise16$(EXEEXT) -nrf -d | tr -d '\r' > build/debug/chapter05/exercise16.out
	@printf '%s\n' 10 3 2 -5 > build/debug/chapter05/exercise16.expected
	@$(CMP) -s build/debug/chapter05/exercise16.out build/debug/chapter05/exercise16.expected

	@printf 'a\t1\na 2\n' | ./build/debug/chapter05/exercise16$(EXEEXT) -d | tr -d '\r' > build/debug/chapter05/exercise16.out
	@printf 'a\t1\na 2\n' > build/debug/chapter05/exercise16.expected
	@$(CMP) -s build/debug/chapter05/exercise16.out build/debug/chapter05/exercise16.expected

	@printf 'a\nc' | ./build/debug/chapter05/exercise16$(EXEEXT) -df | tr -d '\r' > build/debug/chapter05/exercise16.out
	@printf 'a\nc\n' > build/debug/chapter05/exercise16.expected
	@$(CMP) -s build/debug/chapter05/exercise16.out build/debug/chapter05/exercise16.expected

	@$(RM_RF) build/debug/chapter05/exercise16.out build/debug/chapter05/exercise16.expected
	@echo "chapter05/exercise16 tests passed"

test-ch05-ex17: debug
	@$(RM_RF) build/debug/chapter05/exercise17.out build/debug/chapter05/exercise17.expected

	@printf '%s\n' zebra apple banana | ./build/debug/chapter05/exercise17$(EXEEXT) | tr -d '\r' > build/debug/chapter05/exercise17.out
	@printf '%s\n' apple banana zebra > build/debug/chapter05/exercise17.expected
	@$(CMP) -s build/debug/chapter05/exercise17.out build/debug/chapter05/exercise17.expected

	@printf '%s\n' 2 10 -5 3 | ./build/debug/chapter05/exercise17$(EXEEXT) -nr | tr -d '\r' > build/debug/chapter05/exercise17.out
	@printf '%s\n' 10 3 2 -5 > build/debug/chapter05/exercise17.expected
	@$(CMP) -s build/debug/chapter05/exercise17.out build/debug/chapter05/exercise17.expected

	@printf '%s\n' b-2 'A 3' a_1 | ./build/debug/chapter05/exercise17$(EXEEXT) -rdf | tr -d '\r' > build/debug/chapter05/exercise17.out
	@printf '%s\n' b-2 a_1 'A 3' > build/debug/chapter05/exercise17.expected
	@$(CMP) -s build/debug/chapter05/exercise17.out build/debug/chapter05/exercise17.expected

	@printf '%s\n' 'banana    12' 'apple     20' 'banana     3' 'apple      2' | ./build/debug/chapter05/exercise17$(EXEEXT) -k 0:10:df -k 10::n | tr -d '\r' > build/debug/chapter05/exercise17.out
	@printf '%s\n' 'apple      2' 'apple     20' 'banana     3' 'banana    12' > build/debug/chapter05/exercise17.expected
	@$(CMP) -s build/debug/chapter05/exercise17.out build/debug/chapter05/exercise17.expected

	@printf '%s\n' 'banana    12' 'apple     20' 'banana     3' 'apple      2' | ./build/debug/chapter05/exercise17$(EXEEXT) -k 0:10:df -k 10::nr | tr -d '\r' > build/debug/chapter05/exercise17.out
	@printf '%s\n' 'apple     20' 'apple      2' 'banana    12' 'banana     3' > build/debug/chapter05/exercise17.expected
	@$(CMP) -s build/debug/chapter05/exercise17.out build/debug/chapter05/exercise17.expected

	@printf '%s\n' 'banana    12' 'apple     20' 'banana     3' 'apple      2' | ./build/debug/chapter05/exercise17$(EXEEXT) -k 0:10:dfr -k 10::n | tr -d '\r' > build/debug/chapter05/exercise17.out
	@printf '%s\n' 'banana     3' 'banana    12' 'apple      2' 'apple     20' > build/debug/chapter05/exercise17.expected
	@$(CMP) -s build/debug/chapter05/exercise17.out build/debug/chapter05/exercise17.expected

	@printf '%s\n' 'A!b  10' 'a?B  2' 'A_c  3' | ./build/debug/chapter05/exercise17$(EXEEXT) -k 0:5:df -k 5::n | tr -d '\r' > build/debug/chapter05/exercise17.out
	@printf '%s\n' 'a?B  2' 'A!b  10' 'A_c  3' > build/debug/chapter05/exercise17.expected
	@$(CMP) -s build/debug/chapter05/exercise17.out build/debug/chapter05/exercise17.expected

	@printf '%s\n' 'x 2xx' 'x 10a' | ./build/debug/chapter05/exercise17$(EXEEXT) -k 2:3:n | tr -d '\r' > build/debug/chapter05/exercise17.out
	@printf '%s\n' 'x 10a' 'x 2xx' > build/debug/chapter05/exercise17.expected
	@$(CMP) -s build/debug/chapter05/exercise17.out build/debug/chapter05/exercise17.expected

	@printf 'c\na' | ./build/debug/chapter05/exercise17$(EXEEXT) -k 0::df | tr -d '\r' > build/debug/chapter05/exercise17.out
	@printf 'a\nc\n' > build/debug/chapter05/exercise17.expected
	@$(CMP) -s build/debug/chapter05/exercise17.out build/debug/chapter05/exercise17.expected

	@if ./build/debug/chapter05/exercise17$(EXEEXT) -k 10:2:n </dev/null >/dev/null 2>&1; then exit 1; fi
	@if ./build/debug/chapter05/exercise17$(EXEEXT) -k 0::x </dev/null >/dev/null 2>&1; then exit 1; fi
	@if ./build/debug/chapter05/exercise17$(EXEEXT) -k 0:10:n -f </dev/null >/dev/null 2>&1; then exit 1; fi

	@$(RM_RF) build/debug/chapter05/exercise17.out build/debug/chapter05/exercise17.expected
	@echo "chapter05/exercise17 tests passed"
