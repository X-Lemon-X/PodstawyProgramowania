#!/bin/bash

# skrypt sprawdzajacy okresowo, czy jest zalogowany uzytkownik o podanym loginie
# wywolanie:  czy_jest login_uzytkownika

argc=$#            #dane, by pokazac sposob tworzenia zmiennych
                   #wokol operatora przypisania = nie moze byc zadnej spacji!!!

# sprawdzamy, czy podano wymagany argument 
if [ $argc -ne 2 ]; then  # [ ] - alternatywny sposob wywolywania polecenia test
                     # operator != porowna argumenty traktujac je jako napisy!!!
    echo "Wywolanie: $0 login_uzytkownika e-mail"
    exit 1
fi

#jeśli użytownika nie ma wyłącza skrypt bo i tak zostanie wywołany za jakiś ustalonuy czas
if [ `who |grep -sw $1 |wc -l` -eq 0 ];
then 
    exit 1
fi

# uzytkownik pojawil sie - poinformuj
tempFolder=$"Email_Login".$(date +%H).$(date +%M).$(date +%S) 

while [ -e "$tempFolder" ];
do
    tempFolder=$"Email".$(date +%H).$(date +%M).$(date +%S)
    sleep 1s
done
touch $tempFolder

#e-mail z którego będzie wysyłał oczywścei żeby ten skryot działą musi być skonfigorowany /etc/ssmtp/ssmtp.conf i zainstalowany ssmtp  
echo "From: vbmech1234@outlook.com" >> $tempFolder
echo "Subject: zalogowany=$1 " >> $tempFolder

ssmtp -v $2 < $tempFolder  #wysyła e-maila 

rm $tempFolder #usuwa plik z e-mailem


#do konfukuracji crontab -e trzeba wsatwić
# 5 * * * * /home/lemonx/IT/podstawyProgramowania/lab5/zad12.sh lemonx dodpat02@gmail.com &