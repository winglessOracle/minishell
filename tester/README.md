# Minishell Testing Script

Authors: [wesseling & caljouw]
Date: May 2023

This script is used to test the functionality of a minishell program by comparing its output with that of Bash. It executes a set of commands for each type of test specified and compares the output of both shells.

## Disclaimer
The tester was used for personal testing of our minishell and is not cleaned or optimized for general use however I included it in this repository as I think it offers a good foundation for others to build their own testers. Known issue are various doubles in the different tests, some tests writing to the root folder and discrepencies in usage of the /bin functions. 

Also, in some Linux distributions redirects to exisiting files are not allowed. 
We choose to allow overwriting existing files. To modify the behaviour in bash to meet our version change the noclobber setting: 'set +o noclobber'.

## Usage
The test files are located in the "tests" folder.

To run specific types of tests, pass the corresponding letters as arguments (e.g., "s q x" to run simple, env, and expansion tests).
The corresponding letters are:
- s: simple_tests: tests simple commands
- q: quote_tests: tests quotes and escape characters
- b: built_in_tests: tests built-in commands
- a: assign_tests: tests variable assignments
- r: redirect_tests: tests redirection
- c: cond_pipe_tests: tests conditional pipes
- w: wildcard_tests: tests wildcard expansion
- cd: cd_tests: tests various cd commands
- exp: export_tests: tests export commands
- uns: uset_tests: tests unsetting of environment variables
- exit: exit_tests: tests exit values

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

