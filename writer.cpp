#include "writer.h"

bool Writer::write(Memory dualMemory, Memory singleMemory,
        const string& dualMainAddress, const string& singleMainAddress) {
    writer.open(dualMainAddress);
    if (!writer)
        return false;
    for (const Entry& record: dualMemory.getHeap()) {
        writer << record.getExpression() << " " << record.getRepeats() << endl;
    }
    writer.close();writer.open(singleMainAddress);
    if (!writer)
        return false;
    for (const Entry& record: singleMemory.getHeap()) {
        writer << record.getExpression() << " " << record.getRepeats() << endl;
    }
    writer.close();
    return true;
}
