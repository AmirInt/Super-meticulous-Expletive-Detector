#ifndef SUPER_METICULOUS_EXPLETIVE_DETECTOR_WRITER_H
#define SUPER_METICULOUS_EXPLETIVE_DETECTOR_WRITER_H

#include "memory.h"
#include <fstream>
#include <string>

using namespace std;

class Writer {

private:
    ofstream writer;

public:
    bool write(Memory dualMemory, Memory singleMemory, const string& dualMainAddress, const string& singleMainAddress);
};

#endif //SUPER_METICULOUS_EXPLETIVE_DETECTOR_WRITER_H
