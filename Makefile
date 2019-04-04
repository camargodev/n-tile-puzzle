all: Main.cpp src/Position.cpp src/ManhattanDistance.cpp src/StateManager.cpp
	g++ -o main Main.cpp src/Position.cpp src/ManhattanDistance.cpp src/StateManager.cpp