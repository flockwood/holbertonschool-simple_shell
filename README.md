# 🐚 C - Simple Shell (`hsh`)

A lightweight UNIX command interpreter replicating core shell functionalities.

---

## 📜 Table of Contents
- [Introduction](#introduction)
- [Key Concepts](#key-concepts)
- [Built-in Commands](#built-in-commands)
- [External Commands](#external-commands)
- [System Calls & Functions](#system-calls--functions)
- [Allowed Functions](#allowed-functions)
- [Usage](#usage)
- [Error Handling](#error-handling)
- [Authors](#authors)

---

## 🚀 Introduction

### What is a Shell?
A shell is a program that reads commands from a user and interprets them to execute programs, scripts, or built-in functionalities. It acts as a bridge between the user and the operating system.

### About `hsh`
`hsh` is a custom implementation of a simple shell, built in C. It includes:
- Interactive and non-interactive modes
- Built-in commands like `exit` and `env`
- Execution of external programs
- PATH resolution for finding executables
- Environment variable access
- Error handling and status management

---

## 🧠 Key Concepts

### PID and PPID
- **PID (Process ID):** ID assigned to each running process.
- **PPID (Parent Process ID):** The PID of the process that created the current one.

### Process Control
- **`fork()`** - creates child processes.
- **`execve()`** - replaces the current process image with a new program.
- **`wait()`/`waitpid()`** - makes the parent wait for child process termination.

### Environment Variables
- Accessed via `environ`.
- Environment manipulation allows command lookup via `PATH`.

### PATH Resolution
The shell parses the `PATH` environment variable to find executable files if the command is not provided with an absolute or relative path.

### Compilation

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

### Main Signatures Supported
- `int main(void)`
- `int main(int argc, char *argv[])`
- `int main(int argc, char *argv[], char *envp[])`

---

## 📌 Built-in Commands

| Command  | Description                       |
|----------|-----------------------------------|
| `exit`   | Exits the shell with a status code |
| `env`    | Prints the current environment    |

*Built-ins are handled internally without creating a child process.*

---

## 📂 External Commands

If a command is not a built-in, `hsh`:
- Searches directories listed in `PATH`
- Executes the program via `execve()`

Examples:
- `ls`
- `pwd`
- `cat`
- `mkdir`

---

## ⚙️ System Calls & Functions

| Purpose              | System Calls / Functions             |
|----------------------|---------------------------------------|
| Process management   | `fork()`, `execve()`, `wait()`, `waitpid()` |
| Input reading        | `getline()`, `read()`                 |
| File handling        | `open()`, `close()`, `stat()`, `lstat()`, `fstat()` |
| Directory handling   | `chdir()`, `getcwd()`, `opendir()`, `readdir()`, `closedir()` |
| Memory management    | `malloc()`, `free()`                  |
| Environment access   | `environ`, `getenv()`                 |
| Output               | `write()`, `perror()`, `fflush()`     |

---

## ✅ Allowed Functions

**String and Memory:**
- `strtok`, `strlen`, `strcmp`, `strcpy`, `strchr`, `strstr`
- `memcpy`, `memmove`, `memset`, `memcmp`
- `malloc`, `free`

**Process and Execution:**
- `fork`, `execve`, `wait`, `waitpid`, `wait3`, `wait4`
- `_exit`, `exit`

**File and Directory Operations:**
- `open`, `close`, `read`, `write`, `stat`, `lstat`, `fstat`
- `chdir`, `getcwd`, `opendir`, `readdir`, `closedir`

**Environment and Output:**
- `environ`, `getenv`
- `perror`, `printf`, `fprintf`, `vfprintf`, `putchar`, `fflush`
- `isatty`, `kill`

---

## 💻 Usage

### Interactive Mode
$ ./hsh
$ ls -l
$ pwd
$ exit


### Non-Interactive Mode
$ echo "ls -l /tmp" | ./hsh

Or

$ cat commands.txt | ./hsh
(where `commands.txt` contains a list of commands)

---

## ❗ Error Handling

- Command Not Found:
  fprintf(stderr, "./hsh: 1: %s: not found\n", command);
  Exits with status 127.

- Failed System Calls:
  perror("Error");

- Fork Failures:
  Reported using perror() and handled gracefully.

---

## 👥 Authors

- Fernando Lockwood - flockwood@live.com
- Andres Mora - andresfmora.catro@gmail.com


