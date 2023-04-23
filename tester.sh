#!/bin/bash

### Run in minishell to test

### parameters: 
## s >> single command tests
## m >> multi command tests
## env >> env tests
## exp >> expander tests
## q >> quote tests
## b >> built-in tests
## a >> assign tests
## r >> redirect tests
## h >> here_doc tests

## make tmp dit and ensure that the temporary directory is always cleaned up.
mkdir -p ./test

>./test/minishell_output.txt #remove
>./test/bash_output.txt #remove
trap 'rm -rf ./test' EXIT

echo -e "\n\033[1m\033[38;5;202mTesting Minishell vs Bash...\033[0m\n"

compare_output() {

## Compare outputs and exit codes

	echo -e "\tComparing output..."
	diff ./test/bash_output.txt ./test/minishell_output.txt > ./test/diff
	if [ "$?" -eq "0" ]; then
    	echo -e "\t\e[32mOutput OK!\e[0m"
	else
    	echo -e "\t\e[31mOutput KO!\e[0m\n"
		echo -e "Delta:"
		cat ./test/diff
	fi

	## Compare exit codes
	echo -e "\tComparing exit codes..."
	if [ "$exitcode_minishell" -eq "$exitcode_bash" ]; then
    	echo -e "\t\e[32mExit code OK!\e[0m\n"
	else
    	echo -e "\t\e[31mExit code KO!\e[0m"
    	echo -e "\tExpected exit code: $exitcode_bash"
    	echo -e "\tFound exit code: $exitcode_minishell\n"
	fi
}

single_tests() {
    echo "Running single command tests..."

	## Minishell tests
	ls > ./test/minishell_output.txt
	find Makefile >> ./test/minishell_output.txt

	exitcode_minishell=$?

 	## Bash tests
	bash -c 'ls; find Makefile' > ./test/bash_output.txt

	exitcode_bash=$?
	compare_output
}

multi_tests() {
    echo "Running multi tests..."

	## Minishell tests
	ls | ls > ./test/minishell_output.txt
	ls | cat >> ./test/minishell_output.txt
	ls | cat | grep Make >> ./test/minishell_output.txt
	
	exitcode_minishell=$?

 	## Bash tests
	bash -c 'ls | ls; ls | cat; ls | cat | grep Make' > ./test/bash_output.txt
	
	exitcode_bash=$?
	compare_output
}

env_tests() {
    echo "Running environment tests..."

	## Minishell tests
	ls | ls > ./test/minishell_output.txt

	exitcode_minishell=$?

 	## Bash tests
	bash -c 'ls' > ./test/bash_output.txt

	exitcode_bash=$?
	compare_output
}

exp_tests() {
    echo "Running expansion tests..."

	## Minishell tests
	ls | ls > ./test/minishell_output.txt

	exitcode_minishell=$?


 	## Bash tests
	bash -c 'ls' > ./test/bash_output.txt

	exitcode_bash=$?
	compare_output
}

quote_tests() {
    echo "Running quotation tests..."

	## Minishell tests
	ls | ls > ./test/minishell_output.txt

	exitcode_minishell=$?

 	## Bash tests
	bash -c 'ls' > ./test/bash_output.txt

	exitcode_bash=$?
	compare_output
}

built_tests() {
    echo "Running built-in tests..."

	## Minishell tests
	ls | ls > ./test/minishell_output.txt

	exitcode_minishell=$?

 	## Bash tests
	bash -c 'ls' > ./test/bash_output.txt

	exitcode_bash=$?
	compare_output
}

assign_tests() {
    echo "Running assign tests..."

	## Minishell tests
	ls | ls > ./test/minishell_output.txt

	exitcode_minishell=$?

 	## Bash tests
	bash -c 'ls' > ./test/bash_output.txt

	exitcode_bash=$?
	compare_output
}

redirect_tests() {
    echo "Running redirect tests..."

	## Minishell tests
	ls | ls > ./test/minishell_output.txt

	exitcode_minishell=$?

 	## Bash tests
	bash -c 'ls' > ./test/bash_output.txt

	exitcode_bash=$?
	compare_output
}

heredoc_tests() {
    echo "Running here_doc tests..."

	## Minishell tests
	ls | ls > ./test/minishell_output.txt

	exitcode_minishell=$?

 	## Bash tests
	bash -c 'ls' > ./test/bash_output.txt

	exitcode_bash=$?
	compare_output
}

if [ "$1" == "s" ]; then
	single_tests
	exit 0
elif [ "$1" == "m" ]; then
    multi_tests
	exit 0
elif [ "$1" == "env" ]; then
    env_tests
	exit 0
elif [ "$1" == "exp" ]; then
    exp_tests
	exit 0
elif [ "$1" == "q" ]; then
    quot_tests
    exit 0
elif [ "$1" == "b" ]; then
    built_tests
    exit 0
elif [ "$1" == "a" ]; then
    assign_tests
    exit 0
elif [ "$1" == "r" ]; then
    redirect_tests
    exit 0
elif [ "$1" == "h" ]; then
    heredoc_tests
    exit 0
else
	echo "Running all tests..."
	assign_tests
	redirect_tests
	heredoc_tests
	single_tests
	built_tests
	multi_tests
	env_tests
	exp_tests
	quote_tests
	rm -rf ./test
	exit 0
fi
rm -rf ./test


###############################################################3

# pwd > ./test/minishell_output.txt
# cd src
# ls | head -n 5 >> ../test/minishell_output.txt
# cd ..
# pwd >> ./test/minishell_output.txt
# var=42
# echo $var >> ./test/minishell_output.txt
# export var2=KOE
# env | head -n 5 >> ./test/minishell_output.txt
# export | head -n 5 >> ./test/minishell_output.txt


# ## Run Bash, execute commands save in file
# bash -c 'pwd; cd src; ls | head -n 5; cd ..; pwd; var=42; echo $var; \
# export var2=KOE; env | head -n 5; export | head -n 5' > ./test/bash_output.txt
