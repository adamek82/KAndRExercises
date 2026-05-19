CHAPTER02_TESTS := \
	test-ch02-ex01 \
	test-ch02-ex02 \
	test-ch02-ex03 \
	test-ch02-ex04 \
	test-ch02-ex05

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
