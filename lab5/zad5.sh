#!/bin/bash

argc=$#

test $argc -ne 2 &&   echo "Wywolanie: $0 'fraza' dni" && exit 1

find . -type f -mtime -$2 | xargs grep -n $1