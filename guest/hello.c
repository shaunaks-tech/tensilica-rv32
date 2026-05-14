/* Bare-metal RV32I guest: prints "Hello from RV32I!\n" via MMIO then halts. */

#define UART_MMIO ((volatile unsigned char *)0xF000)

static void putch(char c) {
    *UART_MMIO = (unsigned char)c;
}

static void puts_mmio(const char *s) {
    while (*s) putch(*s++);
}

void _start(void) {
    puts_mmio("Hello from RV32I!\n");

    /* Count to exercise ALU instructions */
    volatile int sum = 0;
    for (int i = 1; i <= 100; i++) {
        sum += i;
    }

    /* Print sum digit by digit (sum == 5050) */
    puts_mmio("Sum 1..100 = ");
    int n = sum;
    char buf[12];
    int idx = 0;
    if (n == 0) {
        buf[idx++] = '0';
    } else {
        while (n > 0) {
            buf[idx++] = '0' + (n % 10);
            n /= 10;
        }
        /* reverse */
        for (int a = 0, b = idx - 1; a < b; a++, b--) {
            char tmp = buf[a]; buf[a] = buf[b]; buf[b] = tmp;
        }
    }
    for (int i = 0; i < idx; i++) putch(buf[i]);
    putch('\n');

    /* Halt via EBREAK */
    __asm__ volatile("ebreak");

    /* Unreachable — spin so the CPU doesn't fall off the end */
    while (1) {}
}
