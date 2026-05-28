CHAPTER04_TESTS := \
	test-ch04-ex01

TESTS += $(CHAPTER04_TESTS)
PHONY_TARGETS += $(CHAPTER04_TESTS)

test-ch04-ex01: debug
	@$(RM_RF) build/debug/chapter04/exercise01.out

	@./build/debug/chapter04/exercise01$(EXEEXT) | tr -d '\r' > build/debug/chapter04/exercise01.out
	@grep -Fxq 'strrindex("hello world", "world") = 6' build/debug/chapter04/exercise01.out
	@grep -Fxq 'strrindex("banana", "ana") = 3' build/debug/chapter04/exercise01.out
	@grep -Fxq 'strrindex("aaaa", "aa") = 2' build/debug/chapter04/exercise01.out
	@grep -Fxq 'strrindex("abc", "x") = -1' build/debug/chapter04/exercise01.out
	@grep -Fxq 'strrindex("abc", "") = -1' build/debug/chapter04/exercise01.out
	@grep -Fxq 'strrindex checks: ok' build/debug/chapter04/exercise01.out

	@$(RM_RF) build/debug/chapter04/exercise01.out
	@echo "chapter04/exercise01 tests passed"
