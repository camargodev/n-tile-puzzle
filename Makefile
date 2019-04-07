all: Main.cpp src/ManhattanDistance.cpp src/StateManager.cpp src/Node.cpp src/Result.cpp
	g++ -o main Main.cpp src/ManhattanDistance.cpp src/StateManager.cpp src/Node.cpp src/Result.cpp