CHAPTER05_TESTS := \
	test-ch05-ex01

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
