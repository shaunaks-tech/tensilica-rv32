#include "memory.h"
#include "rv32i.h"
#include <stddef.h>

void mem_init(rv32i_mem_t *mem) {
    memset(mem->data, 0, MEMORY_SIZE);
}

void mem_load(rv32i_mem_t *mem, uint8_t *bin, size_t bin_len, uint32_t base_addr) {
    if (bin_len > MEMORY_SIZE) {
        bin_len = MEMORY_SIZE; // Prevent overflow
    }
    for (size_t i = 0; i < bin_len; i++) {
        mem->data[base_addr + i] = bin[i];
    }
}

void mem_write_u32(rv32i_mem_t *mem, uint32_t addr, uint32_t value) {
    if (addr == MMIO_UART_ADDR) {
        printf("%c", (char)(value & 0xFF)); // Write least significant byte to UART
    }
    else {
        if (addr + 3 < MEMORY_SIZE) {
            mem->data[addr] = (value) & 0xFF;
            mem->data[addr + 1] = ((value) >> 8) & 0xFF;
            mem->data[addr + 2] = ((value) >> 16) & 0xFF;
            mem->data[addr + 3] = ((value) >> 24) & 0xFF;
        }
    }
}

uint32_t mem_read_u32(rv32i_mem_t *mem, uint32_t addr) {
    uint32_t value;
    if (addr <= MEMORY_SIZE - 4) {
        value = mem->data[addr] |
                 (mem->data[addr + 1] << 8) |
                 (mem->data[addr + 2] << 16) |
                 (mem->data[addr + 3] << 24);
    } else {
        value = 0;
    }
    return value;
}