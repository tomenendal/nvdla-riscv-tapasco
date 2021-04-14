SIZE?=0x40000
STACK_START!=printf "0x%08x" $$(($(SIZE) + $(SIZE)))
MARCH?=rv32im
MABI?=ilp32
XLEN?=32
PROGRAM?=nvdla




NVDLA_DIR?=/home/stud/lt25geja/nrt/nvdla-riscv-tapasco/nvdla
STARTUP_DIR?=/home/stud/lt25geja/nrt/nvdla-riscv-tapasco/src/env
TEST_SEARCH_DIR?=/home/stud/lt25geja/nrt/nvdla-riscv-tapasco/src/test
RUNTIME_SEARCH_DIR?=/home/stud/lt25geja/nrt/nvdla-riscv-tapasco/src
SOURCE_FILES?=$(RUNTIME_SEARCH_DIR)/port/std_syscall.c $(RUNTIME_SEARCH_DIR)/arch/riscv/device.c $(RUNTIME_SEARCH_DIR)/arch/riscv/csr.c $(RUNTIME_SEARCH_DIR)/arch/riscv/csr_mmio.c $(RUNTIME_SEARCH_DIR)/arch/riscv/trap.c $(RUNTIME_SEARCH_DIR)/drivers/htif.c
NVDLA_SRC_FILES?=${NVDLA_DIR}/firmware/scheduler.c ${NVDLA_DIR}/firmware/engine.c ${NVDLA_DIR}/firmware/bdma.c ${NVDLA_DIR}/firmware/conv.c ${NVDLA_DIR}/firmware/sdp.c ${NVDLA_DIR}/firmware/cdp.c ${NVDLA_DIR}/firmware/pdp.c ${NVDLA_DIR}/firmware/rubik.c ${NVDLA_DIR}/firmware/cache.c ${NVDLA_DIR}/firmware/common.c ${NVDLA_DIR}/firmware/engine_data.c ${NVDLA_DIR}/firmware/engine_isr.c ${NVDLA_DIR}/firmware/engine_debug.c ${NVDLA_DIR}/port/riscv/nvdla_core_callbacks.c
INCLUDE_FILES?=-I${NVDLA_DIR}/firmware/ -I${NVDLA_DIR}/firmware/include/ -I${NVDLA_DIR}/include/ -I${NVDLA_DIR}/port/riscv/include/ -I${STARTUP_DIR}/ariane/ -I${STARTUP_DIR}/common/ -I${STARTUP_DIR}/common/rv64/ -I$(RUNTIME_SEARCH_DIR)/include/ -I$(RUNTIME_SEARCH_DIR)/include/arch/riscv -I$(RUNTIME_SEARCH_DIR)/test/
DEFINITIONS?=-DMAIN=0 -DATOMIC=0 -DTRAP=0 -DIRQ0=0 -DDLA_REG_TEST=1 -DMEM_TEST=1 -DTASK_TEST=1 -DNVDLA_INFO_ON=0 -DDEBUG_NETWORK_DATA=0 -DFPGA_LOG=0 -DSIM_LOG=1 -DQEMU_LOG=0

RV_FLAGS:=-march=$(MARCH) -mabi=$(MABI) -fno-pic -Os -g --specs=nano.specs -nostartfiles -Werror -Wl,--relax -Wl,--gc-sections -mcmodel=medany $(DEFINITIONS)

ifndef SWERV_CCM
	RV_FLAGS+= -T rv_$(SIZE).ld startup_$(SIZE)1.s
else
	RV_FLAGS+= -T rv_swerv.ld startup_swerv.s
endif

TOP:=`echo $(STACK_START) | cut -c3-7`
BOTTOM:=`echo $(STACK_START) | cut -c8-10`

program: setup
	riscv32-unknown-elf-gcc $(RV_FLAGS) /home/stud/lt25geja/nvtest/nvdla_riscv/src/riscv/main.c -o nvdla.elf $(SOURCE_FILES) $(NVDLA_SRC_FILES)
	      riscv32-unknown-elf-objcopy -O binary nvdla.elf nvdla.bin

setup:
	mkdir -p elf bin
	sed s/TOP/$(TOP)/ startup.s > startup_$(SIZE).s
	sed s/BOTTOM/$(BOTTOM)/ startup_$(SIZE).s > startup_$(SIZE)1.s
	sed s/SIZE/$(SIZE)/ rv.ld > rv_$(SIZE).ld
