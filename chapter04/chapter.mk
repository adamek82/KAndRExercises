CHAPTER04_TESTS := \
	test-ch04-ex01 \
	test-ch04-ex02

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

test-ch04-ex02: debug
	@$(RM_RF) build/debug/chapter04/exercise02.out

	@./build/debug/chapter04/exercise02$(EXEEXT) | tr -d '\r' > build/debug/chapter04/exercise02.out
	@grep -Fxq 'atof_kr("123") = 123' build/debug/chapter04/exercise02.out
	@grep -Fxq 'atof_kr("123.45") = 123.45' build/debug/chapter04/exercise02.out
	@grep -Fxq 'atof_kr(".45") = 0.45' build/debug/chapter04/exercise02.out
	@grep -Fxq 'atof_kr("123.") = 123' build/debug/chapter04/exercise02.out
	@grep -Fxq 'atof_kr("-123.45") = -123.45' build/debug/chapter04/exercise02.out
	@grep -Fxq 'atof_kr("123.45e-6") = 0.00012345' build/debug/chapter04/exercise02.out
	@grep -Fxq 'atof_kr("123.45E+6") = 123450000' build/debug/chapter04/exercise02.out
	@grep -Fxq 'atof_kr("1e3") = 1000' build/debug/chapter04/exercise02.out
	@grep -Fxq 'atof_kr("1e-3") = 0.001' build/debug/chapter04/exercise02.out
	@grep -Fxq 'atof checks: ok' build/debug/chapter04/exercise02.out

	@$(RM_RF) build/debug/chapter04/exercise02.out
	@echo "chapter04/exercise02 tests passed"
