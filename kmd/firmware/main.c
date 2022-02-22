#include "../rv_pe.h"
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
#include "nvdla_riscv.h"
#include "nvdla_interface.h"


int main()
{
    int add_list_start = 0x800f0e80;//readFromCtrl(ARG1);
    int num_add = 10;//readFromCtrl(ARG2);
    nvdla_init();
    uint32_t complete = nvdla_task_submit(add_list_start,num_add);
    //writeToCtrl(RETL, complete);

    asm("LI t6, (1 << 15)");
    asm("CSRRW x0, 0x7b0, t6");
    asm("EBREAK");
    //asm("fence.i");
    setIntr();
    return 0;
}
