#!/bin/bash

# Run in minishell to test

#make tmp dit and ensure that the temporary directory
#is always cleaned up.
mkdir -p ./test
trap 'rm -rf ./test' EXIT

# Run ninishell, execute commands save in file
pwd > ./test/minishell_output.txt
cd src
ls >> ./test/minishell_output.txt
cd ..
pwd >> ./test/minishell_output.txt
var=42
echo $var >> ./test/minishell_output.txt
export var2=KOE >> ./test/minishell_output.txt
env >> ./test/minishell_output.txt
export >> ./test/minishell_output.txt

# Save exit code of Minishell
exitcode_minishell=$?

# Run Bash, execute commands save in file
bash <<EOF > ./test/bash_output.txt
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

#Save exit code of Bash
exitcode_bash=$?

# # Compare outputs and exit codes
diff ./test/bash_output.txt ./test/minishell_output.txt
if [ "$exitcode_minishell" -eq "$exitcode_bash"]; then
     echo "exit_code OK!"
else
     echo "exit_code KO!"
	 echo "expected $exitcode_bash"
	 echo "found $exitcode_minishell" 
fi

# Clean up temporary files
rm -rf ./test
