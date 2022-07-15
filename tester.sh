#!/bin/bash

PIPEX_SOURCE=./
PIPEX_BIN=./pipex

source utils.sh
OS=$(uname)
if [[ $OS == "Linux" ]]
then
	function where_is() {
		whereis -b $1 | awk '{print $2}'
	}
else
	function where_is() {
		whereis $1
	}
fi
make -C $PIPEX_SOURCE $1 > /dev/null || exit 1

cat banner.txt

print_color $BOLD "Testers"

print_color $BOLD$MAGENTA "[+] Identity Tests : "

# Check norminette
find $PIPEX_SOURCE -name '*.c'  -o  -name '*.h' | xargs norminette | grep -v 'OK!' 2>/dev/null > log.txt
status_code=$?
if [ $status_code -eq 1 ]
then
	print_ok "\t[1] Norminette passed \t\t\t\t\t [OK]"
else
	print_ko "\t[1] Norminette passed \t\t\t\t\t [KO]"
fi

# Invalid number of args
mkdir -p ./.tmp
one=$($PIPEX_BIN 1 2> ./.tmp/one.txt)
one_exit=$?
two=$($PIPEX_BIN 1 2 2>./.tmp/two.txt)
two_exit=$?
three=$($PIPEX_BIN 1 2 3 2>./.tmp/three.txt)
three_exit=$?
if [[ $1 = "bonus" ]]
then
	four=$($PIPEX_BIN here_doc 1 2 3 2>./.tmp/four.txt)
    four_exit=$?
	diff --from-file ./.tmp/one.txt ./.tmp/two.txt ./.tmp/three.txt ./.tmp/four.txt > /dev/null
	if [ $? == 0 -a $one_exit -eq $two_exit -a $two_exit -eq $three_exit -a $three_exit -eq $four_exit ]
	then
		print_ok "\t[2] Invalid number of arguments \t\t\t [OK]"
	else
		print_ko "\t[2] Invalid number of arguments \t\t\t [KO]"
	fi
else
	diff --from-file ./.tmp/one.txt ./.tmp/two.txt ./.tmp/three.txt > /dev/null
	if [ $? == 0 ]
    then
        print_ok "\t[2] Invalid number of arguments \t\t\t [OK]"
    else
        print_ko "\t[2] Invalid number of arguments \t\t\t [KO]"
    fi
fi

# Check forbidden functions
nm -g -C --undefined-only $PIPEX_BIN | grep -v __  | grep -v dyld_stub_binder | tr -d '_' | cut -d ' ' -f 1 | cut -d '@' -f 1  > ./.tmp/functions.txt
COMM=$(comm -13 <(sort -u white.txt) <(sort -u ./.tmp/functions.txt) )
if [ $COMM ]
then
	print_ko "\t[3] The program doesn't use forbidden functions \t [KO]"
else
	print_ok "\t[3] The program doesn't use forbidden functions \t [OK]"
fi 


print_color $BOLD$MAGENTA "[+] Handling Paths : "

# Invalid PATH
OLD_PATH=$PATH
export PATH=x
CMD1=$($PIPEX_BIN /dev/null cat ls /dev/stdout 2> /dev/stdout)
export PATH=$OLD_PATH
if [[ $(echo $CMD1 | grep cat | grep -i "command not found") && $(echo $CMD1 | grep ls | grep -i "command not found") ]]
then
	print_ok "\t[4] The program handles invalid path \t\t\t [OK]"
else
	print_ko "\t[4] The program handles invalid path \t\t\t [KO]"
fi
# Empty PATH
OLD_PATH=$PATH
export PATH=
CMD1=$($PIPEX_BIN /dev/null cat ls /dev/stdout 2> /dev/stdout)
export PATH=$OLD_PATH
if [[ $(echo $CMD1 | grep cat | grep -i "command not found") && $(echo $CMD1 | grep ls | grep -i "command not found") ]]
then
	print_ok "\t[5] The program handles empty env PATH \t\t\t [OK]"
else
	print_ko "\t[5] The program handles empty env PATH \t\t\t [KO]"
fi

# unset PATH
OLD_PATH=$PATH
unset PATH
CMD1=$($PIPEX_BIN /dev/null cat ls /dev/stdout 2> /dev/stdout)
export PATH=$OLD_PATH
if [[ $(echo $CMD1 | grep cat | grep -i "command not found") && $(echo $CMD1 | grep ls | grep -i "command not found") ]]
then
	print_ok "\t[6] The program handles unset env PATH \t\t\t [KO]"
else
	print_ko "\t[6] The program handles unset env PATH \t\t\t [KO]"
fi

# absolute path
CAT=$(where_is cat)
WC=$(where_is wc)
NULL=$($PIPEX_BIN /dev/null $CAT "$WC -l" /dev/stdout | tr -d ' ')
if [[ $NULL == "0" ]]
then
	print_ok "\t[7] The program handles absolute paths \t\t\t [OK]"
else
	print_ko "\t[7] The program handles absolute paths \t\t\t [KO]"
fi

# relative path
B64=$(where_is base64)
HEAD=$(where_is head)
cp $B64 ./.tmp/base64
cp $HEAD ./.tmp/head
NULL=$($PIPEX_BIN /dev/zero "./.tmp/head -c 10" "./.tmp/base64" /dev/stdout)
if [[ $NULL == "AAAAAAAAAAAAAA==" ]]
then
	print_ok "\t[8] The program handles relative paths \t\t\t [OK]"
else
	print_ko "\t[8] The program handles relative paths \t\t\t [KO]"
fi

# File doesn't exist

print_color $BOLD$MAGENTA "[+] Handling files : "

CMD=$($PIPEX_BIN /dev/non-existent cat shasum /dev/stdout 2> ./.tmp/non-existent)
if [[ $(cat ./.tmp/non-existent | grep -i "No such file or directory") && $CMD == *"da39a3ee5e6b4b0d3255bfef95601890afd80709"* ]]
then
	print_ok "\t[9] Handle non existing file \t\t\t\t [OK]"
else
	print_ko "\t[9] Handle non existing file \t\t\t\t [KO]"
fi

# Permission denied (READ)

touch .tmp/missing-permission
chmod -r .tmp/missing-permission
CMD=$($PIPEX_BIN ./.tmp/missing-permission cat shasum /dev/stdout 2> ./.tmp/permission-denied)
if [[ $(cat ./.tmp/permission-denied | grep -i "permission denied") && $CMD == *"da39a3ee5e6b4b0d3255bfef95601890afd80709"* ]]
then
	print_ok "\t[10] Handle permission denied file (READ) \t\t [OK]"
else
	print_ko "\t[10] Handle permission denied file (READ) \t\t [KO]"
fi

# Permission denied (WRITE)

CMD=$($PIPEX_BIN /dev/null cat shasum /dev/permission-denied 2> ./.tmp/permission-denied2)
if [[ $(cat ./.tmp/permission-denied2 | grep -i "permission denied") && -z $CMD ]]
then
	print_ok "\t[11] Handle permission denied file (WRITE) \t\t [OK]"
else
	print_ko "\t[11] Handle permission denied file (WRITE) \t\t [KO]"
fi

print_color $BOLD$MAGENTA "[+] Handling commands : "

# Run basic command

# print_ko "\t[12] Run basic command \t\t\t\t\t [OK]"

# Handle command not found
CMD1=$($PIPEX_BIN /dev/null invalid1 invalid2 /dev/stdout 2> /dev/stdout)
if [[ $(echo $CMD1 | grep invalid1 | grep -i "command not found") && $(echo $CMD1 | grep invalid2 | grep -i "command not found") ]]
then
	print_ok "\t[13] Handle command not found \t\t\t\t [OK]"
else
	print_ko "\t[13] Handle command not found \t\t\t\t [KO]"
fi

# Handle non executable binary
cp $(where_is ls) .tmp/ls
cp $(where_is cat) .tmp/cat
chmod -x .tmp/ls
chmod -x .tmp/cat
CMD1=$($PIPEX_BIN /dev/null .tmp/ls .tmp/cat /dev/stdout 2> /dev/stdout)
if [[ $(echo $CMD1 | grep -i "permission denied") && $(echo $CMD1  | grep -i "permission denied") ]]
then
	print_ok "\t[14] Handle non executable binary \t\t\t [OK]"
else
	print_ko "\t[14] Handle non executable binary \t\t\t [KO]"
fi

# Handle commands with arguments
NULL=$($PIPEX_BIN /dev/zero "head -c 10" "base64 -i -" /dev/stdout 2> /dev/stdout)
if [[ $NULL == "AAAAAAAAAAAAAA==" ]]
then
	print_ok "\t[15] Handle commands with arguments \t\t\t [OK]"
else
	print_ko "\t[15] Handle commands with arguments \t\t\t [KO]"
fi

# Handle commands with single quotes
CMD=$($PIPEX_BIN /dev/null "echo 'Hello world'" shasum /dev/stdout 2> /dev/stdout)
if [[ $CMD == *"33ab5639bfd8e7b95eb1d8d0b87781d4ffea4d5d"* ]]
then
	print_ok "\t[16] Handle commands with single quotes \t\t [OK]"
else
	print_ko "\t[16] Handle commands with single quotes \t\t [KO]"
fi

# Handle commands with double quotes
CMD=$($PIPEX_BIN /dev/null 'echo "Hello world"' shasum /dev/stdout 2> /dev/stdout)
if [[ $CMD == *"33ab5639bfd8e7b95eb1d8d0b87781d4ffea4d5d"* ]]
then
	print_ok "\t[17] Handle commands with double quotes \t\t [OK]"
else
	print_ko "\t[17] Handle commands with double quotes \t\t [KO]"
fi

# Handle commands with double and single quotes
echo Hello world > ".tmp/hello w'orld"
CMD=$($PIPEX_BIN /dev/null "cat \".tmp/hello w'orld\"" shasum /dev/stdout 2> /dev/stdout)
if [[ $CMD == *"33ab5639bfd8e7b95eb1d8d0b87781d4ffea4d5d"* ]]
then
	print_ok "\t[18] Handle commands with double and single quotes \t [OK]"
else
	print_ko "\t[18] Handle commands with double and single quotes \t [KO]"
fi

# Program exits with the last command status code
CMD=$($PIPEX_BIN /dev/null true false /dev/null)
if [[ $? == 1 ]]
then
	print_ok "\t[19] Program exits with the last command status code \t [OK]"
else
	print_ko "\t[19] Program exits with the last command status code \t [KO]"
fi

# Program correctly pipes commands
# print_ko "\t[20] Program correctly pipes commands \t\t\t [OK]"

if [[ $1 = "bonus" ]]
then
	print_color $BOLD$MAGENTA "[+] Bonus : "

	print_ko "\t[21] Run multiple commands \t\t\t\t [OK]"
	print_ko "\t[22] Handle here_doc \t\t\t\t\t [OK]"
	print_ko "\t[23] Program exits with the last command status code \t [OK]"
fi

# rm -rf .tmp


## Check all exit codes
## Save errors to log.txt
## check if its bonus
