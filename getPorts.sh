#!/bin/bash

echo "" > ~/awailablePorts.txt
str="/dev/ttyUSB"
count=0
i=0
while [ $count -lt 3 ]
do 
        full_str="$str$i"
        echo "$full_str"
        if [ -c "$full_str" ]; then
                echo "found $full_str"
                echo "$full_str" >> ~/awailablePorts.txt
                echo "\n " >> ~/awailablePorts.txt
                (( count++ ))
        fi
        (( i++ ))
done
