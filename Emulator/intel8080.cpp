#include "intel8080.h"



intel8080::intel8080(byte* p_memory, int p_memorySize)
:
halt(false),
A(0), B(0), C(0), D(0), E(0), H(0), L(0), SP(0), PC(0),
flags(0b00000010)
{
    memory = p_memory;
    memorySize = p_memorySize;
}

intel8080::~intel8080() {
}

void intel8080::execute(byte opCode) {

    switch (opCode) {
        // this is where the fun begins

        // CARRY BIT
        // CMC - carry = !carry
        case 0b00111111: setCarry(!getCarry()); break;
        // STC - carry = 1
        case 0b00110111: setCarry(true); break;

        // SINGLE REGISTER INSTRUCTIONS
        // INR - Increment Register or Memory
        // register B
        case 0b00000100: INR(B); break;
        // register C
        case 0b00001100: INR(C); break;
        // register D
        case 0b00010100: INR(D); break;
        // register E
        case 0b00011100: INR(E); break;
        // register H
        case 0b00100100: INR(H); break;
        // register L
        case 0b00101100: INR(L); break;
        // register M (address in HL)
        case 0b00110100: INR(getM()); break;
        // register A
        case 0b00111100: INR(A); break;

        // DCR - Decrement Register or Memory
        // register B
        case 0b00000101: DCR(B); break;
        // register C
        case 0b00001101: DCR(C); break;
        // register D
        case 0b00010101: DCR(D); break;
        // register E
        case 0b00011101: DCR(E); break;
        // register H
        case 0b00100101: DCR(H); break;
        // register L
        case 0b00101101: DCR(L); break;
        // register M (address in HL)
        case 0b00110101: DCR(getM()); break;
        // register A
        case 0b00111101: DCR(A); break;

        // CMA - Complement Accumulator
        case 0b00101111: A = ~A; break;

        // DAA - Decimal Adjust Accumulator
        case 0b00100111: 
            if ( (A & 0x0F) > 9 || getAuxCarry()) {
                setAuxCarry(A, 6);
                A += 6;
                setSZP(A);
            }
            if ( (A & 0xF0) > 9 || getCarry()) {
                setCarry(A, 6);
                A += 0x60;
                setSZP(A);
            }
            break;

        // NOP - No Operation
        case 0b00000000: break;

        // DATA TRANSFER INSTRUCTIONS
        // MOV - Move data from source register to destination register
        // B destination
        // B source
        case 0b01000000: MOV(B, B); break;
        // C source
        case 0b01000001: MOV(B, C); break;
        // D source
        case 0b01000010: MOV(B, D); break;
        // E source
        case 0b01000011: MOV(B, E); break;
        // H source
        case 0b01000100: MOV(B, H); break;
        // L source
        case 0b01000101: MOV(B, L); break;
        // M source
        case 0b01000110: MOV(B, getM()); break;
        // A source
        case 0b01000111: MOV(B, A); break;
        // C destination
        // B source
        case 0b01001000: MOV(C, B); break;
        // C source
        case 0b01001001: MOV(C, C); break;
        // D source
        case 0b01001010: MOV(C, D); break;
        // E source
        case 0b01001011: MOV(C, E); break;
        // H source
        case 0b01001100: MOV(C, H); break;
        // L source
        case 0b01001101: MOV(C, L); break;
        // M source
        case 0b01001110: MOV(C, getM()); break;
        // A source
        case 0b01001111: MOV(C, A); break;
        // D destination
        // B source
        case 0b01010000: MOV(D, B); break;
        // C source
        case 0b01010001: MOV(D, C); break;
        // D source
        case 0b01010010: MOV(D, D); break;
        // E source
        case 0b01010011: MOV(D, E); break;
        // H source
        case 0b01010100: MOV(D, H); break;
        // L source
        case 0b01010101: MOV(D, L); break;
        // M source
        case 0b01010110: MOV(D, getM()); break;
        // A source
        case 0b01010111: MOV(D, A); break;
        // E destination
        // B source
        case 0b01011000: MOV(E, B); break;
        // C source
        case 0b01011001: MOV(E, C); break;
        // D source
        case 0b01011010: MOV(E, D); break;
        // E source
        case 0b01011011: MOV(E, E); break;
        // H source
        case 0b01011100: MOV(E, H); break;
        // L source
        case 0b01011101: MOV(E, L); break;
        // M source
        case 0b01011110: MOV(E, getM()); break;
        // A source
        case 0b01011111: MOV(E, A); break;
        // H destination
        // B source
        case 0b01100000: MOV(H, B); break;
        // C source
        case 0b01100001: MOV(H, C); break;
        // D source
        case 0b01100010: MOV(H, D); break;
        // E source
        case 0b01100011: MOV(H, E); break;
        // H source
        case 0b01100100: MOV(H, H); break;
        // L source
        case 0b01100101: MOV(H, L); break;
        // M source
        case 0b01100110: MOV(H, getM()); break;
        // A source
        case 0b01100111: MOV(H, A); break;
        // L destination
        // B source
        case 0b01101000: MOV(L, B); break;
        // C source
        case 0b01101001: MOV(L, C); break;
        // D source
        case 0b01101010: MOV(L, D); break;
        // E source
        case 0b01101011: MOV(L, E); break;
        // H source
        case 0b01101100: MOV(L, H); break;
        // L source
        case 0b01101101: MOV(L, L); break;
        // M source
        case 0b01101110: MOV(L, getM()); break;
        // A source
        case 0b01101111: MOV(L, A); break;
        // M destination
        // B source
        case 0b01110000: MOV(getM(), B); break;
        // C source
        case 0b01110001: MOV(getM(), C); break;
        // D source
        case 0b01110010: MOV(getM(), D); break;
        // E source
        case 0b01110011: MOV(getM(), E); break;
        // H source
        case 0b01110100: MOV(getM(), H); break;
        // L source
        case 0b01110101: MOV(getM(), L); break;
        // M source
        case 0b01110110: MOV(getM(), getM()); break;
        // A source
        case 0b01110111: MOV(getM(), A); break;
        // A destination
        // B source
        case 0b01111000: MOV(A, B); break;
        // C source
        case 0b01111001: MOV(A, C); break;
        // D source
        case 0b01111010: MOV(A, D); break;
        // E source
        case 0b01111011: MOV(A, E); break;
        // H source
        case 0b01111100: MOV(A, H); break;
        // L source
        case 0b01111101: MOV(A, L); break;
        // M source
        case 0b01111110: MOV(A, getM()); break;
        // A source
        case 0b01111111: MOV(A, A); break;

        // STAX - Store Accumulator
        // Register BC
        case 0b00000010: writeByte(getBC(), A); break;
        // Register DE
        case 0b00010010: writeByte(getDE(), A); break;

        // LDAX - Load Accumulator
        // Register BC
        case 0b00001010: A = readByte(getBC()); break;
        // Register DE
        case 0b00011010: A = readByte(getDE()); break;

        // REGISTER OR MEMORY TO ACCUMULATOR INSTRUCTIONS
        // ADD - Add register or memory to Accumulator
        // Register B
        case 0b10000000: ADD(B); break;
        // Register C
        case 0b10000001: ADD(C); break;
        // Register D
        case 0b10000010: ADD(D); break;
        // Register E
        case 0b10000011: ADD(E); break;
        // Register H
        case 0b10000100: ADD(H); break;
        // Register L
        case 0b10000101: ADD(L); break;
        // Register M
        case 0b10000110: ADD(getM()); break;
        // Register A
        case 0b10000111: ADD(A); break;

        // ADC - Add register or memory to Accumulator with carry
        // Register B
        case 0b10001000: ADC(B); break;
        // Register C
        case 0b10001001: ADC(C); break;
        // Register D
        case 0b10001010: ADC(D); break;
        // Register E
        case 0b10001011: ADC(E); break;
        // Register H
        case 0b10001100: ADC(H); break;
        // Register L
        case 0b10001101: ADC(L); break;
        // Register M
        case 0b10001110: ADC(getM()); break;
        // Register A
        case 0b10001111: ADC(A); break;

        // SUB - Subtract register or memory from Accumulator
        // Register B
        case 0b10010000: SUB(B); break;
        // Register C
        case 0b10010001: SUB(C); break;
        // Register D
        case 0b10010010: SUB(D); break;
        // Register E
        case 0b10010011: SUB(E); break;
        // Register H
        case 0b10010100: SUB(H); break;
        // Register L
        case 0b10010101: SUB(L); break;
        // Register M
        case 0b10010110: SUB(getM()); break;
        // Register A
        case 0b10010111: SUB(A); break;

        // SBB - Subtract register or memory from Accumulator with borrow
        // Register B
        case 0b10011000: SBB(B); break;
        // Register C
        case 0b10011001: SBB(C); break;
        // Register D
        case 0b10011010: SBB(D); break;
        // Register E
        case 0b10011011: SBB(E); break;
        // Register H
        case 0b10011100: SBB(H); break;
        // Register L
        case 0b10011101: SBB(L); break;
        // Register M
        case 0b10011110: SBB(getM()); break;
        // Register A
        case 0b10011111: SBB(A); break;

        // ANA - Logical and Register or Memory With Accumulator
        // Register B
        case 0b10100000: ANA(B); break;
        // Register C
        case 0b10100001: ANA(C); break;
        // Register D
        case 0b10100010: ANA(D); break;
        // Register E
        case 0b10100011: ANA(E); break;
        // Register H
        case 0b10100100: ANA(H); break;
        // Register L
        case 0b10100101: ANA(L); break;
        // Register M
        case 0b10100110: ANA(getM()); break;
        // Register A
        case 0b10100111: ANA(A); break;

        // XRA - Logical Exclusive-Or Register or Memory With Accumulator (Zero Accumulator)
        // Register B
        case 0b10101000: XRA(B); break;
        // Register C
        case 0b10101001: XRA(B); break;
        // Register D
        case 0b10101010: XRA(C); break;
        // Register E
        case 0b10101011: XRA(D); break;
        // Register H
        case 0b10101100: XRA(E); break;
        // Register L
        case 0b10101101: XRA(L); break;
        // Register M
        case 0b10101110: XRA(getM()); break;
        // Register A
        case 0b10101111: XRA(A); break;

        // ORA - Logical or Register or Memory With Accumulator
        // Register B
        case 0b10110000: ORA(B); break;
        // Register C
        case 0b10110001: ORA(C); break;
        // Register D
        case 0b10110010: ORA(D); break;
        // Register E
        case 0b10110011: ORA(E); break;
        // Register H
        case 0b10110100: ORA(H); break;
        // Register L
        case 0b10110101: ORA(L); break;
        // Register M
        case 0b10110110: ORA(getM()); break;
        // Register A
        case 0b10110111: ORA(A); break;

        // CMP - Compare Register or Memory With Accumulator
        // Register B
        case 0b10111000: CMP(B); break;
        // Register C
        case 0b10111001: CMP(C); break;
        // Register D
        case 0b10111010: CMP(D); break;
        // Register E
        case 0b10111011: CMP(E); break;
        // Register H
        case 0b10111100: CMP(H); break;
        // Register L
        case 0b10111101: CMP(L); break;
        // Register M
        case 0b10111110: CMP(getM()); break;
        // Register A
        case 0b10111111: CMP(A); break;

        // ROTATE ACCUMULATOR INSTRUCTIONS
        // RLC - Rotate Accumulator Left
        case 0b00000111: RLC(); break;
        // RRC - Rotate Accumulator Right
        case 0b00001111: RRC(); break;
        // RAL - Rotate Accumulator Left Through Carry
        case 0b00010111: RAL(); break;
        // RAR - Rotate Accumulator Right Through Carry
        case 0b00011111: RAR(); break;

        // REGISTER PAIR INSTRUCTIONS
        // PUSH - Push Data Onto Stack
        // Registers BC
        case 0b11000101: PUSH(B, C); break;
        // Registers DE
        case 0b11010101: PUSH(D, E); break;
        // Registers HL
        case 0b11100101: PUSH(H, L); break;
        // Registers flags+A
        case 0b11110101: PUSH(flags, A); break;

        // POP - Pop Data Off Stack
        // Registers BC
        case 0b11000001: POP(B, C); break;
        // Registers DE
        case 0b11010001: POP(D, E); break;
        // Registers HL
        case 0b11100001: POP(H, L); break;
        // Registers flags+A
        case 0b11110001: POP(flags, A); break;

        // DAD - Double Add
        // Registers BC
        case 0b00001001: DAD(getBC()); break;
        // Registers DE
        case 0b00011001: DAD(getDE()); break;
        // Registers HL
        case 0b00101001: DAD(getHL()); break;
        // Registers SP
        case 0b00111001: DAD(SP); break;

        // INX - Increment Register Pair
        // Registers BC
        case 0b00000011: setBC(getBC() + 1); break;
        // Registers DE
        case 0b00010011: setDE(getDE() + 1); break;
        // Registers HL
        case 0b00100011: setHL(getHL() + 1); break;
        // Registers SP
        case 0b00110011: SP++; break;

        // DCX - Decrement Register Pair
        // Registers BC
        case 0b00001011: setBC(getBC() - 1); break;
        // Registers DE
        case 0b00011011: setDE(getDE() - 1); break;
        // Registers HL
        case 0b00101011: setHL(getHL() - 1); break;
        // Registers SP
        case 0b00111011: SP--; break;

        // XCHG - Exchange Registers
        case 0b11101011:
        word temp = getHL();
        setHL(getDE());
        setDE(temp);
        break;

        // XTHL - Exchange Stack
        case 0b11100011:
        L = memory[SP];
        H = memory[SP+1];
        break;

        // SPHL - Load SP From H And L
        case 0b11111001:
        SP - getHL();
        break;

        // IMMEDIATE INSTRUCTIONS

    }
}

void intel8080::writeByte(word address, byte value) {
    memory[address] = value;
}

byte intel8080::readByte(word address) {
    return memory[address];
}

void intel8080::writeWord(word address, word value) {
    memory[address] = value << 8;
    memory[address + 1] = value & 0xFF;
}

word intel8080::readWord(word address) {
    return (readByte(address + 1) << 8) | readByte(address);
}

void intel8080::setSign(bool val) {
    flags = flags & (255 - 128);
    flags = flags | (val << 7);
}

bool intel8080::getSign() {
    return (flags & 0b10000000);
}

void intel8080::setZero(bool val) {
    flags = flags & (255 - 64);
    flags = flags | (val << 6);
}

bool intel8080::getZero() {
    return (flags & 0b01000000);
}

void intel8080::setAuxCarry(bool val) {
    flags = flags & (255 - 16);
    flags = flags | (val << 4);
}

bool intel8080::getAuxCarry() {
    return (flags & 0b00010000);
}

void intel8080::setParity(bool val) {
    flags = flags & (255 - 4);
    flags = flags | (val << 2);
}

bool intel8080::getParity() {
    return (flags & 0b00000100);
}

void intel8080::setCarry(bool val) {
    flags = flags & (255 - 1);
    flags = flags | val;
}

bool intel8080::getCarry() {
    return (flags & 0b00000001);
}

void intel8080::setSZP(byte value) {
    setSign(value >> 7);
    setZero(value == 0);
    // my own method
    byte val = 0x01;
    int onesCount = 0;
    for (int i=0; i<8; i++) {
        if (val & value) {
            onesCount++;
        }
        val = val << 1;
    }
    if (onesCount % 2 == 0) {
        setParity(true);
    } else {
        setParity(false);
    }
}

bool intel8080::setCarry(byte value, byte operand) {
    // cast value to higher bit count variable
    short bigValue = value;
    bigValue += operand;
    setCarry(bigValue >> 8);
    return getCarry();
}

bool intel8080::setCarry(byte value, byte operand) {
    // cast value to higher bit count variable
    unsigned long int bigValue = value;
    bigValue += operand;
    setCarry(bigValue >> 16);
    return getCarry();
}

bool intel8080::setAuxCarry(byte value, byte operand) {

    bool previousCarry = false;
    for (int i=0; i<4; i++) {
        // Clear bits to the left
        byte tempVal = value << (7 - i);
        tempVal = tempVal >> (7 - i);
        // Clear bits to the right
        tempVal = tempVal >> i;
        // Rinse and repeat
        byte tempOperand = operand << (7 - i);
        tempOperand = tempOperand >> (7 - i);
        tempOperand = tempOperand >> i;

        int val = 0;
        if (tempVal > 0) {
            val++;
        }
        if (tempOperand > 0) {
            val++;
        }
        if (previousCarry) {
            val++;
        }

        // if it's the 4th iteration, set aux_carry
        if (i == 3) {
            setAuxCarry(val >= 2);
        }

        if (val >= 2) {
            previousCarry = true;
        } else {
            previousCarry = false;
        }

    }


    return getAuxCarry();
}

void intel8080::setBC(word value) {
    B = value >> 8;
    C = value & 0xFF;
}

word intel8080::getBC() {
    return (B << 8) | C;
}

void intel8080::setDE(word value) {
    D = value >> 8;
    E = value & 0xFF;
}

word intel8080::getDE() {
    return (D << 8) | E;
}

void intel8080::setHL(word value) {
    H = value >> 8;
    L = value & 0xFF;
}

word intel8080::getHL() {
    return (H << 8) | L;
}

void intel8080::setM(byte value) {
    writeByte(getHL(), value);
}

byte& intel8080::getM() {
    return memory[getHL()]; // this will actually return a reference so operations can be performed on it
}

void intel8080::INR(byte& reg) {
    setAuxCarry(reg, 1);
    reg += 1;
    setSZP(reg);
}

void intel8080::DCR(byte& reg) {
    setAuxCarry(reg, -1);
    reg -= 1;
    setSZP(reg);
}

void intel8080::MOV(byte& dest, byte src) {
    dest = src;
}

void intel8080::ADD(byte reg) {
    setAuxCarry(A, reg);
    A += reg;
    setSZP(A);
}

void intel8080::ADC(byte reg) {
    bool tempAuxCarry = false;
    bool tempCarry = false;

    if (setAuxCarry(A, reg)) {
        tempAuxCarry = true;
    }
    if (setCarry(A, reg)) {
        tempCarry = true;
    }
    A += reg;
    if (setAuxCarry(A, getCarry())) {
        tempAuxCarry = true;
    }
    if (setCarry(A, getCarry())) {
        tempCarry = true;
    }
    A += getCarry();
    setSZP(A);
    setAuxCarry(tempAuxCarry);
    setCarry(tempCarry);
}

void intel8080::SUB(byte reg) {
    bool tempAuxCarry = false;
    bool tempCarry = true;
    
    reg = ~reg;
    if (setAuxCarry(reg, 1))
        tempAuxCarry = true;
    if (setCarry(reg, 1))
        tempCarry = false;
    reg += 1;

    if (setAuxCarry(A, reg))
        tempAuxCarry = true;
    if (setCarry(A, reg))
        tempCarry = false;
    
    A += reg;
    setSZP(A);
    setAuxCarry(tempAuxCarry);
    setCarry(tempCarry);
}

void intel8080::SBB(byte reg) {

    bool previousCarry = getCarry();

    bool tempAuxCarry = false;
    bool tempCarry = true;
    if (setAuxCarry(reg, getCarry()))
        tempAuxCarry = true;
    if (setCarry(reg, getCarry()))
        tempCarry = false;
    
    SUB(reg + previousCarry);
    if (getAuxCarry() == false)
        setAuxCarry(tempAuxCarry);
    if (getCarry() == true)
        setCarry(tempCarry);
}

void intel8080::ANA(byte& reg) {
    setCarry(false);
    A = reg & A;
    setSZP(A);
}

void intel8080::XRA(byte& reg) {
    setCarry(false);
    // turns out, the aux carry flag is just reset to 0. simple :)
    setAuxCarry(false);
    A = reg ^ A;
    setSZP(A);
}

void intel8080::ORA(byte& reg) {
    setCarry(false);
    A = reg | A;
    setSZP(A);
}

void intel8080::CMP(byte reg) {

    reg = (~reg) + 1;

    setSZP(A + reg);
    setCarry(!setCarry(A, reg));
    setAuxCarry(A, reg);
}

void intel8080::RLC() {
    setCarry(A >> 7);
    byte temp = A & 0x80;
    temp = temp >> 7;
    A = A << 1;
    A = A | temp;
}

void intel8080::RRC() {
    setCarry(A & 0x01);
    byte temp = A & 0x01;
    temp = temp << 7;
    A = A >> 1;
    A = A | temp;
}

void intel8080::RAL() {
    byte temp = getCarry();
    setCarry(A >> 7);
    A = A << 1;
    A = A | temp;
}

void intel8080::RAR() {
    byte temp = getCarry();
    temp = temp << 7;
    setCarry(A & 0x01);
    A = A >> 1;
    A = A | temp;
}

void intel8080::PUSH(byte reg1, byte reg2) {
    memory[--SP] = reg1;
    memory[--SP] = reg2;
}

void intel8080::POP(byte& reg1, byte& reg2) {
    reg2 = memory[SP];
    reg1 = memory[SP+1];
}

void intel8080::DAD(word regs) {
    setHL(getHL() + regs);
    setCarryWord(getHL(), regs);
}

void intel8080::MVI(byte& reg) {
    reg = memory[++PC];
}

void intel8080::ADI() {
    PC++;
    setCarry(A, memory[PC]);
    setAuxCarry(A, memory[PC]);
    A += memory[PC];
    setSZP(A);
}

void intel8080::ACI() {
    bool tempAuxCarry = false;
    bool tempCarry = false;

    PC++;

    if (setAuxCarry(A, memory[PC])) {
        tempAuxCarry = true;
    }
    if (setCarry(A, memory[PC])) {
        tempCarry = true;
    }
    A += memory[PC];
    if (setAuxCarry(A, getCarry())) {
        tempAuxCarry = true;
    }
    if (setCarry(A, getCarry())) {
        tempCarry = true;
    }
    A += getCarry();
    setSZP(A);
    setAuxCarry(tempAuxCarry);
    setCarry(tempCarry);
}

void intel8080::SUI() {
    PC++;
    setCarry(A, (~memory[PC]) + 1);
    setAuxCarry(A, (~memory[PC]) + 1);
    A += (~memory[PC]) + 1;
    setSZP(A);
}

void intel8080::SBI() {
    bool tempAuxCarry = false;
    bool tempCarry = false;

    PC++;

    if (setAuxCarry(A, (~memory[PC]) + 1)) {
        tempAuxCarry = true;
    }
    if (setCarry(A, (~memory[PC]) + 1)) {
        tempCarry = true;
    }
    A += (~memory[PC]) + 1;
    if (setAuxCarry(A, getCarry())) {
        tempAuxCarry = true;
    }
    if (setCarry(A, getCarry())) {
        tempCarry = true;
    }
    A += (~getCarry()) + 1;
    setSZP(A);
    setAuxCarry(tempAuxCarry);
    setCarry(tempCarry);
}

void intel8080::ANI() {
    setCarry(false);
    A = A & memory[++PC];
    setSZP(A);
}

void intel8080::XRI() {
    setCarry(false);
    A = A ^ memory[++PC];
    setSZP(A);
}

void intel8080::ORI() {
    setCarry(false);
    A = A | memory[++PC];
    setSZP(A);
}

void intel8080::CPI() {

    PC++;
    byte temp = memory[PC] = (~memory[PC]) + 1;

    setSZP(A + memory[PC]);
    setCarry(!setCarry(A, memory[PC]));
    setAuxCarry(A, memory[PC]);
}

void intel8080::STA() {
    word address;
    address = memory[PC+2];
    address = address << 8;
    address = address | memory[PC+1];
    memory[address] = A;
    PC += 2;
}

void intel8080::LDA() {
    word address;
    address = memory[PC+2];
    address = address << 8;
    address = address | memory[PC+1];
    A = memory[address];
    PC += 2;
}

void intel8080::SHLD() {
    word address;
    address = memory[PC+2];
    address = address << 8;
    address = address | memory[PC+1];
    memory[address] = L;
    memory[address+1] = H;
    PC += 2;
}

void intel8080::LHLD() {
    word address;
    address = memory[PC+2];
    address = address << 8;
    address = address | memory[PC+1];
    L = memory[address];
    H = memory[address+1];
    PC += 2;
}

void intel8080::run() {
    while (PC < memorySize) {
        execute(readByte(PC++));
    }
}



void intel8080::step() {
    execute(readByte(PC++));
}