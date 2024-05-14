#!/bin/sh

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

base_command="cat"
s21_command="./s21_cat"

# can be changed
flags="-b -e -n -s -t -E -T"

# can be changed
file_path_one="files/first_file.txt"
file_path_two="files/second_file.txt"
file_path_three="files/third_file.txt"
file_path_four="files/test_hzciMX.txt"

# can be changed
files="$file_path_one $file_path_two $file_path_three $file_path_four"

every_check=0
approved=0
wrong=0

for file in $files; do

    for flag in $flags; do

        echo "Parameters for the test are: $flag $file"
    
        current_base_output=$($base_command $file $flag)
        s21_base_output=$($s21_command $file $flag)

        if [ "$current_base_output" = "$s21_base_output" ]; then
            approved=$((approved + 1))
            echo "${GREEN}MATCHES${NC}"
        else
            echo "${RED}DO NOT MATCH${NC}"
            wrong=$((wrong + 1))
        fi

        every_check=$((every_check + 1))

    done

done

echo "Tests are done"
echo "Amount of tests: $every_check"
echo "           GOOD: $approved"
echo "            BAD: $wrong"