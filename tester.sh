#!/bin/bash

# Run ninishell, execute commands save in file
./minishell <<EOF > minishell_output.txt
pwd
cd src
ls
cd ..
pwd
var=42
echo $var
export var2=KOE
env
export
EOF


# Save exit code of Minishell
# exitcode_minishell=$?

# Run Bash, execute commands save in file
# bash <<EOF > bash_output.txt
# pwd
# cd src
# ls
# cd ..
# pwd
# var=42
# echo $var
# export var2=KOE
# env
# export
# EOF

# Save exit code of Bash
# exitcode_bash=$?

# # Compare outputs and exit codes
# if 
# [[ "$exitcode_minishell" -eq "$exitcode_bash" && $(cmp -s minishell_output.txt bash_output.txt) ]]; then
#     echo "Test succeeded!"
# else
#     echo "Test failed!"
# fi

# Clean up temporary files
# rm minishell_output.txt bash_output.txt
# Run minishell and execute commands