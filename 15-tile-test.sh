#!/bin/bash

ulimit -v 8000000
counter=0
while read p; 
do 
    counter=$[$counter+1]
    printf "\n$counter: "
    ./main -astar "$p"; 
done < input/15puzzle_instances.txt

