#!/bin/bash

### Run ./tester/tester.sh in minishell main folder to test

### parameters: 
## s >> single command tests
## p >> multi command tests
## env >> env tests
## exp >> expander tests
## q >> quote tests
## b >> built-in tests
## a >> assign tests
## r >> redirect tests
## h >> here_doc tests
## sig >> signal tests
## c >> conditional pipe tests
## w >> wildcard tests

## make tmp dit and ensure that the temporary directory is always cleaned up.
rm -rf ./tester/output; rm -rf ./tester/trace
mkdir -p ./tester/output; mkdir -p ./tester/trace
trap 'rm -rf ./tester/output' EXIT

echo -e "\n\033[1m\033[38;5;202mTesting Minishell vs Bash...\033[0m\n"

compare_output() {
## Compare outputs and exit codes
	printf "  \e[34mTest %.2d  \e[0m" $counter
    printf "\n\n\t\tcommand=> $command\n" >> ./tester/trace/traces_$test_name
	diff ./tester/output/bash_output ./tester/output/minishell_output >> ./tester/trace/traces_$test_name
	if [ "$?" -eq "0" ]; then
    	printf "\e[32mOK\e[0m\n"
	else
    	printf "\e[31mKO \e[1;36m\t$command\e[0m\n"
	fi
	if [ "$segfault" = "1" ]; then
		printf "\t\t\t\033[1m\033[31mSegfault!!!\e[0m\n\n"
	fi
}

execute_command (){
	shell=$1
	command=$2

	output=$($shell <<EOF
	$command
EOF
)
	exitcode=$?
	printf "Command: $command\n" >> ./tester/output/${shell}_output
	printf "Output:\n$output\n" >> ./tester/output/${shell}_output
	printf "Exit code: $exitcode\n" >> ./tester/output/${shell}_output
	if [ "$exitcode" = "139" ]; then
		segfault=1
	fi
}

run_tests() {
	test_name=$(basename "$file_name")
    printf "\n\e[1;36mRunning "$test_name"...\e[0m\n"
	counter=0

	## Minishell tests
	while read -r line; do
	if [ -z "$line" ] || [[ "$line" = "#"* ]]; then
		continue
	fi
	segfault=0
	counter=$((counter+1))
	execute_command "./minishell" "$line" #>& ./tester/output/error
	execute_command "bash" "$line" #>& ./tester/output/error
	
	##MacOs
	sed -i '' '/0;36m/d' ./tester/output/minishell_output
	sed -i '' '/^$/d' ./tester/output/minishell_output
	sed -i '' '/^$/d' ./tester/output/bash_output
	
	##linux
	# sed -i '/0;36m/d' ./tester/output/minishell_output
	# sed -i '/^$/d' ./tester/output/minishell_output
	# sed -i '/^$/d' ./tester/output/bash_output
	
	compare_output
	rm ./tester/output/bash_output
	rm ./tester/output/minishell_output
	done < $file_name
}

if [ "$1" == "p" ]; then
	file_name="tester/tests/pipe_tests";		run_tests;
elif [ "$1" == "env" ]; then
	file_name="tester/tests/env_tests";			run_tests;
elif [ "$1" == "exp" ]; then
	file_name="tester/tests/exp_tests";			run_tests;
elif [ "$1" == "q" ]; then
	file_name="tester/tests/quote_tests";		run_tests;
elif [ "$1" == "b" ]; then
	file_name="tester/tests/built_in_tests";	run_tests;
elif [ "$1" == "a" ]; then
	file_name="tester/tests/assign_tests";		run_tests;
elif [ "$1" == "r" ]; then
	file_name="tester/tests/redirect_tests";	run_tests;
elif [ "$1" == "h" ]; then
	file_name="tester/tests/here_doc_tests";	run_tests;
# elif [ "$1" == "sig" ]; then
# 	file_name="tester/tests/signal_tests";		run_tests;
elif [ "$1" == "c" ]; then
	file_name="tester/tests/cond_pipe_tests";	run_tests;
elif [ "$1" == "w" ]; then
	file_name="tester/tests/wildcard_tests";	run_tests;
else
	echo "Running all tests..."
	file_name="tester/tests/pipe_tests";	 	run_tests
	file_name="tester/tests/env_tests";			run_tests
	file_name="tester/tests/exp_tests";			run_tests
	file_name="tester/tests/quote_tests";		run_tests
	file_name="tester/tests/built_in_tests";	run_tests
	file_name="tester/tests/assign_tests";		run_tests
	file_name="tester/tests/redirect_tests";	run_tests
	file_name="tester/tests/here_doc_tests";	run_tests
	# file_name="tester/tests/signal_tests";	run_tests
	file_name="tester/tests/cond_pipe_tests";	run_tests
	file_name="tester/tests/wildcard_tests";	run_tests
	exit 0
fi
rm -rf ./tester/output