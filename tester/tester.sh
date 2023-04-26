#!/bin/bash

### make tmp dit and ensure that the temporary directory is always cleaned up.
rm -rf ./tester/output; rm -rf ./tester/trace
mkdir -p ./tester/output; mkdir -p ./tester/trace

### turn on for secured removal of files if tester crashes
# trap 'rm -rf ./tester/output' EXIT

echo -e "\n\033[1m\033[38;5;202mTesting Minishell vs Bash...\033[0m\n"

trace=false
clean=false
if [[ "$*" == *" -v" ]]; then
	trace=true
fi
if [[ "$*" == *" -c" ]]; then
	clean=true
fi

### Compare output files
compare_output() {
    printf "\n\n\t\tcommand=> $command\n" >> ./tester/trace/traces_$test_name
	diff ./tester/output/bash_output ./tester/output/minishell_output >> ./tester/trace/traces_$test_name
	if [ "$?" -eq "0" ]; then
    	printf "\t\e[32mOutput OK!\e[0m\n"
	else
		printf "\t\e[31mOutput KO! \e[1;36m$command\e[0m\n"
		if [ "$trace" == true ]; then
			printf "\tDelta:\n"
			cat ./tester/trace/traces_$test_name
		fi
		if [ "$segfault" = "1" ]; then
			printf "\t\033[1m\033[31mSegfault!!!\e[0m\n" #move
		fi
	fi
}

execute_command (){
	local shell=$1
	local command=$2
	### default is not sending the error messages to the outputfile 
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

	while read -r line; do
	if [ -z "$line" ] || [[ "$line" = "#"* ]]; then
		continue
	fi
	segfault=0
	# add flag and name
	execute_command "./minishell" "$line" >& ./tester/output/error
	execute_command "bash" "$line" >& ./tester/output/error
	
	##check if os is MacOs if not assume Linux / Gnu
	os=$(uname -s)
	if [ "$os" = "Darwin" ]; then
		sed -i '' '/0;36m/d' ./tester/output/minishell_output
		sed -i '' '/^$/d' ./tester/output/minishell_output
		sed -i '' '/^$/d' ./tester/output/bash_output
	else
		sed -i '/0;36m/d' ./tester/output/minishell_output
		sed -i '/^$/d' ./tester/output/minishell_output
		sed -i '/^$/d' ./tester/output/bash_output
	fi
	compare_output
	done < $file_name
}

if [ $# -eq 0 ]; then
	echo "Running all tests..."
	file_name="tester/tests/pipe_tests";	 	run_tests
	file_name="tester/tests/quote_tests";		run_tests
	file_name="tester/tests/built_in_tests";	run_tests
	file_name="tester/tests/assign_tests";		run_tests
	file_name="tester/tests/redirect_tests";	run_tests
	file_name="tester/tests/here_doc_tests";	run_tests
	file_name="tester/tests/signal_tests";		run_tests
	file_name="tester/tests/cond_pipe_tests";	run_tests
	file_name="tester/tests/wildcard_tests";	run_tests
fi

for arg in "$@"; do
	if [ "$arg" == "-v" ] || [ "$arg" == "-c" ]; then
		continue
		#e for error 
	elif [ "$arg" == "s" ]; then
		file_name="tester/tests/simple_tests";		run_tests;
	elif [ "$arg" == "q" ]; then
		file_name="tester/tests/quote_tests";		run_tests;
	elif [ "$arg" == "b" ]; then
		file_name="tester/tests/built_in_tests";	run_tests;
	elif [ "$arg" == "a" ]; then
		file_name="tester/tests/assign_tests";		run_tests;
	elif [ "$arg" == "r" ]; then
		file_name="tester/tests/redirect_tests";	run_tests;
	elif [ "$arg" == "h" ]; then
		file_name="tester/tests/here_doc_tests";	run_tests;
	elif [ "$arg" == "z" ]; then
		file_name="tester/tests/signal_tests";		run_tests;
	elif [ "$arg" == "c" ]; then
		file_name="tester/tests/cond_pipe_tests";	run_tests;
	elif [ "$arg" == "w" ]; then
		file_name="tester/tests/wildcard_tests";	run_tests;
	else
        echo "Invalid argument: $arg"
	fi
	done

if [ "$clean" == true ]; then
	rm -rf ./tester/output
	rm -rf ./tester/trace
fi
### optional turn on to remove output folder after each test run
# rm -rf ./tester/output