/*
 * Copyright (c) 2017-2018, NVIDIA CORPORATION. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated into other
 * software packages, subject to the following license:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of NVIDIA CORPORATION nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdarg.h>
#include <nvdla_interface.h>
#include <nvdla_riscv.h>
#include <string.h>

static struct nvdla_config nvdla_config_os_initial = {
	.atom_size = 32,
	.bdma_enable = true,
	.rubik_enable = true,
	.weight_compress_support = true,
};

static struct nvdla_config nvdla_config_small = {
	.atom_size = 8,
	.bdma_enable = false,
	.rubik_enable = false,
	.weight_compress_support = false,
};

static struct nvdla_config nvdla_config_large = {
	.atom_size = 32,
	.bdma_enable = false,
	.rubik_enable = false,
	.weight_compress_support = false,
};
/*
//static struct riscv_device *nvdla_dev;
//static struct nvdla_submit_task *local_task;

void* get_nvdla_dev(void)
{
    return &nvdla_dev;
}
void set_nvdla_dev(struct riscv_device *rdev)
{
    nvdla_dev = rdev;
}

void* get_local_task(void)
{
    return &local_task;
}*/


void dla_debug(const char *str, ...)
{
	//va_list args;
	//va_start(args, str);
	//vprintk(pr_fmt(str), args);
	//va_end(args);
}

void dla_info(const char *str, ...)
{
	//va_list args;
	//va_start(args, str);
	//vprintk(str, args);
	//va_end(args);
}

void dla_warn(const char *str, ...)
{
	//va_list args;
    //va_start(args, str);
	//vprintk(str, args);
	//va_end(args);
}

void dla_error(const char *str, ...)
{
	//va_list args;
	//va_start(args, str);
	//vprintk(str, args);
	//va_end(args);
}

void *dla_memset(void *src, int ch, uint64_t len)
{
	return memset(src, ch, len);
}

void *dla_memcpy(void *dest, const void *src, uint64_t len)
{
	return memcpy(dest, src, len);
}

int64_t dla_get_time_us(void)
{
	return 0;
}

void dla_reg_write(void *driver_context, uint32_t addr, uint32_t reg)
{
	struct nvdla_device *nvdla_dev =
			(struct nvdla_device *)driver_context;

	if (!nvdla_dev)
		return;

    asm volatile("sw %0, 0(%1)" :: "r"(reg), "r"(nvdla_dev->base + addr));
}

uint32_t dla_reg_read(void *driver_context, uint32_t addr)
{
	struct nvdla_device *nvdla_dev =
			(struct nvdla_device *)driver_context;
    uint32_t ret;

	if (!nvdla_dev)
		return 0;

    asm volatile("lw %0, 0(%1)" : "=r" (ret) : "r" (nvdla_dev->base + addr));

	return ret;
}

/*static irqreturn_t nvdla_engine_isr(int32_t irq, void *data)
{
	unsigned long flags;
	struct nvdla_device *nvdla_dev = (struct nvdla_device *)data;

	if (!nvdla_dev)
		return IRQ_NONE;

	dla_isr_handler(nvdla_dev->engine_context);

	return IRQ_HANDLED;
}*/

static int32_t dla_read_dma_address(void *driver_context, void *task_data,
						int16_t index, void *dst)
{
	int32_t ret = 0;
	struct nvdla_handle *handles;
    struct nvdla_offset *offsets;
	struct riscv_device *nvdla_dev =
			(struct riscv_device *)driver_context;
	struct riscv_task *task = (struct riscv_task *)task_data;

	if (index == -1 || index > task->num_addresses)
		return -1;

	handles = (struct nvdla_handle *)task->handle_list;
    offsets = (struct nvdla_offset *)task->offset_list;

	/* Add offset to IOVA address */
    memcpy(dst, &handles[index].handle, sizeof(struct nvdla_handle));
    uint64_t *tmp = (uint64_t *)dst;
    tmp[0] += offsets[index].offset;
	//*dst = *dst + handles[index].offset;

	return ret;
}

static int32_t dla_read_cpu_address(void *driver_context, void *task_data,
						int16_t index, void *dst)
{
	uint64_t *temp = (uint64_t *)dst;
	struct riscv_task *task = (struct riscv_task *)task_data;

	if (index == -1 || index > task->num_addresses)
		return -1;

	*temp = (uint64_t)index;
	return 0;
}

int32_t dla_get_dma_address(void *driver_context, void *task_data,
					int16_t index, void *dst_ptr,
					uint32_t destination)
{
	int32_t ret = 0;


    struct riscv_device *nvdla_dev =
            (struct riscv_device *)driver_context;
    volatile uint32_t *intr_mask = (void *)(uint32_t)(0x12001004);
    volatile uint32_t im;
    im = intr_mask[0];
    if (im!=0)
    {
        dla_isr_handler(nvdla_dev->engine_context);
    }


	if (destination == DESTINATION_PROCESSOR) {
		ret = dla_read_cpu_address(driver_context, task_data,
						index, dst_ptr);
	} else if (destination == DESTINATION_DMA) {
		ret = dla_read_dma_address(driver_context, task_data,
						index, dst_ptr);
	} else {
		ret = -1;
	}

	return ret;
}

int32_t dla_data_write(void *driver_context, void *task_data,
				void *src, uint64_t dst,
				uint32_t size, uint64_t offset)
{
	struct nvdla_handle *handles;
	struct riscv_task *task = (struct riscv_task *)task_data;

    struct riscv_device *nvdla_dev =
            (struct riscv_device *)driver_context;
    volatile uint32_t *intr_mask = (void *)(uint32_t)(0x12001004);
    volatile uint32_t im;
    im = intr_mask[0];
    if (im!=0)
    {
        dla_isr_handler(nvdla_dev->engine_context);
    }

	handles = task->handle_list;
    memcpy((void *)(uint32_t)(handles[dst].handle + offset), src, size);

	return 0;
}

int32_t dla_data_read(void *driver_context, void *task_data,
				uint64_t src, void *dst,
				uint32_t size, uint64_t offset)
{
	struct nvdla_handle *handles;
	struct riscv_task *task = (struct riscv_task *)task_data;
    struct riscv_device *nvdla_dev =
            (struct riscv_device *)driver_context;
    volatile uint32_t *intr_mask = (void *)(uint32_t)(0x12001004);
    volatile uint32_t im;
    im = intr_mask[0];
    if (im!=0)
    {
        dla_isr_handler(nvdla_dev->engine_context);
    }

	handles = task->handle_list;

    memcpy(dst, (void *)(uint32_t)(handles[src].handle + offset), size);

	return 0;
}

int32_t nvdla_task_submit(int list_start,int address_count)
{
	int32_t err = 0;
	uint32_t task_complete = 0;
    struct riscv_device *nvdla_dev = nvdla_init();
    struct riscv_task *task = malloc(sizeof(struct riscv_task));

    //volatile unsigned int address = 0x800f0e80;
    volatile unsigned int address = list_start;
    uint32_t task_count = 1;
    volatile uint8_t *read_byte = (uint8_t *)address;
    volatile uint8_t ra,rb,rc,rd;
    struct nvdla_handle *handles = malloc(address_count * sizeof(struct nvdla_handle));
    struct nvdla_offset *offsets = malloc(address_count * sizeof(struct nvdla_offset));
    volatile uint32_t *mem_handles = (uint32_t *)handles;
    volatile uint32_t *mem_offsets = (uint32_t *)offsets;
    uint32_t j;

    for (j = 0; j < address_count; j++) {
        read_byte = (uint8_t *)address;
        ra = read_byte[0]; rb = read_byte[1]; rc = read_byte[2]; rd = read_byte[3];
        mem_handles[0] = ((((uint32_t)ra)<<24) | (((uint32_t)rb)<<16) | (((uint32_t)rc)<<8) | (((uint32_t)rd)));
        mem_handles += 0x00000001;
        address += 0x00000004;
        read_byte = (uint8_t *)address;
        ra = read_byte[0]; rb = read_byte[1]; rc = read_byte[2]; rd = read_byte[3];
        mem_offsets[0] = ((((uint32_t)ra)<<24) | (((uint32_t)rb)<<16) | (((uint32_t)rc)<<8) | (((uint32_t)rd)));
        mem_offsets += 0x00000001;
        address += 0x00000004;
    }

    task->num_addresses = address_count;
    task->nvdla_dev = nvdla_dev;
    task->handle_list = handles;
    task->offset_list = offsets;
    nvdla_dev->task = task;
    task->nvdla_dev = nvdla_dev;

	nvdla_dev->task = task;

	err = dla_execute_task(nvdla_dev->engine_context, (void *)task, nvdla_dev->config_data);
	if (err) {
		//pr_err("Task execution failed\n");
		return err;
	}

	//pr_debug("Wait for task complete\n");

	while (1) {

        dla_isr_handler(nvdla_dev->engine_context);

		err = dla_process_events(nvdla_dev->engine_context, &task_complete);

		if (err || task_complete)
			break;
	}

	//pr_debug("Task complete\n");
	dla_clear_task(nvdla_dev->engine_context);

	return err;
}

struct riscv_device * nvdla_init()
{
    //struct riscv_device *nvdla_dev = get_nvdla_dev();
    struct riscv_device *nvdla_dev = malloc(sizeof(struct riscv_device));
    nvdla_dev->config_data = &nvdla_config_small;

    /* initialize io base */
    nvdla_dev->base = (volatile void *)(0x12000000);

    dla_register_driver(&nvdla_dev->engine_context, (void *)nvdla_dev);
    dla_clear_task(nvdla_dev->engine_context);
    return nvdla_dev;
}
