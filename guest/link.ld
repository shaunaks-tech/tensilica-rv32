OUTPUT_ARCH(riscv)
ENTRY(_start)

MEMORY {
    RAM (rwx) : ORIGIN = 0x00000000, LENGTH = 64K
}

SECTIONS {
    . = 0x00000000;

    .text : {
        *(.text.startup)
        *(.text._start)
        *(.text*)
        *(.rodata*)
    } > RAM

    .data : {
        *(.data*)
        *(.sdata*)
    } > RAM

    .bss : {
        *(.bss*)
        *(.sbss*)
        *(COMMON)
    } > RAM

    /* Stack grows down from top of RAM; reserve 4 KB */
    _stack_top = ORIGIN(RAM) + LENGTH(RAM);
}
