#!/bin/bash

argc=$#

test $argc -ne 2 &&   echo "Wywolanie: $0 plik.pdf strona" && exit 1

echo "Wybrany plik to: $1"
echo "Wybrana strona w plik to: $2"

pdftoppm -singlefile -f $2 -jpeg -r 300 $1 out 