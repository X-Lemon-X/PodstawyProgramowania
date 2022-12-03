#!/bin/bash



# w katalogu domowym usuwamy ewentualnie istniejący katalog pomoczniczy Temp
# i tworzymy nowy, pusty

temp=$"Temp".$(date +%H).$(date +%M).$(date +%S)

test -d $temp && rm -rf $temp
mkdir $temp

fileIn="$temp/site.txt"
fileOut="$temp/site2.txt"

# pobieramy stronkę do pliky site.txt
wget -q -O $fileIn en.wikiquote.org/wiki/Wikiquote:Quote_of_the_Day 

#usy=uwamy wszystko czego nie chcemy
cat "$fileIn" | grep '^<dd>*'| sed 's/~ <a.*//' | sed 's/~ <i><a.*//' | sed 's/<dd>....//' > "$fileOut" 



length=$(wc -l < $fileOut)
declare -i num
declare -i count
count=0
num=$[ $RANDOM % $length + 1 ]

while read -r line;
do
    if [ $count == $num ]
    then
        echo -e "$line\n"
    fi
    count+=1
done <$fileOut

rm -rf $temp