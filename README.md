# minishell

minishell is a Unix shell project from the 42 School common core curriculum.

The goal of the project is to recreate a simplified shell, handling command execution, pipes, redirections, environment variables and built-in commands.

## Features

- Interactive shell prompt
- Command parsing and execution
- Environment variable expansion
- Pipes
- Input and output redirections
- Heredoc support
- Signal handling
- Exit status management
- Built-in commands:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

## Concepts

- C programming
- Unix processes
- File descriptors
- Pipes and redirections
- Environment management
- Signal handling
- Parsing
- Memory management

## Usage

Compile the project:

```bash
make
```

Run the shell:

```bash
./minishell
```

Clean generated files:

```bash
make fclean
```

## Note

This project was developed as part of the 42 School curriculum and follows the project constraints defined by the subject.