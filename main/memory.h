#pragma once
#include <stdint.h>
#include <stddef.h>

#define MEM_SIZE 0x10000

typedef struct rv32i_mem {
    uint8_t ram[MEM_SIZE];
} rv32i_mem_t;

void     mem_init(rv32i_mem_t *m);
void     mem_load(rv32i_mem_t *m, const uint8_t *data, size_t len, uint32_t base);

uint8_t  mem_read8 (rv32i_mem_t *m, uint32_t addr);
uint16_t mem_read16(rv32i_mem_t *m, uint32_t addr);
uint32_t mem_read32(rv32i_mem_t *m, uint32_t addr);

void     mem_write8 (rv32i_mem_t *m, uint32_t addr, uint8_t  val);
void     mem_write16(rv32i_mem_t *m, uint32_t addr, uint16_t val);
void     mem_write32(rv32i_mem_t *m, uint32_t addr, uint32_t val);
