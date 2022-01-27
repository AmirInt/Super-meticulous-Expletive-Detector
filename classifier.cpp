#include "classifier.h"
#include <sstream>
#include <iostream>
#include <cmath>

Classifier::Classifier() {
    posSingleMemory = Memory();
    posDualMemory = Memory();
    negSingleMemory = Memory();
    posDualMemory = Memory();
}

bool Classifier::readDatabase() {
    totalPositiveWords = reader.readMain(posDualMemory, posSingleMemory,
            "Database\\posDualMemory.txt", "Database\\posSingleMemory.txt");
    if (totalPositiveWords == -1) {
        totalPositiveWords = reader.readSecondary(posDualMemory, posSingleMemory,
                             "Database\\rt-polarity-positive.txt");
        if (totalPositiveWords == -1)
            return false;
        writeResult(posDualMemory, posSingleMemory,
                    "Database\\posDualMemory.txt", "Database\\posSingleMemory.txt");
    }
    totalNegativeWords = reader.readMain(negDualMemory, negSingleMemory,
            "Database\\negDualMemory.txt", "Database\\negSingleMemory.txt");
    if (totalNegativeWords == -1) {
        totalNegativeWords = reader.readSecondary(negDualMemory, negSingleMemory,
                             "Database\\rt-polarity-negative.txt");
        if (totalNegativeWords == -1)
            return false;
        writeResult(negDualMemory, negSingleMemory,
                    "Database\\negDualMemory.txt", "Database\\negSingleMemory.txt");
    }
    cout << posDualMemory.getMemorySize() << endl;
    cout << posSingleMemory.getMemorySize() << endl;
    cout << negDualMemory.getMemorySize() << endl;
    cout << negSingleMemory.getMemorySize() << endl;
    return true;
}

bool Classifier::writeResult(Memory dualMemory, Memory singleMemory,
                             const string& dualMainAddress, const string& singleMainAddress) {
    return writer.write(move(dualMemory), move(singleMemory), dualMainAddress, singleMainAddress);
}

string Classifier::classify(const string& sentence) {
    istringstream iss(sentence);
    string expression;
    string nextExpression;
    double positiveProbability = 0;
    double negativeProbability = 0;
    while (iss >> nextExpression) {
        if (nextExpression.at(0) >= 'a' && nextExpression.at(0) <= 'z'
                || nextExpression.at(0) >= '0' && nextExpression.at(0) <= '9') {
            if (expression.empty()) {
                positiveProbability += log10(posProbabilityOf(nextExpression));
                negativeProbability += log10(negProbabilityOf(nextExpression));
            } else {
                positiveProbability += log10(lambda1 * posProbabilityOf(expression, nextExpression) +
                                             lambda2 * posProbabilityOf(nextExpression) +
                                             lambda3 * epsilon);
                negativeProbability += log10(lambda1 * negProbabilityOf(expression, nextExpression) +
                                             lambda2 * negProbabilityOf(nextExpression) +
                                             lambda3 * epsilon);
            }
            expression = nextExpression;
        }
    }
    cout << positiveProbability << " vs. " << negativeProbability << endl;
    if (positiveProbability > negativeProbability)
        return "not filter this";
    return "filter this";
}

double Classifier::posProbabilityOf(const string& expression) {
    return (double)posSingleMemory.getFrequenciesOf(expression) / totalPositiveWords;
}

double Classifier::posProbabilityOf(const string& expression, const string& nextExpression) {
    if (posSingleMemory.getFrequenciesOf(expression) == 0)
        return 0;
    return (double)posDualMemory.getFrequenciesOf(expression + " " + nextExpression) /
           posSingleMemory.getFrequenciesOf(expression);
}

double Classifier::negProbabilityOf(const string& expression) {
    return (double)negSingleMemory.getFrequenciesOf(expression) / totalNegativeWords;
}

double Classifier::negProbabilityOf(const string& expression, const string& nextExpression) {
    if (negSingleMemory.getFrequenciesOf(expression) == 0)
        return 0;
    return (double)negDualMemory.getFrequenciesOf(expression + " " + nextExpression) /
           negSingleMemory.getFrequenciesOf(expression);
}

void Classifier::eliminateTheUseless(int head, int tail) {
    for (int i = 0; i < head; ++i) {
        posSingleMemory.deleteEntry(0);
        negSingleMemory.deleteEntry(0);
    }
    for (int i = 0; i < tail; ++i) {
        posSingleMemory.deleteEntry(posSingleMemory.getMemorySize());
        negSingleMemory.deleteEntry(negSingleMemory.getMemorySize());
    }
}
