# Shell Script for xv6

This project implements a simple shell interface for the xv6 operating system. The shell supports basic command execution, input/output redirection, piping, and more. It is implemented in the file `my_shell.c`.

## Features

The shell implements the following features:

### Basic Shell Setup :

- **Shell Initialization**: The shell starts by initializing and creating a command prompt that interacts with the user.
- **Executable Integration**: The shell is included as an executable in the xv6 operating system and can be run by typing `myshell` at the command prompt.
  
### Execute Simple Commands :

- **Command Prompt**: The shell displays a `>>>` prompt, awaiting user input.
- **Command Execution**: Executes simple user commands like `ls`, `echo`, etc.
- **Loop**: The shell loops indefinitely, allowing continuous command execution.
- **Handle `cd` Command**: Implements the `cd` command, which changes the current directory and handles special cases related to this command.
- **Edge Case Handling**: Deals with input formatting issues like extra spaces between commands.

### Input/Output Redirection :

- **Redirection**: Handles input and output redirection using `>` and `<`.
  - Example: `echo "Hello world" > temp`
  - Example: `cat < temp`

### Pipes :

- **Piping**: Implements two-element pipes, allowing command output to be piped as input to the next command.
  - Example: `cat README | grep github`

### Additional Features :

- **Multi-Element Pipelines**: Supports multi-element pipes.
  - Example: `ls | grep test | cat`
- **Combining Pipes and Redirection**: Supports complex combinations of pipes and redirection.
  - Example: `ls | grep test | cat > myoutput`
- **`Semicolon (;)` Operator**: Implements the semicolon operator to execute a list of commands sequentially.
  - Example: `ls | grep test | cat > myoutput; cat myoutput`

## How to Run

1. Place `my_shell.c` in the `user` directory of the xv6 source code.
2. Modify the `Makefile` to include the new shell in the build process.
3. Compile xv6 by running:

   ```bash
   make qemu
