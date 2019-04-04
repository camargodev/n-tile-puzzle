all: Main.cpp src/ManhattanDistance.cpp src/StateManager.cpp
	g++ -o main Main.cpp src/ManhattanDistance.cpp src/StateManager.cpp