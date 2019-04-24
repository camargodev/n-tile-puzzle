#ifndef RESULT_H
#define RESULT_H

#include <fstream>
#include <string>

class Result {

public:
  void startCountingTime();
  void stopCountingTime();
  void increaseExpandedNodes();
  void increaseGeneratedNodes();
  void setOptimalSolutionLenght(int lenght);
  void printResult();
  void writeResult(std::string fileName);
  void setInitialHeuristicValue(int hValue);
  void increaseTotalHeuristicValue(int hValue);
  void setTotalHeuristicValue(int hValue);

private:
  int expandedNodes = 0;
  int generatedNodes = 0;
  int counter = 0;
  short optimalSolutionLenght;
  float duration;
  double averageHeuristicValue;
  short initialHeuristicValue;

  clock_t startMoment;
  double totalHValue = 0;
};

#endif