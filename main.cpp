#include "classifier.h"
#include <iostream>

using namespace std;

int main() {

    Classifier classifier = Classifier();
    if (!classifier.readDatabase())
        cout << "Couldn't read the database" << endl;
    else {
        classifier.eliminateTheUseless(0, 0);
        string input;
        cout << "Enter comment:" << endl;
        getline(cin, input);
        while (input != "!q") {
            cout << classifier.classify(input) << endl;
            getline(cin, input);
        }
    }
    return 0;
}
