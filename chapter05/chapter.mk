CHAPTER05_TESTS := \
	test-ch05-ex01 \
	test-ch05-ex02

TESTS += $(CHAPTER05_TESTS)
PHONY_TARGETS += $(CHAPTER05_TESTS)

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
