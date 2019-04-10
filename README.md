# Algorithms to solve N-tile-puzzle  

Implementations of BFS, Greedy-BFS, A*, Iterative Deepening and IDA* for 3 and 4 tile puzzles.

## Compiling it

Clone and run make.

## Running it

Run ```./main``` passing the algorithm you want to execute. Options are:
    * ```-bfs``` for BFS
    * ```-gbfs``` for Greedy-BFS
    * ```-astar``` for A*
    * ```-idfs``` for Iterative Deepening
    * ```-idastar``` for IDA*

Also pass a set of initial entries with at least 1 element. Examples are:
    * ```0 1 2 3 4 5 6 7 8``` (1 element)
    * ```1 4 0 5 9 7 2 3 6, 8 7 6 5 4 3 2 1``` (2 elements)

## Running it

For input ```./main -astar 8 3 5 7 2 6 0 4 1, 3 0 8 7 5 2 1 6 4, 5 4 6 3 2 7 0 1 8```, output should be something like:
```
330,22,0.004757,10.545455,18
197,19,0.002806,9.517767,13
3015,26,0.036673,10.768491,14
```
where values are, in order, the number of expanded nodes, the length of the optimal solution, the duration, average heuristic value and the heuristic value for the initial state.