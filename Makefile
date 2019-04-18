all: Main.cpp manhattan state io algorithms 
	g++ -std=c++11 -O3 -o main Main.cpp ManhattanDistance.o StateManager.o Result.o InputReader.o BFS.o GreedyBestFirstSearch.o AStar.o IDFS.o


manhattan:
	g++ -std=c++11 -O3 -c src/ManhattanDistance.cpp

state:
	g++ -std=c++11 -O3 -c src/StateManager.cpp

io:
	g++ -std=c++11 -O3 -c src/InputReader.cpp
	g++ -std=c++11 -O3 -c src/Result.cpp

algorithms:
	g++ -std=c++11 -O3 -c src/algorithms/AStar.cpp
	g++ -std=c++11 -O3 -c src/algorithms/BFS.cpp
	g++ -std=c++11 -O3 -c src/algorithms/GreedyBestFirstSearch.cpp
	g++ -std=c++11 -O3 -c src/algorithms/IDFS.cpp

clean:
	rm -f *.o
	rm -f main
	