#ifndef SUPER_METICULOUS_EXPLETIVE_DETECTOR_ENTRY_H
#define SUPER_METICULOUS_EXPLETIVE_DETECTOR_ENTRY_H

#include <string>

using namespace std;

class Entry {

private:
    string expression;
    int repeats;

public:
    explicit Entry(string expression);
    explicit Entry(string expression, int repeats);
    [[nodiscard]] string getExpression() const;
    [[nodiscard]] int getRepeats() const;
    void setRepeats(int newRepeats);
};

#endif //SUPER_METICULOUS_EXPLETIVE_DETECTOR_ENTRY_H
