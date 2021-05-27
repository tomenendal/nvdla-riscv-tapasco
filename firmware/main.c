#include "../rv_pe.h"
//#include <stdio.h>
//#include <stdlib.h>
#include "nvdla_riscv.h"
#include "nvdla_interface.h"


int main(void)
{
    int value_c, value_cc;
    value_c = value_a+value_b;
    value_cc = value_c*value_c;
    //printf("hello");
    nvdla_init();
    volatile int val, op;
    asm volatile("lw %0, 0(%1)" : "=r" (val) : "r" (0xee000007c));
    asm volatile("lw %0, 0(%1)" : "=r" (op) : "r" (0xee000007e));
    asm("LI t6, (1 << 15)");
    asm("CSRRW x0, 0x7b0, t6");
    asm("EBREAK");
    writeToCtrl(RETL,0);
    setIntr();
    return 0;
}
