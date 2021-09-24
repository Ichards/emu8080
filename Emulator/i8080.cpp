#include "i8080.h"


i8080::i8080(byte* p_memory, int p_memorySize)
:
A(0), B(0), C(0), D(0), E(0), H(0), L(0), SP(0), PC(0),
flags(0b00000010)
{
    memory = p_memory;
    memorySize = p_memorySize;
}

i8080::~i8080() {
}

void i8080::execute(byte opCode) {

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
            }
            if ( (A & 0xF0) > 9 || getCarry()) {
                setCarry(A, 6);
                A += 0x60;
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

        
    }
}

void i8080::writeByte(word address, byte value) {
    memory[address] = value;
}

byte i8080::readByte(word address) {
    return memory[address];
}

void i8080::writeWord(word address, word value) {
    memory[address] = value << 8;
    memory[address + 1] = value & 0xFF;
}

word i8080::readWord(word address) {
    return (readByte(address + 1) << 8) | readByte(address);
}

void i8080::setSign(bool val) {
    flags = flags ^ (val << 7);
}

bool i8080::getSign() {
    return (flags & 0b10000000);
}

void i8080::setZero(bool val) {
    flags = flags ^ (val << 6);
}

bool i8080::getZero() {
    return (flags & 0b01000000);
}

void i8080::setAuxCarry(bool val) {
    flags = flags ^ (val << 4);
}

bool i8080::getAuxCarry() {
    return (flags & 0b00010000);
}

void i8080::setParity(bool val) {
    flags = flags ^ (val << 2);
}

bool i8080::getParity() {
    return (flags & 0b00000100);
}

void i8080::setCarry(bool val) {
    flags = flags ^ val;
}

bool i8080::getCarry() {
    return (flags & 0b00000001);
}

void i8080::setSZP(byte value) {
    setSign(value >> 7);
    setZero(value == 0);
    // ripped this from the internet
    setParity(true);
    while (value) {
        setParity(!getParity());
        value = value & (value - 1);
    }
}


bool i8080::setCarry(byte value, byte operand) {
    // cast value to higher bit count variable
    short bigValue = value;
    bigValue += operand;
    setCarry(bigValue >> 8);
    return getCarry();
}

bool i8080::setAuxCarry(byte value, byte operand) {
    // get rid of the most significant 4 bits
    value = value & 0x0F;
    value += operand;
    setAuxCarry(value >> 4);
    return getAuxCarry();
}

void i8080::setBC(word value) {
    B = value >> 8;
    C = value & 0xFF;
}

word i8080::getBC() {
    return (B << 8) | C;
}

void i8080::setDE(word value) {
    D = value >> 8;
    E = value & 0xFF;
}

word i8080::getDE() {
    return (D << 8) | E;
}

void i8080::setHL(word value) {
    H = value >> 8;
    L = value & 0xFF;
}

word i8080::getHL() {
    return (H << 8) | L;
}

void i8080::setM(byte value) {
    writeByte(getHL(), value);
}

byte& i8080::getM() {
    return memory[getHL()]; // this will actually return a reference so operations can be performed on it
}

void i8080::INR(byte& reg) {
    setAuxCarry(reg, 1);
    reg += 1;
    setSZP(reg);
}

void i8080::DCR(byte& reg) {
    setAuxCarry(reg, -1);
    reg -= 1;
    setSZP(reg);
}

void i8080::MOV(byte& dest, byte src) {
    dest = src;
}

void i8080::ADD(byte reg) {
    setAuxCarry(A, reg);
    A += reg;
    setSZP(A);
}

void i8080::ADC(byte reg) {
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

void i8080::SUB(byte reg) {
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

void i8080::SBB(byte reg) {
    bool tempAuxCarry = false;
    bool tempCarry = true;
    if (setAuxCarry(reg, getCarry()))
        tempAuxCarry = true;
    if (setCarry(reg, getCarry()))
        tempCarry = false;
    
    SUB(reg + getCarry());
    if (getAuxCarry() == false)
        setAuxCarry(tempAuxCarry);
    if (getCarry() == true)
        setCarry(tempCarry);
}

void i8080::ANA(byte& reg) {
    setCarry(false);
    reg = reg & A;
    setSZP(reg);
}

void i8080::XRA(byte& reg) {
    setCarry(false);
    // doesn't really say how to set aux_carry flag, so here's my logic:
    // if both registers are 1 at the 4th least significant bit, then it sets it. real simple :)
    setAuxCarry(1 == ((reg & 0x08) == (A & 0x08)));
    reg = reg ^ A;
    setSZP(reg);
}

void i8080::ORA(byte& reg) {
    setCarry(false);
    reg = reg | A;
    setSZP(reg);
}

void i8080::CMP(byte reg) {
    setZero(reg == A);

    bool sameSign = true;

    if ((reg >> 7) != (A >> 7))
        sameSign = false;
    
    if (reg > A && sameSign)
        setCarry(true);
    else
        setCarry(false);
}

void i8080::RLC() {
    setCarry(A >> 7);
    byte temp = A & 0x80;
    temp = temp >> 7;
    A = A << 1;
    A = A | temp;
}

void i8080::RRC() {
    setCarry(A & 0x01);
    byte temp = A & 0x01;
    temp = temp << 7;
    A = A >> 1;
    A = A | temp;
}

void i8080::RAL() {
    byte temp = getCarry();
    setCarry(A >> 7);
    A = A << 1;
    A = A | temp;
}

void i8080::RAR() {
    byte temp = getCarry();
    temp = temp << 7;
    setCarry(A & 0x01);
    A = A >> 1;
    A = A | temp;
}

void i8080::PUSH(byte reg1, byte reg2) {
    memory[--SP] = reg1;
    memory[--SP] = reg2;
}

void i8080::POP(byte& reg1, byte& reg2) {
    reg2 = memory[SP];
    reg1 = memory[SP+1];
}

void i8080::run() {
    while (PC < memorySize) {
        execute(readByte(PC++));
    }
}

void i8080::run() {
    execute(readByte(PC++));
}