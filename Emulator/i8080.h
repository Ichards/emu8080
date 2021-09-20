typedef unsigned char byte;
typedef unsigned short int word;

class i8080 {
    private:
        // registers
        byte A, B, C, D, E, H, L;
        word SP, PC;

        // flags
        bool sign, zero, parity, carry, aux_carry;

        // memory
        byte* memory;
        int memorySize;

        // execute instruction
        void execute(byte opcode);

        // read and write to memory
        // byte
        void writeByte(word address, byte value);
        byte readByte(word address);
        // word
        void writeWord(word address, word value);
        word readWord(word address);

        // set sign, zero, parity flags
        void setSZP(byte value);
        // carry
        bool setCarry(byte value, byte addend); // assuming the value being operated upon is a byte, hope the assumption works out :^|
        // aux carry
        bool setAuxCarry(byte value, byte addend);
        
        // functions to handle the merged registers
        void setBC(word value);
        word getBC();

        void setDE(word value);
        word getDE();

        void setHL(word value);
        word getHL();

        // handles the psuedo-register M, which is just the byte the word in HL is pointing to
        void setM(byte value);
        byte& getM();

        // all the opcode instructions
        void INR(byte& reg);
        void DCR(byte& reg);
        void MOV(byte& dest, byte src);
        void ADD(byte reg);
        void ADC(byte reg);
        void SUB(byte reg);
        void SBB(byte reg);
        void ANA(byte& reg);
        void XRA(byte& reg);
        void ORA(byte& reg);
        void CMP(byte reg);
        void RLC();
        void RRC();
        void RAL();
        void RAR();


    public:
        // constructor
        i8080(byte* p_memory, int p_memorySize);
        // destructor
        ~i8080();

        // start program
        void run();

        // debug function
        void printStats();

};