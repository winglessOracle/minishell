# minishell | CODAM Amsterdam

## Introduction
Minishell is a simple shell written in C as a project for CODAM programming school. It allows you to run commands and manage files through a terminal interface similar to bash but with less features.

## Features
Display a prompt and wait for user input
Launch executables using a path or the PATH environment variable
Handle input/output redirection and pipes
Handle environment variables
Implement built-in commands (echo, cd, pwd, export, unset, env, exit)

## Requirements
C compiler (tested with clang)
GNU Readline library (libreadline-dev)

## Installation
Clone the repository: git clone https://github.com/yourusername/minishell.git
Change directory: cd minishell
Compile: make or make bonus
Run the executable: ./minishell

You can enter commands and use the built-in commands. To exit, type exit or press Ctrl+D.

## Known Issues
Wildcards (*) are only supported in the bonus.
Memory leaks caused by the readline() can occur.

## Credits
This Minishell was created by Carien Caljouw and Carlo Wesseling as a project for CODAM programming school.
