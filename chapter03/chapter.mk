CHAPTER03_TESTS := \
	test-ch03-ex01

TESTS += $(CHAPTER03_TESTS)
PHONY_TARGETS += $(CHAPTER03_TESTS)

ifeq ($(BUILD),release)
CH03_EX01_BENCH_FLAGS := -DBENCH_SIZE=1048576 -DBENCH_REPEAT=5000000
else
CH03_EX01_BENCH_FLAGS := -DBENCH_SIZE=32768 -DBENCH_REPEAT=50000
endif

$(OUTDIR)/chapter03/exercise01$(EXEEXT): chapter03/exercise01/main.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) $(CH03_EX01_BENCH_FLAGS) $< -o $@

test-ch03-ex01: debug
	@$(RM_RF) build/debug/chapter03/exercise01.out

	@./build/debug/chapter03/exercise01$(EXEEXT) | tr -d '\r' > build/debug/chapter03/exercise01.out
	@grep -Fxq 'correctness checks: ok' build/debug/chapter03/exercise01.out
	@grep -Fq 'original found clocks:' build/debug/chapter03/exercise01.out
	@grep -Fq 'one-test found clocks:' build/debug/chapter03/exercise01.out
	@grep -Fq 'original missing clocks:' build/debug/chapter03/exercise01.out
	@grep -Fq 'one-test missing clocks:' build/debug/chapter03/exercise01.out

	@$(RM_RF) build/debug/chapter03/exercise01.out
	@echo "chapter03/exercise01 tests passed"
