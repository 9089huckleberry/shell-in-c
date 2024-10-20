# Simple Shell Implementation in C

This project features a simple shell implementation in C that runs on both Windows and Unix-like systems. It allows users to execute commands from the command line and supports an interactive interface.

## Features

- Command execution using `system()` on Windows and `fork()`/`execvp()` on Unix-like systems.
- Supports built-in commands such as `exit`.
- Handles input and output redirection (basic functionality).
- Interactive command line interface.

## Files

- `shellforwindows.c`: Implementation of the shell for Windows using the `system()` function.
- `shellforunix.c`: Implementation of the shell for Unix-like systems using `fork()` and `execvp()`.

## Compilation

### For Windows

1. Open a terminal.
2. Compile the code using a C compiler like MinGW or Visual Studio:
gcc shellforwindows.c -o shell

### For Unix-like Systems

1. Open a terminal.
2. Compile the code using gcc:
gcc shellforunix.c -o shell

# Clone this repository
git clone https://github.com/9089huckleberry/shell-in-c.git