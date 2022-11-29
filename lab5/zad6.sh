#!/bin/bash

argc=$#]

test $argc -ne 1 &&   echo "Wywolanie: $0 'nazwa pliku'" && exit 1

find -type f -name '$1' | xargs ls -tlh
