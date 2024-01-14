#include <stdio.h>
#include <stdlib.h>
/* Xeno's NES Emulator
   (C) 2024 feesh.dev
*/
using Byte = unsigned char;
using Word = unsigned short;
using U32 = unsigned int;
struct MEMORY{
    static constexpr U32 MAX_MEM = 1024*64;
    static constexpr U32 PRG_ROM = 0x8000;
    static constexpr U32 RAM = 0x0000;
    static constexpr U32 IO = 0x2000;
    static constexpr U32 ExROM = 0x4020;
    static constexpr U32 SRAM = 0x6000;
    Byte Data[MAX_MEM];
    Byte operator[](U32 add) const
    {
        return Data[add];
    };
    void initialize(){
        for (U32 i = 0; i < PRG_ROM; i++){
            Data[i] = 0;
        };
    };
};
struct CPU
{
    Word PC;
    Word SP;
    Byte A,X,Y; //General Purpose
    //Byte STATUS; System Flags [NV-BDIZC]
    //TODO: rewrite it to be bitwise
    bool N,V,B,D,I,Z,C;
    static constexpr Byte
        //Load Accumulator
        LDA_IMM = 0xA9,
        //ADD with Carry
        ADC_IMM = 0x69,
        ADC_ZPG = 0x65,
        ADC_ZPX = 0x75,
        ADC_ABS = 0x6D,
        ADC_ABX = 0x7D,
        ADC_ABY = 0x79,
        ADC_INX = 0x61,
        ADC_INY = 0x71,
        //Logical AND
        AND_IMM = 0x29,
        AND_ZPG = 0x25,
        AND_ZPX = 0x35,
        AND_ABS = 0x2D,
        AND_ABX = 0x35,
        AND_ABY = 0x39,
        AND_INX = 0x21,
        AND_INY = 0x31;
    void Reset (MEMORY& mem){
        A=X=Y=0;
        mem.initialize();
    };
    Byte Grab(U32 cycles, MEMORY& mem){
        Byte data = mem[PC];
        PC++;
        cycles--;
        return data;
    };

    void Execute(U32 cycles, MEMORY& mem){
        while(cycles > 0){
            Byte inst = Grab(cycles, mem);
            switch(inst){
                case(LDA_IMM):
                {
                    Byte imm = Grab(cycles,mem);
                    Z = (A = 0);
                    N = (imm & 0b10000000) > 0;
                }break;
                case(ADC_IMM):
                {
                    Byte imm = Grab(cycles, mem);
                    A = (A + imm + C);
                    
                }break;
                case(AND_IMM):
                {   
                    Byte imm = Grab(cycles,mem);
                    Z = (X == 0);
                    N = (imm & 0b10000000) > 0;
                    A = A & imm;
                }break;  
            }
        };
    };
};

int main(){
    MEMORY mem;
    CPU cpu;
    cpu.Reset(mem);
    mem.Data[0x0000]=0xA9;
    mem.Data[0x0001]=0xFF;
    cpu.Execute(2, mem);
    return 0;
};