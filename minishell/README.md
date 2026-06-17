*This project has been created as part of the 42 curriculum by rzaatreh.*


## Description

**Minishell** is a mini-version of a real command-line shell, modeled after Bash. The goal of this project is to explore the inner workings of operating systems by designing a program capable of parsing user input, managing a local environment system, launching system executables, and connecting multiple concurrent processes through custom pipeline infrastructures.

### Project Overview

At its core, Minishell operates as an infinite read-eval-print loop (REPL). It intercepts raw keyboard inputs from the terminal, breaks down commands into structured grammatical syntax trees, expands variables, and safely interfaces with the system kernel via process duplication and file-descriptor multiplexing.

---

## Features

* **Interactive Command Line:** Powered by the GNU `readline` library, offering smooth cursor navigation, text editing, and command history retention.
* **The 7 Core Shell Builtins:** Completely native C implementations that run inside the parent process without spawning child forks:
* `echo` (with support for the `-n` option)
* `cd` (with absolute or relative paths, updating `PWD` and `OLDPWD`)
* `pwd` (fetches current directory tracking)
* `export` (appends or modifies tracking environment variables)
* `unset` (removes selective variables from the environment)
* `env` (displays all currently visible exported variables)
* `exit` (safely terminates the shell matrix with standard numeric exit statuses)


* **Redirection Engines:** Allows standard inputs and outputs to be decoupled and tied to data files:
* `<` redirects input streams from standard files.
* `>` redirects output streams to files (overwriting mode).
* `>>` redirects output streams to files (append mode).
* `<<` (Heredoc) reads input sequentially until a designated delimiter token is reached.


* **Pipes (`|`):** Connects the output stream of one command directly into the input stream of the next. Multiple pipelines are managed simultaneously.
* **Variable Expansions:** Resolves environment variables preceded by `$` and dynamically expands `$?` to the exit status code of the most recently executed foreground pipeline.
* **Signal Adjustments:** Captures interrupts dynamically:
* `Ctrl-C` cancels the current prompt line and renders a clean line.
* `Ctrl-\` is ignored across general prompt sequences to avoid unexpected runtime terminations.
* `Ctrl-D` transmits an EOF signal to cleanly shut down the shell interface.




## Technical Choices

To preserve structural safety, minimize memory fragmentation, and strictly avoid memory leaks, the architecture uses a clearly separated multi-tier pipeline:

1. **Lexer (Tokenization):** Takes raw text streams and chunks them into semantic pieces (Words, Pipes, Redirection Operators) while correctly preserving single and double-quoted literals.
2. **Parser (Grammar Assembly):** Aggregates tokens into clean, actionable data nodes, verifying execution grammar patterns and highlighting syntax errors before execution begins.
3. **Expander (Variable Translation):** Strips redundant outer quotes and replaces environmental keys with their matching system values.
4. **Executor (Process Management):** Allocates pipe systems, sets up files via `dup2`, forks child nodes for complex binaries, and cleans up open file descriptors systematically.


## Instructions

### Prerequisites

To compile and run this project, you must have a C compiler (`gcc` or `clang`) along with the GNU `readline` development library installed on a Linux or macOS environment.


### Compilation

A multi-tier `Makefile` is included at the root level of the project. Build the executable by running:

```bash
make

```

**Available Compilation Commands:**

* `make clean` – Removes intermediate binary object files (`.o`).
* `make fclean` – Deletes the object files as well as the final compiled `minishell` executable.
* `make re` – Forces a complete re-compilation of the codebase from scratch.

### Execution

Launch the interpreter by invoking the compiled binary:

```bash
./minishell

```

---

## Resources

### Classic References

- [Bash Overview](https://www.gnu.org/software/bash/manual/bash.html#Shell-Operation)
- [Using Fork and Pipe](https://eceweb.uwaterloo.ca/~agurfink/ece650.f19/assets/pdf/04_ForkPipe.pdf)
- [Programming with GNU Readline](https://web.mit.edu/gnu/doc/html/rlman_2.html)
- [code-vault](https://code-vault.net/)
- [Minishell: Building a mini-bash](https://medium.com/@zouhairlrs/minishell-building-a-mini-bash-a-42-project-5dc20d671fbb)

### AI Usage Statement

AI tools were selectively integrated into the workflow of this project for the following development tasks:

* **Edge Case Verification:** Brainstorming complex quote and redirection token combinations (e.g., nested quotes like `echo "'$USER'"` or edge sequences like `cat < file1 > file2`) to help structure the lexer's validation states.
* **Memory Architecture Design:** Reviewing structural strategies for clean pointer cleanup arrays (`token_clear`, `cmd_clear`) to prevent leaks inside long-running interactive shell loops.
* **Documentation Formatting:** Assisting in structural organization and proofreading layout phrasing to generate this compliant `README.md` file.
