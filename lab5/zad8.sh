#!/bin/bash

argc=$#

test $argc -ne 3 &&   echo "Wywolanie: $0 'plik.pdf' strona" && exit 1

echo "Wybrany plik to $1"
echo "Wybrana strona w plik to: $2"

STRONY=$(12)

if[STREONY]
then 
    pdftoppm -jpeg -r 300 $1 out 