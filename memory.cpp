#include "memory.h"

using namespace std;

Memory::Memory() {
    heapSize = 0;
}

void Memory::push(const Entry& newEntry) {
    heap.push_back(newEntry);
    ++heapSize;
    sortUp(heapSize - 1);
}

int Memory::get(const string& expression) {
    for (int i = 0; i < heapSize; ++i) {
        if (heap.at(i).getExpression() == expression) {
            return i;
        }
    }
    return -1;
}

int Memory::getFrequenciesOf(const string &expression) {
    for (int i = 0; i < heapSize; ++i) {
        if (heap.at(i).getExpression() == expression) {
            return heap.at(i).getRepeats();
        }
    }
    return 0;
}

vector<Entry> Memory::getHeap() {
    return heap;
}

void Memory::incrementEntryFrequency(int position) {
    int frequency = heap.at(position).getRepeats();
    heap.at(position).setRepeats(frequency + 1);
    sortDown(position);
    sortUp(position);
}

void Memory::deleteEntry(int position) {
    if (position == heapSize - 1)
        heap.pop_back();
    else {
        heap.at(position) = heap.back();
        --heapSize;
        heap.pop_back();
        sortUp(position);
        sortDown(position);
    }
}

void Memory::sortDown(int position) {
    int descendant1 = (position + 1) * 2 - 1;
    int descendant2 = (position + 1) * 2;
    int largest = position;
    if (descendant1 < heapSize && heap.at(descendant1).getRepeats() > heap.at(largest).getRepeats())
        largest = descendant1;
    if (descendant2 < heapSize && heap.at(descendant2).getRepeats() > heap.at(largest).getRepeats())
        largest = descendant2;
    if (largest != position) {
        Entry temp = heap.at(position);
        heap.at(position) = heap.at(largest);
        heap.at(largest) = temp;
        sortDown(largest);
    }
}

void Memory::sortUp(int position) {
    int ancestor = (position + 1) / 2 - 1;
    if (ancestor >= 0 && heap.at(position).getRepeats() > heap.at(ancestor).getRepeats()) {
        Entry temp = heap.at(ancestor);
        heap.at(ancestor) = heap.at(position);
        heap.at(position) = temp;
        sortUp(ancestor);
    }
}

int Memory::getMemorySize() const {
    return heapSize;
}
