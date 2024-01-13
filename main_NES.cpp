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
    Byte Data[MAX_MEM];
    void initialize(){
        for (U32 i = 0; i <= MAX_MEM; i++){
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
    void Reset (MEMORY mem){
        A=X=Y=0;
        mem.initialize();
    };
};

int main(){
    MEMORY mem;
    CPU cpu;
    cpu.Reset(mem);
    return 0;
};