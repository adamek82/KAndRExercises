CHAPTER02_TESTS := \
	test-ch02-ex01

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
