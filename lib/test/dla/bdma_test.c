
#include "dla_engine_internal.h"
#include <nvdla_riscv.h>
#include "test_util.h"


extern uint32_t dla_irq_notifier_test;
static uint32_t saved_irq = 0;
uint32_t check_irq = MASK(GLB_S_INTR_STATUS_0, BDMA_DONE_STATUS0);
void dla_bdma_test(void)
{
    bdma_reg_write(CFG_DST_SURF, 0x800);
    bdma_reg_write(CFG_DST_LINE, 0x100);
    bdma_reg_write(CFG_SRC_SURF, 0x800);
    bdma_reg_write(CFG_SRC_LINE, 0x100);
    bdma_reg_write(CFG_SURF_REPEAT, 0x0);
    bdma_reg_write(CFG_LINE_REPEAT, 0x7);
    bdma_reg_write(CFG_LINE, 0x7);
    bdma_reg_write(CFG_CMD, 0x3);
    bdma_reg_write(CFG_SRC_ADDR_LOW, gpsram_read32(DLA_BASE));
    bdma_reg_write(CFG_SRC_ADDR_HIGH, gpsram_read32(DLA_BASE + 4));
    bdma_reg_write(CFG_DST_ADDR_LOW, gpsram_read32(DLA_BASE + 8));
    bdma_reg_write(CFG_DST_ADDR_HIGH, gpsram_read32(DLA_BASE + 12));
    bdma_reg_write(CFG_OP, 0x1);
    bdma_reg_write(CFG_LAUNCH0, 0x1);

    wait_for_dla_flag(&dla_irq_notifier_test, &saved_irq, check_irq);

    send_end_to_simulation();
}

void riscv_runtime(void)
{

    // use handler for test
    register_irq_handler(IRQ_ID_IRQ0, irq0_handler_test);
    set_saved_irq(&saved_irq);

    dla_bdma_test();
}

