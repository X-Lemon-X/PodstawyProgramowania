#!/bin/bash


argc=$#

test $argc -ne 1 &&   echo "Wywolanie: $0 'pattern_file' " && exit 1

find . -type f -name '*.txt' | xargs rm