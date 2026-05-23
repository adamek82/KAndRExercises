CHAPTER02_TESTS := \
	test-ch02-ex01 \
	test-ch02-ex02 \
	test-ch02-ex03 \
	test-ch02-ex04 \
	test-ch02-ex05 \
	test-ch02-ex06 \
	test-ch02-ex07 \
	test-ch02-ex08 \
	test-ch02-ex09 \
	test-ch02-ex10

TESTS += $(CHAPTER02_TESTS)
PHONY_TARGETS += $(CHAPTER02_TESTS)

test-ch02-ex01: debug
	@$(RM_RF) build/debug/chapter02/exercise01.out

	@./build/debug/chapter02/exercise01$(EXEEXT) | tr -d '\r' > build/debug/chapter02/exercise01.out
	@grep -Fxq 'Integer range checks: ok' build/debug/chapter02/exercise01.out
	@grep -Fxq 'Floating-point ranges from <float.h>:' build/debug/chapter02/exercise01.out
	@grep -Fq 'float max:' build/debug/chapter02/exercise01.out
	@grep -Fq 'double max:' build/debug/chapter02/exercise01.out
	@grep -Fq 'long double max:' build/debug/chapter02/exercise01.out

	@$(RM_RF) build/debug/chapter02/exercise01.out
	@echo "chapter02/exercise01 tests passed"

test-ch02-ex02: debug
	@$(RM_RF) build/debug/chapter02/exercise02.out build/debug/chapter02/exercise02.expected

	@printf '%s' '' | ./build/debug/chapter02/exercise02$(EXEEXT) | tr -d '\r' > build/debug/chapter02/exercise02.out
	@printf '%s' '' > build/debug/chapter02/exercise02.expected
	@$(CMP) -s build/debug/chapter02/exercise02.out build/debug/chapter02/exercise02.expected

	@printf 'abc\n' | ./build/debug/chapter02/exercise02$(EXEEXT) | tr -d '\r' > build/debug/chapter02/exercise02.out
	@printf 'abc\n' > build/debug/chapter02/exercise02.expected
	@$(CMP) -s build/debug/chapter02/exercise02.out build/debug/chapter02/exercise02.expected

	@printf '%s' 'abc' | ./build/debug/chapter02/exercise02$(EXEEXT) | tr -d '\r' > build/debug/chapter02/exercise02.out
	@printf '%s' 'abc' > build/debug/chapter02/exercise02.expected
	@$(CMP) -s build/debug/chapter02/exercise02.out build/debug/chapter02/exercise02.expected

	@printf '\n' | ./build/debug/chapter02/exercise02$(EXEEXT) | tr -d '\r' > build/debug/chapter02/exercise02.out
	@printf '\n' > build/debug/chapter02/exercise02.expected
	@$(CMP) -s build/debug/chapter02/exercise02.out build/debug/chapter02/exercise02.expected

	@printf '123456789abcdefgh\n' | ./build/debug/chapter02/exercise02$(EXEEXT) | tr -d '\r' > build/debug/chapter02/exercise02.out
	@printf '123456789abcdefgh\n' > build/debug/chapter02/exercise02.expected
	@$(CMP) -s build/debug/chapter02/exercise02.out build/debug/chapter02/exercise02.expected

	@$(RM_RF) build/debug/chapter02/exercise02.out build/debug/chapter02/exercise02.expected
	@echo "chapter02/exercise02 tests passed"

test-ch02-ex03: debug
	@$(RM_RF) build/debug/chapter02/exercise03.out build/debug/chapter02/exercise03.expected

	@./build/debug/chapter02/exercise03$(EXEEXT) | tr -d '\r' > build/debug/chapter02/exercise03.out
	@printf '%s\n' '0 -> 0' > build/debug/chapter02/exercise03.expected
	@printf '%s\n' '1 -> 1' >> build/debug/chapter02/exercise03.expected
	@printf '%s\n' '9 -> 9' >> build/debug/chapter02/exercise03.expected
	@printf '%s\n' 'a -> 10' >> build/debug/chapter02/exercise03.expected
	@printf '%s\n' 'f -> 15' >> build/debug/chapter02/exercise03.expected
	@printf '%s\n' 'A -> 10' >> build/debug/chapter02/exercise03.expected
	@printf '%s\n' 'F -> 15' >> build/debug/chapter02/exercise03.expected
	@printf '%s\n' '10 -> 16' >> build/debug/chapter02/exercise03.expected
	@printf '%s\n' '0x10 -> 16' >> build/debug/chapter02/exercise03.expected
	@printf '%s\n' '0X10 -> 16' >> build/debug/chapter02/exercise03.expected
	@printf '%s\n' '7f -> 127' >> build/debug/chapter02/exercise03.expected
	@printf '%s\n' '0xff -> 255' >> build/debug/chapter02/exercise03.expected
	@printf '%s\n' '0XABC -> 2748' >> build/debug/chapter02/exercise03.expected
	@printf '%s\n' '123g -> 291' >> build/debug/chapter02/exercise03.expected
	@$(CMP) -s build/debug/chapter02/exercise03.out build/debug/chapter02/exercise03.expected

	@$(RM_RF) build/debug/chapter02/exercise03.out build/debug/chapter02/exercise03.expected
	@echo "chapter02/exercise03 tests passed"

test-ch02-ex04: debug
	@$(RM_RF) build/debug/chapter02/exercise04.out build/debug/chapter02/exercise04.expected

	@./build/debug/chapter02/exercise04$(EXEEXT) | tr -d '\r' > build/debug/chapter02/exercise04.out
	@printf '%s\n' 'hello, world / lo -> he, wrd' > build/debug/chapter02/exercise04.expected
	@printf '%s\n' 'The C Programming Language / vowels -> Th C Prgrmmng Lngg' >> build/debug/chapter02/exercise04.expected
	@printf '%s\n' 'abc / empty -> abc' >> build/debug/chapter02/exercise04.expected
	@printf '%s\n' 'empty / abc -> ' >> build/debug/chapter02/exercise04.expected
	@printf '%s\n' 'mississippi / is -> mpp' >> build/debug/chapter02/exercise04.expected
	@$(CMP) -s build/debug/chapter02/exercise04.out build/debug/chapter02/exercise04.expected

	@$(RM_RF) build/debug/chapter02/exercise04.out build/debug/chapter02/exercise04.expected
	@echo "chapter02/exercise04 tests passed"

test-ch02-ex05: debug
	@$(RM_RF) build/debug/chapter02/exercise05.out build/debug/chapter02/exercise05.expected

	@./build/debug/chapter02/exercise05$(EXEEXT) | tr -d '\r' > build/debug/chapter02/exercise05.out
	@printf '%s\n' 'hello, world / od -> 4' > build/debug/chapter02/exercise05.expected
	@printf '%s\n' 'hello, world / xyz -> -1' >> build/debug/chapter02/exercise05.expected
	@printf '%s\n' 'abc / c -> 2' >> build/debug/chapter02/exercise05.expected
	@printf '%s\n' 'abc / a -> 0' >> build/debug/chapter02/exercise05.expected
	@printf '%s\n' 'abc / empty -> -1' >> build/debug/chapter02/exercise05.expected
	@printf '%s\n' 'empty / abc -> -1' >> build/debug/chapter02/exercise05.expected
	@printf '%s\n' 'mississippi / ps -> 2' >> build/debug/chapter02/exercise05.expected
	@$(CMP) -s build/debug/chapter02/exercise05.out build/debug/chapter02/exercise05.expected

	@$(RM_RF) build/debug/chapter02/exercise05.out build/debug/chapter02/exercise05.expected
	@echo "chapter02/exercise05 tests passed"

test-ch02-ex06: debug
	@$(RM_RF) build/debug/chapter02/exercise06.out build/debug/chapter02/exercise06.expected

	@./build/debug/chapter02/exercise06$(EXEEXT) | tr -d '\r' > build/debug/chapter02/exercise06.out
	@printf '%s\n' 'setbits(0xffff, 7, 4, 0x0) = 0xff0f' > build/debug/chapter02/exercise06.expected
	@printf '%s\n' 'setbits(0x0000, 7, 4, 0xf) = 0x00f0' >> build/debug/chapter02/exercise06.expected
	@printf '%s\n' 'setbits(0xaaaa, 7, 4, 0x5) = 0xaa5a' >> build/debug/chapter02/exercise06.expected
	@printf '%s\n' 'setbits(0x1234, 11, 4, 0xf) = 0x1f34' >> build/debug/chapter02/exercise06.expected
	@printf '%s\n' 'setbits(0x1234, 3, 4, 0x0) = 0x1230' >> build/debug/chapter02/exercise06.expected
	@$(CMP) -s build/debug/chapter02/exercise06.out build/debug/chapter02/exercise06.expected

	@$(RM_RF) build/debug/chapter02/exercise06.out build/debug/chapter02/exercise06.expected
	@echo "chapter02/exercise06 tests passed"

test-ch02-ex07: debug
	@$(RM_RF) build/debug/chapter02/exercise07.out build/debug/chapter02/exercise07.expected

	@./build/debug/chapter02/exercise07$(EXEEXT) | tr -d '\r' > build/debug/chapter02/exercise07.out
	@printf '%s\n' 'invert(0x0000, 7, 4) = 0x00f0' > build/debug/chapter02/exercise07.expected
	@printf '%s\n' 'invert(0xffff, 7, 4) = 0xff0f' >> build/debug/chapter02/exercise07.expected
	@printf '%s\n' 'invert(0xaaaa, 7, 4) = 0xaa5a' >> build/debug/chapter02/exercise07.expected
	@printf '%s\n' 'invert(0x1234, 11, 4) = 0x1d34' >> build/debug/chapter02/exercise07.expected
	@printf '%s\n' 'invert(0x1234, 3, 4) = 0x123b' >> build/debug/chapter02/exercise07.expected
	@$(CMP) -s build/debug/chapter02/exercise07.out build/debug/chapter02/exercise07.expected

	@$(RM_RF) build/debug/chapter02/exercise07.out build/debug/chapter02/exercise07.expected
	@echo "chapter02/exercise07 tests passed"

test-ch02-ex08: debug
	@$(RM_RF) build/debug/chapter02/exercise08.out

	@./build/debug/chapter02/exercise08$(EXEEXT) | tr -d '\r' > build/debug/chapter02/exercise08.out
	@grep -Fxq 'rightrot checks: ok' build/debug/chapter02/exercise08.out
	@grep -Fq 'rightrot(0x12345678, 4)' build/debug/chapter02/exercise08.out
	@grep -Fq 'rightrot(0x12345678, 32)' build/debug/chapter02/exercise08.out

	@$(RM_RF) build/debug/chapter02/exercise08.out
	@echo "chapter02/exercise08 tests passed"

test-ch02-ex09: debug
	@$(RM_RF) build/debug/chapter02/exercise09.out build/debug/chapter02/exercise09.expected

	@./build/debug/chapter02/exercise09$(EXEEXT) | tr -d '\r' > build/debug/chapter02/exercise09.out
	@printf '%s\n' 'bitcount(0x00000000) = 0' > build/debug/chapter02/exercise09.expected
	@printf '%s\n' 'bitcount(0x00000001) = 1' >> build/debug/chapter02/exercise09.expected
	@printf '%s\n' 'bitcount(0x00000009) = 2' >> build/debug/chapter02/exercise09.expected
	@printf '%s\n' 'bitcount(0x0000000f) = 4' >> build/debug/chapter02/exercise09.expected
	@printf '%s\n' 'bitcount(0xffffffff) = 32' >> build/debug/chapter02/exercise09.expected
	@printf '%s\n' 'bitcount(0x12345678) = 13' >> build/debug/chapter02/exercise09.expected
	@printf '%s\n' 'bitcount checks: ok' >> build/debug/chapter02/exercise09.expected
	@$(CMP) -s build/debug/chapter02/exercise09.out build/debug/chapter02/exercise09.expected

	@$(RM_RF) build/debug/chapter02/exercise09.out build/debug/chapter02/exercise09.expected
	@echo "chapter02/exercise09 tests passed"

test-ch02-ex10: debug
	@$(RM_RF) build/debug/chapter02/exercise10.out build/debug/chapter02/exercise10.expected

	@./build/debug/chapter02/exercise10$(EXEEXT) | tr -d '\r' > build/debug/chapter02/exercise10.out
	@printf '%s\n' 'A -> a' > build/debug/chapter02/exercise10.expected
	@printf '%s\n' 'Z -> z' >> build/debug/chapter02/exercise10.expected
	@printf '%s\n' 'M -> m' >> build/debug/chapter02/exercise10.expected
	@printf '%s\n' 'a -> a' >> build/debug/chapter02/exercise10.expected
	@printf '%s\n' 'z -> z' >> build/debug/chapter02/exercise10.expected
	@printf '%s\n' '0 -> 0' >> build/debug/chapter02/exercise10.expected
	@printf '%s\n' '? -> ?' >> build/debug/chapter02/exercise10.expected
	@$(CMP) -s build/debug/chapter02/exercise10.out build/debug/chapter02/exercise10.expected

	@$(RM_RF) build/debug/chapter02/exercise10.out build/debug/chapter02/exercise10.expected
	@echo "chapter02/exercise10 tests passed"
