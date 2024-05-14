#!/bin/sh

output_log="log.txt"

output=$(cat files/first_file.txt -n)

echo $output >> "$output_log"