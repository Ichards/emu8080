#include <iostream>
#include "intel8080.h"

using namespace std;

void intel8080::printStats() {
    cout << "Registers" << endl;
    cout << "B: " << (int)B << " C: " << (int)C << " D: " << (int)D << endl;
    cout << "E: " << (int)E << " H: " << (int)H << " L: " << (int)L << " A: " << (int)A << endl;
    cout << "SP: " << (int)SP << " PC: " << (int)PC << endl;

    cout << "Flags" << endl;
    cout << "Sign: " << getSign() << " Zero: " << getZero() << " Parity: " << getParity() << endl;
    cout << "Carry: " << getCarry() << " Auxiliary Carry: " << getAuxCarry() << endl;
}

int main() {
    byte memory[] = {0x04, 0x90};
    int memorySize = *(&memory + 1) - memory; // found a dope way of getting an array size
    
    intel8080* cpu = new intel8080(memory, memorySize);
    cpu->printStats();
    cout << endl;
    cout << "Running cpu" << endl;
    cpu->run();
    cout << "Finished running" << endl;
    cout << endl;
    cpu->printStats();

    delete cpu;

    return 0;
}