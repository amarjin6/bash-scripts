#!/bin/bash
errFile="/tmp/${0##*/}.err"
if [ $# \< 1 ]
then
     echo "$("$0"): Too few arguments" 1>"$errFile"
     while IFS= read -r line; do echo "$line" >&2; done < "$errFile"
     exit 1
fi
if [ $1 -gt "-1" ] && [ $1 -lt "1001" ]
then
     for pid in $(pgrep -U "$(id -nu "$1")")
         do
           echo "$pid $(ls /proc/$pid/fd/ 2>> $errFile| wc -l)" 2>> "$errFile"
         done
	while IFS= read -r line; do  echo "$(basename "$0"): $line" >&2; done < "$errFile"
else
     echo "$(basename "$0"): Invalid user uid: $1" 1>"$errFile"
     while IFS= read -r line; do echo "$line" >&2; done < "$errFile"
     exit 1
fi
rm $errFile
exit 0
