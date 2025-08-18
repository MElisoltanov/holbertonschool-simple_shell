# Holberton Simple shell
## Description
Simple Shell `hsh` is a minimalist UNIX command-line interpreter built at Holberton School to solidify core C concepts through pair programming. It supports interactive and non-interactive modes, PATH resolution and execution of external commands, basic built-ins (exit, env), signal handling (SIGINT), and error/status propagation via fork, execve, and waitpid. The project emphasizes clean memory management, modular design, and adherence to Holberton’s Betty style.

## <span id="files-description">File description</span>

| **FILE**            | **DESCRIPTION** |
|:-------------------:|-----------------|
| `shell.h`           | Project header: macros (`PROMPT`, `TOKEN_DELIMS`), `extern environ`, types, and all function prototypes. |
| `main.c`            | Entry point: installs signal handlers and starts the shell loop. |
| `loop.c`            | Main REPL loop: show prompt (interactive), read line, tokenize, execute, and clean up. |
| `input.c`           | Prompt display, interactive-mode detection, and safe line reading with `getline()`. |
| `parse.c`           | Tokenization utilities (`tokenize`, `count_tokens`) and `free_tokens` (shallow free of the argv array). |
| `execute.c`         | Command dispatcher for built-ins and external programs; process creation (`fork`/`execve`) and status handling. |
| `path.c`            | PATH resolution helpers: `resolve_path`, `is_executable`, and `join_path`. |
| `signals.c`         | Signal setup (`SIGINT`) and handler that keeps the shell running. |
| `builtin.c`         | Built-in detection (`is_builtin`) and dispatch (`run_builtin`). |
| `builtin_env.c`     | Implementation of `env` (prints the current environment). |
| `builtin_exit.c`    | Implementation of `exit` (sets exit status and signals loop termination). |
| `errors.c`          | Error helpers: formatted shell errors and `perror` wrapper. |
| `memory.c`          | Safe memory helpers (`xmalloc`, `xrealloc`) and a generic NULL-terminated array freer. |
| `README.md`         | Project documentation. |
| `man_1_simple_shell` | Manual page describing usage, options, and behavior of the shell.|
| `AUTHORS` | File listing the contributors of the project. |

### Limitations
- Built-ins limited to **`exit`** and **`env`**.  
- No command chaining (`&&`, `||`, `;`) and no internal pipelines.  
- No variable expansion (`$VAR`), tilde expansion, or advanced quoting/escaping.  
- No built-ins like `cd`, `setenv`, `unsetenv` (beyond what’s implemented).  
- I/O redirection is not handled by the shell (non-interactive stdin works).  
- Error reporting is basic (unknown commands, system call failures).


## Getting Started
### Technologies Used
[![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)](#)
[![GitHub](https://img.shields.io/badge/GitHub-%23121011.svg?logo=github&logoColor=white)](#)
[![GCC](https://img.shields.io/badge/gcc-13.3.0-blue)](#)

## Overview
`hsh` reads a line from standard input, tokenizes it, dispatches built-ins (`exit`, `env`) or resolves external commands via `PATH`, then runs them in a child process (`fork`/`execve`) and waits with `waitpid` before looping again. It supports both interactive (prompted) and non-interactive (piped/scripted) modes and handles `SIGINT` gracefully without terminating the shell.

## Features
- Execute programs by absolute/relative path or via PATH lookup
- Whitespace-delimited argument parsing
- Built-ins: exit, env
- Interactive mode with prompt ($)
- Non-interactive execution (piped or redirected input)
- Basic error reporting for unknown commands and system call failures

### Requirements
- OS: Ubuntu 20.04 LTS
- Compiler: `gcc` with flags `-Wall -Wextra -Werror -pedantic -std=gnu89`
- Notes: uses POSIX APIs (`fork`, `execve`, `waitpid`, `isatty`, `getline`, …).
        Windows is supported via WSL only.


## Build

```sh
git clone https://github.com/MElisoltanov/holbertonschool-simple_shell.git

cd holbertonschool-simple_shell

gcc -Wall -Wextra -Werror -pedantic -std=gnu89 *.c -o hsh

./hsh
```

## Usage
### Interactive Mode
Start the shell in interactive mode:
```sh
./hsh
($) ls -l
($) exit
```
You can exit with Ctrl-D (EOF) or the built-in `exit` command.

### Non-Interactive Mode
Run commands via a pipe or a script file:
```sh
echo "ls -l" | ./hsh
# or
./hsh < scriptfile
```

## Built-in Commands
- `exit`: exits the shell
- `env`: prints the current environment, one variable per line

## Exit Codes
- The shell returns 0 on normal termination.
- Built-ins and external commands set an internal status used within the loop.
  (If you later return this status from `main`, update this section to:
   “returns the last command’s exit status”.)

## Examples
```sh
# Run a command from the PATH
($) echo Hello
Hello

# Run with an absolute path
($) /bin/ls

# Unknown command (example)
($) lol
./hsh: 1: lol: not found
```

## Man page
To view the manual.

You can use:
```sh
man -l man_1_simple_shell
```

## Project Structure
```txt
.
├── shell.h
├── main.c
├── loop.c
├── input.c
├── parse.c
├── execute.c
├── path.c
├── signals.c
├── builtin.c
├── builtin_env.c
├── builtin_exit.c
├── errors.c
├── memory.c
├── man_1_simple_shell
├── README.md
└── AUTHORS
```

## Authors
- [Haï-tu N.](https://github.com/N-Haitu31)
- [Moussa E.](https://github.com/MElisoltanov)