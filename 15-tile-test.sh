#!/bin/bash

while read p; do ./main -astar "$p"; done < input/15puzzle_instances.txt

