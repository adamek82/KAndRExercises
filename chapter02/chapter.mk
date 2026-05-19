CHAPTER02_TESTS := \
	test-ch02-ex01 \
	test-ch02-ex02

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
