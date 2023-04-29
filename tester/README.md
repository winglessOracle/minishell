# Minishell Testing Script

Authors: [wesseling caljouw]
Date: September 2021

This script is used to test the functionality of a minishell program by comparing its output with that of Bash. It executes a set of commands for each type of test specified and compares the output of both shells.

The test files are located in the "tests" folder.

To run specific types of tests, pass the corresponding letters as arguments (e.g., "s q x" to run simple, env, and expansion tests).

The corresponding letters are:
- s: simple_tests: tests simple commands
- q: quote_tests: tests quotes and escape characters
- b: built_in_tests: tests built-in commands
- a: assign_tests: tests variable assignments
- r: redirect_tests: tests redirection
- h: here_doc_tests: tests here documents
- z: signal_tests: tests signals and interrupts
- c: cond_pipe_tests: tests conditional pipes
- w: wildcard_tests: tests wildcard expansion


## Usage

1. Run the script in the folder where the minishell executable is located.
2. To run specific types of tests, pass the corresponding letters as arguments (e.g., "s e x" to run simple, env, and expansion tests).
3. If no arguments are provided, all tests are run by default.
4. "-v" flag, displays traces in the terminal for each test.
5. "-c" flag, cleans up all output files.
6. "-e" flag, shows errormessages on terminal.

## Output

The script generates two output files for each test: "bash_output" and "minishell_output". The output of each command is written to these files, along with the exit code and the command itself. If the output of the minishell and Bash differ, the script writes the command and the delta to a trace file.
The trace files are located in the "trace" folder and are named "traces_[test_name]".

## OS Checker

The script automatically detects the operating system and adjusts the sed commands accordingly. For example, on macOS, the sed command requires an extra empty string argument. The script uses the `uname -s` command to determine the operating system and adjusts the sed commands accordingly.

## Cleanup and Error Handling

The script cleans up the output and trace folders before each execution of the code. The `-c` flag can be passed to clean up all output files.
The script also includes a commented-out `trap` command that can be used to ensure that the temporary directory is always cleaned up if the script crashes.