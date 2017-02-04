#!/bin/bash

alphabet=(a b c d e f g h i j k l m n o p q r s t u v w x y z)
counts=()
for letter in ${alphabet[@]}; do
    newcount=0
    for filename in /usr/bin/*; do
	if [[ "${filename:9:1}" ==  "$letter" ]]
	then
	    ((newcount++))
        else
	    continue
	fi
    done
    counts+=($newcount)
    echo $letter $newcount
done
