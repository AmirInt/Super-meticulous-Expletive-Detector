#ifndef SUPER_METICULOUS_EXPLETIVE_DETECTOR_MEMORY_H
#define SUPER_METICULOUS_EXPLETIVE_DETECTOR_MEMORY_H

#include "entry.h"
#include <vector>

using namespace std;

class Memory {

private:
    vector<Entry> heap;
    int heapSize;

public:
    Memory();
    void push(const Entry& newEntry);
    int get(const string &expression);
    int getFrequenciesOf(const string &expression);
    vector<Entry> getHeap();
    void incrementEntryFrequency(int position);
    void deleteEntry(int position);
    void sortDown(int position);
    void sortUp(int position);
    [[nodiscard]] int getMemorySize() const;
};

#endif //SUPER_METICULOUS_EXPLETIVE_DETECTOR_MEMORY_H
