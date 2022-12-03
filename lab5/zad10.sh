#!/bin/bash

argc=$#

test $argc -ne 2 &&   echo "Wywolanie: $0 katalog rozmiar" && exit 1

KATALOG=$1$"/"  #katalog w tkórm są wszystkie pliki

tempFolder=$KATALOG$"Temp".$(date +%H).$(date +%M).$(date +%S) #tworzy nzwę chwilowego folderu jeśli taki istnieje kończy program
if [ -e $tempFolder ]
then    
    echo "Folder already exist"
    exit 1
else
    mkdir $tempFolder
fi

for file in $KATALOG*.[pP][nN][gG];  #konfiguruje każdy plik .png
do
    newName=${file//[[:blank:]]/_} #zaminnia spacje lub tab na _
    fname=$(basename $newName)     #oddziela nazwe pliku od folderu
    fbname=${fname%.*}             #usuwa stare rozszerzenie
    newName=$fbname".png"          #dodaje nowe rozszerzenia .png
    
    tempPath=$tempFolder"/"$newName
    convert "$file" -resize $2 -quality 100 $tempPath #konweruje do wybranego rozmiaru
done

#tworzy nzwę chwilowego archiwum jeśli taki istnieje kończy program
archiveFolder=$KATALOG"Archive".$(date +%H).$(date +%M).$(date +%S)."tar" 
if [ -e $archiveFolder ]
then                                
    echo "Archive already exist"
    echo "Deleting files"
    rm -r $tempFolder
    exit 1
else
    tar -cf $archiveFolder $tempFolder 
    rm -r $tempFolder
    echo "Archive name: $archiveFolder"
    echo "Done!"
fi


