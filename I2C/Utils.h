#ifndef utils_h_
#define utils_h_

#define SetBit(Reg,Num) (Reg = Reg | (1<<Num))
#define ClearBit(Reg,Num) (Reg = Reg & ~(1<<Num))

#define GetBit(Reg,Num) ((Reg>>Num)&1)
#define ToggleBit(Reg,Num) ((Reg ^=(1<<Num)))
#define SetPort(Reg) (Reg | oxFF)
#define GetPort(Reg) (Reg & 0xFF)

#endif 
