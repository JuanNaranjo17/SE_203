.syntax unified
.arch armv7-m
.cpu cortex-m4

.thumb

.global _start

_start:
    // Instance of memory directions of pointers and the values pointed
    // r0 is the pointer ap, r2 is the pointer bp and r4 is the pointer cp
    // r1, r3 and r5 are the values pointed
  
    ldr r0, =ap           // r0 = &ap then r0 = a
    ldr r1, [r0]          // r1 = RAM[&ap] then r1 = ap
    ldr r2, =bp           // r2 = &bp then r2 = b
    ldr r3, [r2]          // r3 = RAM[&bp] then r3 = bp
    ldr r4, =cp           // r4 = &cp then r4 = c
    ldr r5, [r4]          // r5 = RAM[&cp] then r5 = cp

    // Sum of values pointed

    add r1, r1, r5        // r1 = r1 + r5 = ap + cp
    add r3, r3, r5        // r3 = r3 + r5 = bp + cp

    // Save the values of r1, r3 and r5 in the addresses pointed

    str r1, [r0]          // r1 = *a, r0 = a
    str r3, [r2]          // r3 = *b, r2 = b
    // str r5, [r4]       // r4 = *c, r5 = c, This is not neccesary because the pointer c is not modified

end:
    b end

.section .data            // Section data in the hardware memory

ap:                       // Define the value of a variable ap in the data zone of memory, the address is defined by the compiler by itself
    .global ap            // Define the variables as global for allow them be recognize out of the file
    .word 0x0000000a
bp:
    .global bp
    .word 0x0000000b
cp:
    .global cp
    .word 0x0000000c
