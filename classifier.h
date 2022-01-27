#ifndef SUPER_METICULOUS_EXPLETIVE_DETECTOR_CLASSIFIER_H
#define SUPER_METICULOUS_EXPLETIVE_DETECTOR_CLASSIFIER_H

#include "reader.h"
#include "writer.h"
#include "memory.h"

using namespace std;

class Classifier {

private:
    Memory posSingleMemory;
    Memory posDualMemory;
    Memory negSingleMemory;
    Memory negDualMemory;
    Reader reader;
    Writer writer;
    int totalPositiveWords{};
    int totalNegativeWords{};
    const double lambda1 = 0.4, lambda2 = 0.3, lambda3 = 0.3, epsilon = 0.1;

public:
    Classifier();
    bool readDatabase();
    string classify(const string& sentence);
    void eliminateTheUseless(int head, int tail);

private:
    bool writeResult(Memory dualMemory, Memory singleMemory,
                     const string& dualMainAddress, const string& singleMainAddress);
    double posProbabilityOf(const string& expression);
    double posProbabilityOf(const string& expression, const string& nextExpression);
    double negProbabilityOf(const string& expression);
    double negProbabilityOf(const string& expression, const string& nextExpression);

};

#endif //SUPER_METICULOUS_EXPLETIVE_DETECTOR_CLASSIFIER_H
