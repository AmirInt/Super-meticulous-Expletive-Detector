#include "entry.h"
#include <string>

Entry::Entry(string expression) {
    this -> expression = move(expression);
    repeats = 0;
}

Entry::Entry(string expression, int repeats) {
    this -> expression = move(expression);
    this -> repeats = repeats;
}

string Entry::getExpression() const {
    return expression;
}

int Entry::getRepeats() const {
    return repeats;
}

void Entry::setRepeats(int newRepeats) {
    this -> repeats = newRepeats;
}
