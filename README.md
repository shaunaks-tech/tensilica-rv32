# tenselica-rv32 

A RISC-V RV32I interpreter running on the ESP32's Xtensa core, written in C using ESP-IDF.

> Work in progress — started this to get a better feel for how ISA design translates to actual execution.

## What it does

Executes compiled RV32I binaries on the ESP32 by emulating the full base integer instruction set on top of the Xtensa core. Guest programs are compiled with `riscv64-elf-gcc` targeting `rv32i` and loaded into a flat 64KB RAM array. MMIO at `0xF000` maps character writes to the ESP32's UART so guest output shows up in the serial monitor.

## Why


I wanted to understand what actually happens when a CPU fetches and decodes an instruction, not just in theory but down to the bit manipulation. Writing the decode loop by hand for 37 instructions makes that pretty concrete. The ESP32 was a natural target since I had one sitting around and ESP-IDF gives enough control to keep things interesting.

## Status

- [x] Project scaffold + ESP-IDF build system
- [x] Memory model (flat `uint8_t ram[65536]`)
- [ ] Full RV32I decode/execute loop
- [ ] UART MMIO
- [ ] Guest toolchain + linker script
- [ ] Cycle counter / instructions-per-second

## Project structure

```
rvx32/
├── main/
│   ├── main.c          # app_main, loads guest binary and runs interpreter
│   ├── rv32i.c/.h      # fetch/decode/execute loop, register file, CPU state
│   └── memory.c/.h     # flat RAM model, MMIO handler
├── guest/
│   ├── hello.c         # bare-metal test program (no stdlib)
│   ├── link.ld         # linker script, places program at 0x0
│   └── build_guest.sh  # compiles guest and generates guest_bin.h
└── CMakeLists.txt
```

## Building

### Prerequisites

- [ESP-IDF VS Code extension](https://marketplace.visualstudio.com/items?itemName=espressif.esp-idf-extension) (handles toolchain install)
- `riscv64-elf-gcc` for cross-compiling guest programs:
  ```bash
  brew install riscv64-elf-gcc
  ```

### Build and flash

Open the project in VS Code with the ESP-IDF extension and use the build/flash buttons, or from the terminal:

```bash
idf.py build
idf.py -p /dev/tty.usbserial-* flash monitor
```

### Compile a guest program

```bash
cd guest
./build_guest.sh
```

This compiles `hello.c` targeting `rv32i`, links it at address `0x0`, and outputs `guest_bin.h` which gets included in the main build.

## Hardware

Tested on an ESP32 DevKit v1. Should work on any ESP32 variant with at least 64KB free SRAM for the guest memory array.

## Roadmap

- RV32M extension (multiply/divide)
- Exception handling (EBREAK, illegal instruction trap)
- UART monitor shell — inspect registers, single-step, set breakpoints

## Author

Shaunak Sarlashkar
