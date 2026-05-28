CHAPTER03_TESTS := \
	test-ch03-ex01 \
	test-ch03-ex02 \
	test-ch03-ex03 \
	test-ch03-ex04 \
	test-ch03-ex05

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

test-ch03-ex02: debug
	@$(RM_RF) build/debug/chapter03/exercise02.out build/debug/chapter03/exercise02.expected

	@./build/debug/chapter03/exercise02$(EXEEXT) | tr -d '\r' > build/debug/chapter03/exercise02.out
	@printf 'escape 1: hello\134nworld\134t!\n' > build/debug/chapter03/exercise02.expected
	@printf 'escape 2: path\134\134file\n' >> build/debug/chapter03/exercise02.expected
	@printf 'escape 3: plain text\n' >> build/debug/chapter03/exercise02.expected
	@printf 'unescape 1, escaped again: hello\134nworld\134t!\n' >> build/debug/chapter03/exercise02.expected
	@printf 'unescape 2, escaped again: path\134\134file\n' >> build/debug/chapter03/exercise02.expected
	@printf 'unescape 3, escaped again: unknown\134\134qescape\n' >> build/debug/chapter03/exercise02.expected
	@printf 'unescape 4, escaped again: trailing\134\134\n' >> build/debug/chapter03/exercise02.expected
	@$(CMP) -s build/debug/chapter03/exercise02.out build/debug/chapter03/exercise02.expected

	@$(RM_RF) build/debug/chapter03/exercise02.out build/debug/chapter03/exercise02.expected
	@echo "chapter03/exercise02 tests passed"

test-ch03-ex03: debug
	@$(RM_RF) build/debug/chapter03/exercise03.out build/debug/chapter03/exercise03.expected

	@./build/debug/chapter03/exercise03$(EXEEXT) | tr -d '\r' > build/debug/chapter03/exercise03.out
	@printf '%s\n' 'expand 1: abcdefghijklmnopqrstuvwxyz' > build/debug/chapter03/exercise03.expected
	@printf '%s\n' 'expand 2: ABCDEFGHIJKLMNOPQRSTUVWXYZ' >> build/debug/chapter03/exercise03.expected
	@printf '%s\n' 'expand 3: 0123456789' >> build/debug/chapter03/exercise03.expected
	@printf '%s\n' 'expand 4: abc' >> build/debug/chapter03/exercise03.expected
	@printf '%s\n' 'expand 5: abcdefghijklmnopqrstuvwxyz0123456789' >> build/debug/chapter03/exercise03.expected
	@printf '%s\n' 'expand 6: -abcdefghijklmnopqrstuvwxyz' >> build/debug/chapter03/exercise03.expected
	@printf '%s\n' 'expand 7: abcdefghijklmnopqrstuvwxyz-' >> build/debug/chapter03/exercise03.expected
	@printf '%s\n' 'expand 8: a-Z' >> build/debug/chapter03/exercise03.expected
	@printf '%s\n' 'expand 9: z-a' >> build/debug/chapter03/exercise03.expected
	@printf '%s\n' 'expand 10: a-9' >> build/debug/chapter03/exercise03.expected
	@$(CMP) -s build/debug/chapter03/exercise03.out build/debug/chapter03/exercise03.expected

	@$(RM_RF) build/debug/chapter03/exercise03.out build/debug/chapter03/exercise03.expected
	@echo "chapter03/exercise03 tests passed"

test-ch03-ex04: debug
	@$(RM_RF) build/debug/chapter03/exercise04.out

	@./build/debug/chapter03/exercise04$(EXEEXT) | tr -d '\r' > build/debug/chapter03/exercise04.out
	@grep -Fxq 'itoa(0) = 0' build/debug/chapter03/exercise04.out
	@grep -Fxq 'itoa(12345) = 12345' build/debug/chapter03/exercise04.out
	@grep -Fxq 'itoa(-12345) = -12345' build/debug/chapter03/exercise04.out
	@grep -Fq 'itoa(INT_MAX) = ' build/debug/chapter03/exercise04.out
	@grep -Fq 'itoa(INT_MIN) = ' build/debug/chapter03/exercise04.out
	@grep -Fxq 'itoa checks: ok' build/debug/chapter03/exercise04.out

	@$(RM_RF) build/debug/chapter03/exercise04.out
	@echo "chapter03/exercise04 tests passed"

test-ch03-ex05: debug
	@$(RM_RF) build/debug/chapter03/exercise05.out

	@./build/debug/chapter03/exercise05$(EXEEXT) | tr -d '\r' > build/debug/chapter03/exercise05.out
	@grep -Fxq 'itob(0, 2) = 0' build/debug/chapter03/exercise05.out
	@grep -Fxq 'itob(31, 2) = 11111' build/debug/chapter03/exercise05.out
	@grep -Fxq 'itob(31, 16) = 1f' build/debug/chapter03/exercise05.out
	@grep -Fxq 'itob(-31, 16) = -1f' build/debug/chapter03/exercise05.out
	@grep -Fxq 'itob(255, 16) = ff' build/debug/chapter03/exercise05.out
	@grep -Fxq 'itob(35, 36) = z' build/debug/chapter03/exercise05.out
	@grep -Fq 'itob(INT_MIN, 10) = ' build/debug/chapter03/exercise05.out
	@grep -Fq 'itob(INT_MIN, 16) = ' build/debug/chapter03/exercise05.out
	@grep -Fxq 'itob checks: ok' build/debug/chapter03/exercise05.out

	@$(RM_RF) build/debug/chapter03/exercise05.out
	@echo "chapter03/exercise05 tests passed"
