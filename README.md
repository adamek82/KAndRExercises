# K&R Exercises

Small C programs based on exercises from *The C Programming Language* by Brian W. Kernighan and Dennis M. Ritchie.

The repository is intentionally simple: each exercise is kept as a standalone program with its own `main.c`, while a top-level `Makefile` provides common build, run, and test commands.

## Goals

This project is mainly educational. The priorities are:

- keep each exercise independent and easy to inspect;
- make the programs build on both Linux and Windows;
- avoid IDE-specific project formats as much as possible;
- keep the build system simple enough to understand;
- provide basic automated tests where it makes sense.

## Repository layout

```text
.
├── Makefile
├── chapter01/
│   ├── exercise01/
│   │   └── main.c
│   ├── exercise02/
│   │   └── main.c
│   ├── ...
│   └── exercise13/
│       ├── horizontal/
│       │   └── main.c
│       └── vertical/
│           └── main.c
└── .vscode/
    └── tasks.json
```

Each exercise directory contains a standalone program. Some exercises may have multiple variants, for example:

```text
chapter01/exercise13/horizontal
chapter01/exercise13/vertical
```

Build output is written under:

```text
build/debug/
build/release/
```

## Requirements

### Linux / Ubuntu 24.04

Ubuntu 24.04 uses GCC 13 as the default `gcc`. GCC 13 accepts the older provisional C23 option name `-std=c2x`, but not the final `-std=c23` name.

This project uses:

```text
-std=c23
```

so on Ubuntu 24.04 install GCC 14:

```bash
sudo apt update
sudo apt install gcc-14 make
```

Then build with:

```bash
make CC=gcc-14
```

or export the compiler for the current shell session:

```bash
export CC=gcc-14
make
```

### Windows / MSYS2 UCRT64

Install MSYS2 and use the UCRT64 environment.

Typical packages:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-make
```

The make executable is usually:

```text
C:/msys64/ucrt64/bin/mingw32-make.exe
```

The compiler is usually:

```text
C:/msys64/ucrt64/bin/gcc.exe
```

## Building

Build the default debug configuration:

```bash
make
```

or explicitly:

```bash
make debug
```

Build the release configuration:

```bash
make release
```

The debug build uses:

```text
-g -O0
```

The release build uses:

```text
-O2 -DNDEBUG
```

## Listing exercises

To list all detected exercises:

```bash
make list
```

Example output:

```text
chapter01/exercise01
chapter01/exercise02
chapter01/exercise03
...
chapter01/exercise13/horizontal
chapter01/exercise13/vertical
```

## Running an exercise

Run a selected exercise by passing its path through `EX`:

```bash
make run EX=chapter01/exercise09
```

For nested variants:

```bash
make run EX=chapter01/exercise13/vertical
```

On Ubuntu 24.04 with GCC 14:

```bash
make CC=gcc-14 run EX=chapter01/exercise09
```

## Testing

Run tests for a selected exercise:

```bash
make test EX=chapter01/exercise09
```

Run all available tests:

```bash
make test-all
```

On Ubuntu 24.04 with GCC 14:

```bash
make CC=gcc-14 test-all
```

Not every exercise necessarily has automated tests. Early K&R exercises often print simple output or process standard input, so tests are added where they are useful and reasonably simple.

## Cleaning build output

```bash
make clean
```

This removes the `build/` directory.

## VS Code

The repository contains cross-platform VS Code tasks in:

```text
.vscode/tasks.json
```

These tasks use platform-specific commands:

- on Windows: MSYS2 `mingw32-make.exe`;
- on Linux: system `make`, with `CC=gcc-14` where needed.

Available tasks include:

- `Build Debug`
- `Build Release`
- `Run Exercise`
- `Test Exercise`
- `Test All`
- `Clean`

### C/C++ extension configuration

The VS Code C/C++ extension uses machine-specific paths such as compiler locations and system include directories. For that reason, the real file below should be treated as local configuration:

```text
.vscode/c_cpp_properties.json
```

It is intentionally not suitable as a single universal file for both Windows and Linux, because paths such as these are system-specific:

```text
C:/msys64/ucrt64/bin/gcc.exe
/usr/bin/gcc-14
```

Recommended approach:

```text
.vscode/c_cpp_properties.json              # local, ignored by Git
.vscode/c_cpp_properties.windows.example.json
.vscode/c_cpp_properties.linux.example.json
```

Copy the relevant example file to:

```text
.vscode/c_cpp_properties.json
```

For example, on Linux:

```bash
cp .vscode/c_cpp_properties.linux.example.json .vscode/c_cpp_properties.json
```

On Windows, copy the Windows example instead.

## Suggested local VS Code C/C++ configurations

### Ubuntu 24.04 / GCC 14

Use `/usr/bin/gcc-14` as the compiler path and `linux-gcc-x64` as the IntelliSense mode.

### Windows / MSYS2 UCRT64

Use `C:/msys64/ucrt64/bin/gcc.exe` as the compiler path and `windows-gcc-x64` as the IntelliSense mode.

## Notes about C23

The project currently builds with:

```text
-std=c23
```

This requires a compiler version that recognizes the final C23 option name. GCC 14 supports this. Older GCC versions may require `-std=c2x` instead, but the project keeps `-std=c23` to match the final standard name.

## Typical workflow

On Ubuntu 24.04:

```bash
git clone https://github.com/adamek82/KAndRExercises.git
cd KAndRExercises
sudo apt install gcc-14 make
make CC=gcc-14
make CC=gcc-14 test-all
```

On Windows with MSYS2 UCRT64:

```bash
git clone https://github.com/adamek82/KAndRExercises.git
cd KAndRExercises
C:/msys64/ucrt64/bin/mingw32-make.exe
C:/msys64/ucrt64/bin/mingw32-make.exe test-all
```

## License

This repository is licensed under the MIT License.

You are free to use, copy, modify, and distribute the code, including for
commercial purposes, as long as the original copyright notice and license text
are preserved.

See [LICENSE](LICENSE) for details.
