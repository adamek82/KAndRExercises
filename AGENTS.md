# KAndRExercises agent guide

## Educational scope comes first

Implement from the supplied K&R Second Edition exercise statement, knowledge of
K&R and C, and repository evidence; do not require a supplied solution or algorithm.
Identify requirements, interfaces, constraints, chapter, and the conceptual point
within it. Exercise numbers are not section numbers; do not invent exact boundaries.

For each exercise, distinguish:

1. Concepts taught in previous chapters.
2. Concepts introduced earlier in the current chapter.
3. The new technique or concept this exercise practices.
4. Later concepts normally unavailable at this point.

Use the first three; an explicit requirement or permission in the statement wins.

- Reassess scope per exercise, not merely per chapter. Existing solutions establish
  style and organization, not correctness or permission to use later concepts.
- Use arrays/indexing before explicit pointer techniques are taught. Array
  parameters such as `char s[]` do not justify premature pointer arithmetic.
  Use pointers meaningfully when the exercise introduces or requires them.
- Avoid structures, heap allocation, function pointers, advanced library facilities,
  or modern features before their introduction unless the statement permits them.
  K&R's fixed-buffer `alloc` is distinct from heap allocation with `malloc`.
  Newly introduced concepts are appropriate even without earlier repository examples.
- Implement the essential algorithm; a library shortcut must not do the work being
  practiced. Supporting calls must fit the educational scope; reference checks
  must remain separate from the solution.
- C23 is the compiler standard, not the syllabus. Use simple book-appropriate C
  with explicit types/prototypes; do not copy obsolete syntax incompatible with C23.
- Resolve ordinary ambiguities from book context and repository conventions.
  State material assumptions; ask only when missing information changes the solution.

## Layout and implementation

- Use `chapterNN/exerciseNN/main.c`. Independent variants use one descriptive
  lowercase subdirectory each, e.g. `chapter01/exercise13/horizontal/main.c`.
  Keep each independently understandable; comparisons may share one program when
  the exercise calls for that. Do not introduce a shared exercise framework.
- Usually keep one translation unit: needed standard headers, symbolic constants,
  helper prototypes, `main`, then helper definitions. Use `int main(void)` or
  `int main(int argc, char *argv[])` when arguments belong to the exercise.
- Indent C with four spaces; function opening braces go on their own line,
  control-flow braces on the same line, with `} else {`. Use braces for bodies,
  operator/comma spacing, and blank lines between functions/logical steps.
  Prefer LF for new files; preserve existing formatting. Make recipes need tabs.
- Use lowercase descriptive names with underscores, traditional book names where
  useful, and uppercase macros. Declare locals near the start of their block;
  initialized declarations and later assignments are both established patterns.
  Avoid standard-function collisions with names such as `kr_strncpy` when needed.
- Prefer clear steps and small helpers over shortest code, abstractions, or excessive
  defensive programming. Respect specified interfaces and caller-owned capacity
  contracts; do not redesign an exercise into a production library.
- Handle relevant boundaries: `int` character input for `EOF`, string terminators,
  empty input, missing final newline, storage limits, and meaningful invalid input.
  Avoid undefined behavior such as signed overflow, invalid shifts, or out-of-array pointer
  formation except one-past. Pass `EOF` or unsigned-character values to `<ctype.h>`.
- Use concise block comments for identity, assumptions, contracts, and non-obvious
  reasoning. Put the pedagogical explanation in the final response.

## Workflow and build integration

Inspect related solutions and chapter tests before coding. Limit changes to the
requested exercise, its variants, and necessary build/test rules; preserve unrelated
working-tree changes. Design portable code/tests for Windows 11/MSYS2 UCRT64 and
Linux/Ubuntu under WSL unless the exercise requires platform behavior; document it.

- Do not commit changes unless explicitly requested.
- Root `Makefile` discovers `chapter*/exercise*/main.c` and
  `chapter*/exercise*/*/main.c`; ordinary programs and one-level variants need no
  executable registration. Additional sources or deeper layouts need custom rules.
- All `chapter*/chapter.mk` files are included. Put special compilation recipes
  there, reusing `$(OUTDIR)`, `$(EXEEXT)`, `$(CC)`, `$(CFLAGS)`, and
  `$(MKDIR_P)`. Follow existing benchmark macro overrides or math-linking `-lm`
  rules when needed. Declare extra source/header prerequisites explicitly.
- Keep `-std=c23 -Wall -Wextra -pedantic`. Debug adds `-g -O0`; release adds
  `-O2 -DNDEBUG`. Linux defaults to `gcc-14`; Windows uses UCRT64 `gcc` and
  needs MSYS2's POSIX shell/utilities as well as GNU Make. Use command-line `CC=...`
  overrides; the Makefile overrides ordinary environment-only compiler settings.
- Output is `build/debug/<exercise-path>` or `build/release/<exercise-path>`,
  with `.exe` on Windows. Keep all generated/test artifacts under ignored `build/`.
  The default recipe compiles only `main.c`; changed flags do not trigger a rebuild.
- `make`/`make debug` build all debug programs; `make release` builds release.
  `make BUILD=release build` selects release; plain `make BUILD=release` still
  goes through `all: debug`. Request an output path to build one program.
  `make run EX=<path>` builds all debug programs and runs the selected one;
  invoke its executable directly for program arguments or release runs.

From the repository root, common commands are:

```sh
make debug
make test EX=chapter01/exercise13/horizontal
make test-all
make release
```

On Linux use GCC 14; in PowerShell replace `make` with
`& C:/msys64/ucrt64/bin/mingw32-make.exe` (see README.md for setup).
Use `make list` to check discovery and `make -B <output-path>` for a fresh build;
`make clean` removes the entire build tree.

## Portable tests

- Register `test-chNN-exNN[-variant]` in the chapter's `CHAPTERNN_TESTS`, appended
  to both `TESTS` and `PHONY_TARGETS`. Follow `: debug` dependencies and
  `$(EXEEXT)` paths. `make test EX=<path>` translates the path to that target;
  missing tests have no fallback. `test-all` runs only registered targets.
- Add a focused, registered test target for every new exercise whenever its
  behavior can be verified deterministically. Automatic executable discovery
  does not imply automatic test coverage. Ensure new tests are included in
  both `make test EX=<path>` and `make test-all`.
- Existing tests build/run debug executables even with `BUILD=release`.
  Check release separately; do not copy weak assertions or platform assumptions.
- Use portable POSIX-shell recipes, not Bash-only syntax or `pipefail`.
  Use deterministic `printf`, not `echo -e` or implementation-dependent escapes.
  For literal data use fixed formats such as `printf '%s' "$value"`.
- Distinguish Make expansion, shell quoting, `printf` format interpretation, and
  the program's own parsing. Make recipes need `$$` to pass `$` to the shell.
  Keep literal backslashes/quotes and textual C escapes distinct from actual bytes.
  Quote special shell arguments such as `'*'`; preserve the Chapter 05/exercise10
  `MSYS2_ARG_CONV_EXCL=/` pattern for literal `/` arguments to Windows programs.
- For difficult backslashes, quotes, tabs, CR, or LF, prefer verified octal bytes
  over layered escaping (`\047` is a single quote; `\042` a double quote).
  This POSIX-shell command emits literal `\t`, TAB, CR, LF (decimal `92 116 9 13 10`):
  `printf '\134\164\011\015\012' | od -An -t u1`.
  Inspect actual input/output bytes when uncertain; use existing tools such as
  `od` and `cmp` rather than adding dependencies for hexadecimal formatting.
- Normalize only known platform text-line-ending differences when irrelevant.
  Target CR in CRLF line endings; do not indiscriminately delete every CR with
  `tr -d '\r'`, change meaningful data, or normalize away defects. Byte-sensitive
  tests need explicit expected bytes and `$(CMP) -s`; account for platform text-mode
  translation only when the output contract permits it. Not all text must be byte-identical.
- Account for input text-mode translation, not just output differences.
  On Windows, CRLF may become LF and Ctrl-Z may be interpreted as EOF.
  Use ordinary text I/O unless the exercise explicitly requires raw bytes;
  do not assume byte-sensitive input behaves identically across platforms.
- Check complete expected output when practical; selected matching fragments alone
  may miss failures. Verify exit status independently of output comparison.
  Feed prepared input by redirection, capture output and status, then normalize or
  compare separately. For expected failures assert the intended status. A pipeline's
  final command can hide program failure; keep dependent checks in one shell recipe.
- Keep cases small, readable, deterministic, and proportionate: normal cases and
  meaningful EOF, whitespace, capacity, numeric, invalid-input, and variant boundaries.
  Avoid fixed integer-width, timing, locale, or platform assumptions unless required.
  Simple built-in `check_*` routines are established; no elaborate test framework.

## Final verification and reporting

Run relevant builds/tests on Windows/MSYS2 and Linux/WSL when both are accessible.
Use WSL from Windows when available. Test the same source revision and working-tree
changes, including untracked files; matching commit IDs alone are insufficient.
Use a shared checkout or compare actual source/test contents; rebuild stale outputs.
Run suites sequentially when sharing build artifacts.
If a test differs across platforms, inspect quoting, actual bytes, exit status,
and text-mode line endings before changing expectations or the algorithm.

If only one environment is accessible, still design portable code/tests and
statically check the other platform's shell constructs, escapes, flags, and assumptions.
Name the environment actually tested and the unavailable checks; never claim
cross-platform success or a passing test without executing it successfully.
Run `test-all` for shared build/test changes or appropriate broader regressions.
Inspect warnings/failures and the final diff; leave unrelated files untouched.

Briefly report implementation/path, previously taught concepts used, the new
concept practiced and why the solution fits its point in K&R, actual build/test
commands/results by environment, and material assumptions or verification limits.
