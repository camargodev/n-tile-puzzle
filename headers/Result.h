#ifndef RESULT_H
#define RESULT_H

class Result {

public:
  void startCountingTime();
  void stopCountingTime();
  void increaseExpandedNodes();
  void setOptimalSolutionLenght(int lenght);
  void printResult();
  void setInitialHeuristicValue(int hValue);
  void increaseTotalHeuristicValue(int hValue);
  void setTotalHeuristicValue(int hValue);

private:
  int expandedNodes = 0;
  int optimalSolutionLenght;
  float duration;
  float averageHeuristicValue;
  int initialHeuristicValue;

  clock_t startMoment;
  float totalHValue = 0;
};

#endif