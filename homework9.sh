#!/bin/bash

function main() {
  datetime = $1
  curl -o $datetime.html http://www.wsj.com/mdc/public/page/2_3021-activnyse-actives.html
  `python homework9.py $datetime.html`
  `rm $datetime.*`
}

counter = 0
while [[ $counter -le 60 ]]; do
  datetime = `(datetime + "%Y-%m-%d-%H-%M-%s")`
  main $datetime
  sleep 3
  counter = `expr $counter + 1`
done
