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
    Byte STATUS; //System Flags [NV-BDIZC]
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
            
        };
    };
};

int main(){
    MEMORY mem;
    CPU cpu;
    cpu.Reset(mem);
    cpu.Execute(2, mem);
    return 0;
};