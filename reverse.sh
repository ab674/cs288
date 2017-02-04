#!/bin/bash

function reverse() {
    local parameter=$1
	files=(`ls $parameter`)
	reversefiles=()
	length=(${#files[@]}-1)
	for filename in ${files[@]}; do
	    reversefiles[$length]=$filename
	    ((length--))
	done
	for file in ${reversefiles[@]}; do
	    echo $file
	done
}

function main() {
    local parameter=$1
    reverse $parameter
}

main $1
