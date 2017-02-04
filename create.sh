#!/bin/bash

function breadthfirst() {
    local depth=$1
    local breadth=$2
    local directory=$3
    if (( $depth <= 0 )); then
	return
    fi
    ((depth--))
    local counter=$breadth
    while (( $counter > 0 )); do
	mkdir $directory/$counter
	((counter--))
    done
    let counter=$breadth
    while (( $counter > 0 )); do
	breadthfirst $depth $breadth $directory/$counter
	((counter--))
    done
}

function depthfirst() {
    local depth=$1
    local breadth=$2
    local directory=$3
    if (( $depth <= 0 )); then
	return
    fi
    ((depth--))
    local counter=$breadth
    while (( $counter > 0 )); do
	mkdir $directory/$counter
	depthfirst $depth $breadth $$directory/$counter
	((counter--))
    done
}

function main() {
    if (( $4=="breadth" )); then
	breadthfirst $1 $2 $3
    elif (( $4=="depth" )); then
	depthfirst $1 $2 $3
    fi
}

main $1 $2 $3 $4
