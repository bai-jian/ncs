# i386-emulator

An emulator of the i386 computer system, including i386 CPU (isa, reg, mm, int, io), RAM (two levels of cache, dram), and peripheral devices (serial, ide, timer, keyboard, vga).

After the emulator boots and then loads the mini kernel which initializes the emulator, it can execute programs which are compatible with i386 isa.

### COMPATIBILITY

- Support only 80386 protection mode
    - No support for backward compatibility with 80286, etc
    - No support for 80386 real-address mode and virtual 8086 mode
- No support for 16-bit addressing instruction
