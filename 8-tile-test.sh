#!/bin/bash

while read p; do ./main -astar "$p"; done < input/8puzzle_instances.txt
while read p; do ./main -bfs "$p"; done < input/8puzzle_instances.txt
while read p; do ./main -gbfs "$p"; done < input/8puzzle_instances.txt
while read p; do ./main -idastar "$p"; done < input/8puzzle_instances.txt
while read p; do ./main -idfs "$p"; done < input/8puzzle_instances.txt

