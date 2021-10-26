extern "C" {
#include "../TestEmulator/i8080.h"
}
#include <iostream>


typedef unsigned char byte;
typedef unsigned short int word;


class intel8080 {
    private:
        // Halt and INTE
        bool halt, INTE;

        // registers
        byte A, B, C, D, E, H, L;
        word SP, PC;

        // flags
        byte flags;
        void setSign(bool val);
        bool getSign();
        void setZero(bool val);
        bool getZero();
        void setAuxCarry(bool val);
        bool getAuxCarry();
        void setParity(bool val);
        bool getParity();
        void setCarry(bool val);
        bool getCarry();
        
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
        bool setCarryWord(word value, word addend);
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
        void PUSH(byte reg1, byte reg2);
        void POP(byte& reg1, byte& reg2);
        void DAD(word regs);
        void MVI(byte& reg);
        void ADI();
        void ACI();
        void SUI();
        void SBI();
        void ANI();
        void XRI();
        void ORI();
        void CPI();
        void STA();
        void LDA();
        void SHLD();
        void LHLD();
        void PCHL();
        void JMP();
        void JC();
        void JNC();
        void JZ();
        void JNZ();
        void JM();
        void JP();
        void JPE();
        void JPO();
        void CALL();
        void CC();
        void CNC();
        void CZ();
        void CNZ();
        void CM();
        void CP();
        void CPE();
        void CPO();
        void RET();
        void RC();
        void RNC();
        void RZ();
        void RNZ();
        void RM();
        void RP();
        void RPE();
        void RPO();
        void RST(byte exp);
        void EI();
        void DI();
        void IN();
        void OUT();
        void HLT();


    public:
        // constructor
        intel8080(byte* p_memory, int p_memorySize);
        // destructor
        ~intel8080();

        // run program
        void run();
        void step();

        // debug functions
        void printStats();
        bool compareCPU(i8080* testCpu);
};