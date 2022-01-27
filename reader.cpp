#include "reader.h"
#include <iostream>
#include <sstream>

int Reader::readMain(Memory& dualMemory, Memory& singleMemory,
        const string& dualMainAddress, const string& singleMainAddress) {
    reader.open(dualMainAddress);
    if (!reader)
        return -1;
    while (!reader.eof()) {
        string part1;
        string part2;
        reader >> part1;
        reader >> part2;
        part1 = part1.append(" ");
        string expression = part1 + part2;
        int repeats;
        reader >> repeats;
        Entry newEntry = Entry(expression, repeats);
        dualMemory.push(newEntry);
    }
    reader.close();
    reader.open(singleMainAddress);
    if (!reader) {
        return -1;
    }
    int totalWords = 0;
    while (!reader.eof()) {
        string expression;
        reader >> expression;
        int repeats;
        reader >> repeats;
        totalWords += repeats;
        Entry newEntry = Entry(expression, repeats);
        singleMemory.push(newEntry);
    }
    reader.close();
    return totalWords;
}

int Reader::readSecondary(Memory& dualMemory, Memory& singleMemory, const string& secondaryAddress) {
    reader.open(secondaryAddress);
    if (!reader)
        return -1;
    int totalWords = 0;
    string sentence;
    string expression;
    string nextExpression;
    while (!reader.eof()) {
        getline(reader, sentence);
        istringstream iss(sentence);
        while (iss >> nextExpression) {
            if (!record(singleMemory, nextExpression))
                continue;
            totalWords += 1;
            if (!expression.empty()) {
                expression = expression.append(" ");
                record(dualMemory, expression + nextExpression);
            }
            expression = nextExpression;
        }
    }
    reader.close();
    return totalWords;
}

bool Reader::record(Memory& memory, string expression) {
    if (expression.at(0) >= 'a' && expression.at(0) <= 'z'
            || expression.at(0) >= '0' && expression.at(0) <= '9') {
        int position = memory.get(expression);
        if (position == -1) {
            memory.push(Entry(expression, 1));
        }
        else {
            memory.incrementEntryFrequency(position);
        }
        return true;
    }
    return false;
}
