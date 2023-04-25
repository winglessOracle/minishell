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
# trap 'rm -rf ./tester/output' EXIT

echo -e "\n\033[1m\033[38;5;202mTesting Minishell vs Bash...\033[0m\n"

compare_output() {
## Compare outputs and exit codes
	printf "\t\e[34mComparing output...\e[0m"
	diff ./tester/output/bash_output ./tester/output/minishell_output >> ./tester/trace/traces
	if [ "$?" -eq "0" ]; then
    	printf "\t\e[32mOutput OK!\e[0m\n"
	else
    	printf "\t\e[31mOutput KO!\e[0m\n"
		printf "\tDelta:\n" 
		cat ./tester/trace/traces
	fi

	# ## Compare exit codes
	# printf "\t\e[34mComparing exit codes...\e[0m"
	# if [ "$exitcode_minishell" -eq "$exitcode_bash" ]; then
    # 	printf "\t\e[32mExit code OK!\e[0m\n"
	# else
    # 	printf "\t\e[31mExit code KO!\e[0m\n"
    # 	printf "\tExpected exit_code: $exitcode_bash\n"
    # 	printf "\tFound exit_code: $exitcode_minishell\n"
	# fi
}

execute_bashcommand (){
	output=$(bash -c "$1" 2>&1)
	exitcode_bash=$?
	printf "Command: $1\n" >> ./tester/output/bash_output
	printf "Output: $output\n" >> ./tester/output/bash_output
	printf "Exit code: $exitcode_minishell\n" >> ./tester/output/bash_output
}

execute_minicommand (){
    output=$(my_eval "$1" 2>&1)
    exitcode_minishell=$?
    printf "Command: $1\n" >> ./tester/output/minishell_output
    printf "Output: $output\n" >> ./tester/output/minishell_output
    printf "Exit code: $exitcode_minishell\n" >> ./tester/output/minishell_output
}

run_tests() {
	test_name=$(basename "$file_name")
    printf "\n\e[1;36mRunning %s...\e[0m\n" "$test_name"
    printf "\n\n\t\tRunning %s...$test_name" >> ./tester/trace/traces

	## Minishell tests
	while read -r line; do
		if [ -z "$line" ]; then
			continue
		fi
		execute_minicommand "$line";
		execute_bashcommand "$line"
		compare_output
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
	file_name="tester/tests/signal_tests";		run_tests;
elif [ "$1" == "w" ]; then
	file_name="tester/tests/wildcard_tests";	run_tests;
else
	echo "Running all tests..."
	file_name="tester/tests/pipe_tests";	 	run_tests
	file_name="tester/tests/env_tests";			run_tests
	file_name="tester/tests/exp_tests";			run_tests
	file_name="tester/tests/quote_tests";		run_tests
	file_name="tester/tests/built_tests";		run_tests
	file_name="tester/tests/assign_tests";		run_tests
	file_name="tester/tests/redirect_tests";	run_tests
	file_name="tester/tests/here_doc_tests";	run_tests
	# file_name="tester/tests/signal_tests";		run_tests
	file_name="tester/tests/cond_pipe_tests";	run_tests
	file_name="tester/tests/wildcard_tests";	run_tests
	exit 0
fi
# rm -rf ./tester/output