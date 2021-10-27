#include "../Emulator/intel8080.h"
#include "i8080.h"

using namespace std;

void intel8080::printStats() {
    cout << "My CPU" << endl;
    cout << "Registers" << endl;
    cout << "B: " << (int)B << " C: " << (int)C << " D: " << (int)D << endl;
    cout << "E: " << (int)E << " H: " << (int)H << " L: " << (int)L << " A: " << (int)A << endl;
    cout << "SP: " << (int)SP << " PC: " << (int)PC << endl;

    cout << "Flags" << endl;
    cout << "Sign: " << getSign() << " Zero: " << getZero() << " Parity: " << getParity() << endl;
    cout << "Carry: " << getCarry() << " Auxiliary Carry: " << getAuxCarry() << endl;
    cout << "Halt: " << halt << endl;
    cout << "Error msg: " << error << endl;
    cout << endl;
}

void printi8080Stats(struct i8080 *cpu) {
    cout << "Test CPU" << endl;
    cout << "Registers" << endl;
    cout << "B: " << cpu->B << " C: " << cpu->C << " D: " << cpu->D << endl;
    cout << "E: " << cpu->E << " H: " << cpu->H << " L: " << cpu->L << " A: " << cpu->A << endl;
    cout << "SP: " << cpu->SP << " PC: " << cpu->PC << endl;

    cout << "Flags" << endl;
    cout << "Sign: " << i8080_get_flag(cpu, FLAG_S) << " Zero: " << i8080_get_flag(cpu, FLAG_Z) << " Parity: " << i8080_get_flag(cpu, FLAG_P) << endl;
    cout << "Carry: " << i8080_get_flag(cpu, FLAG_C) << " Auxiliary Carry: " << i8080_get_flag(cpu, FLAG_A) << endl;
    cout << "Halt: " << cpu->halted << endl;
    cout << endl;
}

bool intel8080::compareCPU(i8080* testCpu) {
    bool success = true;
    if (B != testCpu->B) {
        cout << "B registers are different" << endl;
        cout << "MyCpu:\t" << (int)B << "\tTestCpu:\t" << testCpu->B << endl;
        success = false;
    }
    if (C != testCpu->C) {
        cout << "C registers are different" << endl;
        cout << "MyCpu:\t" << (int)C << "\tTestCpu:\t" << testCpu->C << endl;
        success = false;
    }
    if (D != testCpu->D) {
        cout << "D registers are different" << endl;
        cout << "MyCpu:\t" << (int)D << "\tTestCpu:\t" << testCpu->D << endl;
        success = false;
    }
    if (E != testCpu->E) {
        cout << "E registers are different" << endl;
        cout << "MyCpu:\t" << (int)E << "\tTestCpu:\t" << testCpu->E << endl;
        success = false;
    }
    if (H != testCpu->H) {
        cout << "H registers are different" << endl;
        cout << "MyCpu:\t" << (int)H << "\tTestCpu:\t" << testCpu->H << endl;
        success = false;
    }
    if (L != testCpu->L) {
        cout << "L registers are different" << endl;
        cout << "MyCpu:\t" << (int)L << "\tTestCpu:\t" << testCpu->L << endl;
        success = false;
    }
    if (A != testCpu->A) {
        cout << "A registers are different" << endl;
        cout << "MyCpu:\t" << (int)A << "\tTestCpu:\t" << testCpu->A << endl;
        success = false;
    }
    if (SP != testCpu->SP) {
        cout << "SP registers are different" << endl;
        cout << "MyCpu:\t" << SP << "\tTestCpu:\t" << testCpu->SP << endl;
        success = false;
    }
    if (PC != testCpu->PC) {
        cout << "PC registers are different" << endl;
        cout << "MyCpu:\t" << PC << "\tTestCpu:\t" << testCpu->PC << endl;
        success = false;
    }
    if (flags != testCpu->flags) {
        cout << "Flags are different" << endl;
        cout << "MyCpu:\t" << (int)flags << "\tTestCpu:\t" << testCpu->flags << endl;
        cout << "Sign flag" << endl;
        cout << "MyCpu:\t" << (int)getSign() << "\tTestCpu:\t" << i8080_get_flag(testCpu, FLAG_S) << endl;
        cout << "Zero flag" << endl;
        cout << "MyCpu:\t" << (int)getZero() << "\tTestCpu:\t" << i8080_get_flag(testCpu, FLAG_Z) << endl;
        cout << "Auxilliary Carry flag" << endl;
        cout << "MyCpu:\t" << (int)getAuxCarry() << "\tTestCpu:\t" << i8080_get_flag(testCpu, FLAG_A) << endl;
        cout << "Parity flag" << endl;
        cout << "MyCpu:\t" << (int)getParity() << "\tTestCpu:\t" << i8080_get_flag(testCpu, FLAG_P) << endl;
        cout << "Carry flag" << endl;
        cout << "MyCpu:\t" << (int)getCarry() << "\tTestCpu:\t" << i8080_get_flag(testCpu, FLAG_C) << endl;
        success = false;
    }
    if (testCpu->halted != halt) {
        cout << "Halt Status is different" << endl;
    }
    return success;
}

void testCPU(byte* program, int programSize) {

    struct i8080 *testCpu = reinterpret_cast<struct i8080*>(malloc(sizeof(struct i8080)));

    testCpu->memory = reinterpret_cast<char*>(malloc(sizeof(char) * programSize));
    testCpu->memsize = programSize;

    i8080_reset(testCpu);
    for (int i=0; i<programSize; i++) {
        i8080_write_byte(testCpu, i, program[i]);
        i8080_step(testCpu);
    }

    intel8080* myCpu = new intel8080(program, programSize);

    bool success = true;
    for (int i=0; i<programSize; i++) {
        if (testCpu->halted) {
            break;
        }
        i8080_step(testCpu);
        myCpu->step();
        if (!myCpu->compareCPU(testCpu)) {
            success = false;
            break;
        }
    }


    if (success) {
        cout << "CPU meets the standard" << endl;
    } else {
        cout << "CPU fails to meet the standard" << endl;
    }

    delete testCpu;
    delete myCpu;

}


int main() {

    byte program[] = {0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b10111000};

    int programSize = *(&program + 1) - program;

    testCPU(program, programSize);
    return 0;
}