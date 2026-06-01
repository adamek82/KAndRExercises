CHAPTER04_TESTS := \
	test-ch04-ex01 \
	test-ch04-ex02 \
	test-ch04-ex03 \
	test-ch04-ex04 \
	test-ch04-ex05

TESTS += $(CHAPTER04_TESTS)
PHONY_TARGETS += $(CHAPTER04_TESTS)

$(OUTDIR)/chapter04/exercise03$(EXEEXT): chapter04/exercise03/main.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) $< -o $@ -lm

$(OUTDIR)/chapter04/exercise04$(EXEEXT): chapter04/exercise04/main.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) $< -o $@ -lm

$(OUTDIR)/chapter04/exercise05$(EXEEXT): chapter04/exercise05/main.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) $< -o $@ -lm

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

test-ch04-ex03: debug
	@$(RM_RF) build/debug/chapter04/exercise03.out build/debug/chapter04/exercise03.expected

	@printf '1 2 +\n1 -1 +\n10 3 %%\n-10 3 %%\n5 2 /\n1 2 -\n' | ./build/debug/chapter04/exercise03$(EXEEXT) | tr -d '\r' > build/debug/chapter04/exercise03.out
	@printf '\t3\n' > build/debug/chapter04/exercise03.expected
	@printf '\t0\n' >> build/debug/chapter04/exercise03.expected
	@printf '\t1\n' >> build/debug/chapter04/exercise03.expected
	@printf '\t-1\n' >> build/debug/chapter04/exercise03.expected
	@printf '\t2.5\n' >> build/debug/chapter04/exercise03.expected
	@printf '\t-1\n' >> build/debug/chapter04/exercise03.expected
	@$(CMP) -s build/debug/chapter04/exercise03.out build/debug/chapter04/exercise03.expected

	@$(RM_RF) build/debug/chapter04/exercise03.out build/debug/chapter04/exercise03.expected
	@echo "chapter04/exercise03 tests passed"

test-ch04-ex04: debug
	@$(RM_RF) build/debug/chapter04/exercise04.out build/debug/chapter04/exercise04.expected

	@printf '2 3 + ?\n4 d *\n2 5 s -\n9 c 1 2 +\n10 3 %%\n1 -1 +\n' | ./build/debug/chapter04/exercise04$(EXEEXT) | tr -d '\r' > build/debug/chapter04/exercise04.out
	@printf '\t5\n' > build/debug/chapter04/exercise04.expected
	@printf '\t5\n' >> build/debug/chapter04/exercise04.expected
	@printf '\t16\n' >> build/debug/chapter04/exercise04.expected
	@printf '\t3\n' >> build/debug/chapter04/exercise04.expected
	@printf '\t3\n' >> build/debug/chapter04/exercise04.expected
	@printf '\t1\n' >> build/debug/chapter04/exercise04.expected
	@printf '\t0\n' >> build/debug/chapter04/exercise04.expected
	@$(CMP) -s build/debug/chapter04/exercise04.out build/debug/chapter04/exercise04.expected

	@$(RM_RF) build/debug/chapter04/exercise04.out build/debug/chapter04/exercise04.expected
	@echo "chapter04/exercise04 tests passed"

test-ch04-ex05: debug
	@$(RM_RF) build/debug/chapter04/exercise05.out build/debug/chapter04/exercise05.expected

	@printf '3.14159265 2 / sin\n0 cos\n2 exp\n2 3 pow\n2 3 pow 4 2 pow +\n5 d *\n2 5 s -\n' | ./build/debug/chapter04/exercise05$(EXEEXT) | tr -d '\r' > build/debug/chapter04/exercise05.out
	@printf '\t1\n' > build/debug/chapter04/exercise05.expected
	@printf '\t1\n' >> build/debug/chapter04/exercise05.expected
	@printf '\t7.3890561\n' >> build/debug/chapter04/exercise05.expected
	@printf '\t8\n' >> build/debug/chapter04/exercise05.expected
	@printf '\t24\n' >> build/debug/chapter04/exercise05.expected
	@printf '\t25\n' >> build/debug/chapter04/exercise05.expected
	@printf '\t3\n' >> build/debug/chapter04/exercise05.expected
	@$(CMP) -s build/debug/chapter04/exercise05.out build/debug/chapter04/exercise05.expected

	@$(RM_RF) build/debug/chapter04/exercise05.out build/debug/chapter04/exercise05.expected
	@echo "chapter04/exercise05 tests passed"
