#include <stdint.h>
#include <stdbool.h>
#include "rv32i.h"
#ifndef MEMORY_H
#define MEMORY_H
#define MEMORY_SIZE 65536 // 64KB

typedef struct {
    uint8_t data[MEMORY_SIZE];
} rv32i_mem_t;

#endif 