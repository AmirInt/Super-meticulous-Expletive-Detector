#ifndef SUPER_METICULOUS_EXPLETIVE_DETECTOR_READER_H
#define SUPER_METICULOUS_EXPLETIVE_DETECTOR_READER_H

#include "memory.h"
#include <fstream>
#include <string>

using namespace std;

class Reader {

private:
    ifstream reader;

public:
    int readMain(Memory& dualMemory, Memory& singleMemory, const string& dualMainAddress, const string& singleMainAddress);
    int readSecondary(Memory& dualMemory, Memory& singleMemory, const string& secondaryAddress);

private:
    static bool record(Memory& memory, string expression);
};

#endif //SUPER_METICULOUS_EXPLETIVE_DETECTOR_READER_H
