#!/bin/sh

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

base_command="cat"
s21_command="./s21_cat"

flags="-b -e -n -s -t -E -T"

file_path_one="files/first_file.txt"
file_path_two="files/second_file.txt"
file_path_three="files/third_file.txt"
file_path_four="files/test_hzciMX.txt"

files="$file_path_one $file_path_two $file_path_three $file_path_four"

for file in $files; do

    for flag in $flags; do
    
        current_base_output=$($base_command $file $flag)
        s21_base_output=$($s21_command $file $flag)

        if [ "$current_base_output" = "$s21_base_output" ]; then
            echo "${GREEN}MATCHES${NC}"
        else
            echo "${RED}DO NOT MATCH${NC}"
        fi

    done

done