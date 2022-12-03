#!/bin/bash


argc=$#

test $argc -ne 2 &&   echo "Wywolanie: $0 e-mail serwer" && exit 1

#usuwa narmalne wyjście z komendy ping przekerowujac strumien stdout na puste
#oraz przekierowuje strumień stderr na głuwne wyjście

ping -c 1 -q  $2 >/dev/null 2>&1

#tworzy nzwę chwilowego pliku zawierającego strukturę emaila jeśli taki istnieje kończy program
tempFolder=$"Email".$(date +%H).$(date +%M).$(date +%S) 

while [ -ne %tempFolder ]
do
    tempFolder=$"Email".$(date +%H).$(date +%M).$(date +%S)
    sleep 1s
done
touch $tempFolder

#e-mail z którego będzie wysyłał oczywścei żeby ten skryot działą musi być skonfigorowany /etc/ssmtp/ssmtp.conf i zainstalowany ssmtp  
echo "From: vbmech1234@outlook.com" >> $tempFolder

if [ $? -ne 0 ]; #zczytuje z głównego wejścia liczbe z komendy pingu
then 
    echo "Subject: host=$2 Offline" >> $tempFolder
else    
    echo "Subject:  host=$2 Online" >> $tempFolder
fi

ssmtp $1 < $tempFolder  #wysyła e-maila 

rm $tempFolder #usuwa plik z e-mailem
 