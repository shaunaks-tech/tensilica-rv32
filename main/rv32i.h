#include <stdint.h>
#include <stdbool.h>

#ifndef RV32I_H
#define RV32I_H
#define RV32I_RESET_ADDR 0x00000000
#define NUM_REGS 32

typedef struct {
    uint32_t reg[NUM_REGS]; // 32 registers
    uint32_t pc;
    bool halted;
    uint32_t cycle_count;
} rv32i_cpu_t;

#endif 
