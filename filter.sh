#!/bin/bash

function filter() {
    local directory=$1
    local average=$2
    for item in $(ls $directory); do
	local size=$(du -s "$directory/$item" | awk '{print $1}')
	if (( $size > $average )); then
	    echo $item
	fi
    done
}

function average() {
    local directory=$1
    local totalsize=0
    local filecount=0
    for item in $(ls $directory); do
	local size=$(du -s "$directory/$item" | awk '{print $1}')
	((totalsize+=size))
	((filecount++))
    done
    local average=$(($totalsize/$filecount))
    filter $directory $average
}

function main() {
    average $1
}

main $1
