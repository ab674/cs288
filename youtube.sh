#!/bin/bash

function useroutput() {
    grep "pHg\" data-ytid\(.*\)</a>" $inputfile |
	while read line; do
	    user=`expr "$line" : ".*>\(.*\)</a>&nbsp;"`
	    if [ "$user" == "" ]
	    then
		user=`expr "$line" : ".*>\(.*\)</a></div><div"`
	    fi
	    echo "$user" >> userfile.txt;
	done
}

function viewsoutput(){
    grep "views" $inputfile |
	while read line; do
	    views=`expr "$line" : ".*<li>\(.*\) views</li>"`
	    views=${views//,/}
	    echo "$views" >> viewsfile.txt;
	done	
}

function timeoutput() {
    grep "\- Duration: \(.*\).</span>" $inputfile |
	while read line; do
	    time=`expr "$line" : ".*Duration: \(.*\).</span></h3>"`
	    echo "$time" >> timefile.txt;
	done
}

function idoutput() {
    grep "id=\"description-id-\(.*\)\">" $inputfile |
	while read line; do
	    id=`expr "$line" : ".*description-id-\(.*\)\"> -"`
	    echo "$id" >> idfile.txt;
	done
}

function titleoutput() {
    grep "title=\"\(.*\) aria-describedby" $inputfile |
	while read line; do
	    title=`expr "$line" : ".*title=\(.*\) aria-describedby"`
	    title=${title//,/}
	    echo "$title" >> titlefile.txt;
	done
}

function main() {
    wget -O index.html www.youtube.com/trending
    inputfile="index.html"
    userlist=();
    viewslist=();
    timelist=();
    idlist=();
    titlelist=();
    useroutput
    viewsoutput
    timeoutput
    idoutput
    titleoutput
    count=0;
    while read line; do
	userlist[count]=$line;
	((count++));
    done < userfile.txt
    count=0;
    while read line; do
	viewslist[count]=$line;
	((count++));
    done < viewsfile.txt
    count=0;
    while read line; do
	timelist[count]=$line;
	((count++));
    done < timefile.txt	
    count=0;
    while read line; do
	idlist[count]=$line;
	((count++));
    done < idfile.txt
    count=0;
    while read line; do
	titlelist[count]=$line;
	((count++));
    done < titlefile.txt
    for (( i=0; i<50; i++ )); do
	echo "${userlist[$i]};${viewslist[$i]};${timelist[$i]};${idlist[$i]};${titlelist[$i]}" >> output.csv
    done
}

main
