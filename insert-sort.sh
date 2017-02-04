#!/bin/bash

list=()
for item in $@; do
    pointer=0
    for value in ${list[@]}; do
	if [ $item -lt $value ]; then
	    placeholder=${list[$pointer]}
	    list[$pointer]=$item
	    item=$placeholder
	fi
	let pointer++
    done
    list+=($item)
done

echo ${list[@]}
