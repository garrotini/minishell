# minishell

## description

This is a simplified Unix shell project, part of the 42 school curriculum. 

It should somehow be similar to Bash (Bourne Again Shell).

It was a group project.

I took care of the parsing and Joefriends (https://github.com/Joefriends) took care of the execution.

## features

### built-in commands
| Command | Description |
|---------|-------------|
| `echo` | prints text to stdout |
| `cd` | changes directory |
| `pwd` | print working directory |
| `export` | set environment variables |
| `unset` | remove environment variables |
| `env` | Display all environment variables |
| `exit` | Exit the shell with optional exit code |

### operators
- **Pipes** (`|`)
- **Semicolon** (`;`)
- **Input redirection** (`<`)
- **Output redirection** (`>`)
- **Append** (`>>`)
- **Heredoc** (`<<`)

### other Features
- Environment variable expansion (`$VAR`)
- Exit code expansion (`$?`)
- Single and double quote handling
- Signal handling (Ctrl+C, Ctrl+\)
- Command history (readline)

## build
```bash
make
```

### clean
```bash
make clean   # Remove object files
make fclean  # Remove object files and binary
make re      # Rebuild from scratch
```

## usage

```bash
./minishell
```

Use it the regular BASH, although do not forget: it's a **minishell**!

Check `make vs` and `make vf`, if you want to launch the program with valgrind.
(I added those optional rules to Makefile, so I can use them as sort of a script for debbuging)

## project structure

```
Input → Lexer → Parser → Executor → Output
```

```
src/
├── builtins/    # built-in commands
├── execution/   # execution and pipeline handling
├── exit/        # clean exit and error handling
├── init/        # init_shell and signal handlers
├── lexer/       # lexical analysis and tokenization
├── parser/      # syntax parsing and command building
├── utils/       # utils
└── main.c       # main function and REPL loop
```

## exit codes

| Code | Description |
|------|-------------|
| 0 | Success |
| 1 | General error |
| 2 | Syntax error |
| 126 | Command not executable |
| 127 | Command not found |
| 128+N | Terminated by signal N |

## demo

here's some examples of **minishell** compared to **BASH**

(I totally forgot to test `exit` command!)

[![minishell.mp4](https://github.com/user-attachments/assets/b33d3532-6dff-412f-9680-546c3d1b96d5)](https://github.com/user-attachments/assets/3bd17bbc-e5f5-4d23-a79b-75329b17cb00)


## license
This project is part of the 42 school curriculum.

