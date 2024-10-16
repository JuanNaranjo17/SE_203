.syntax unified
.arch armv7-m
.cpu cortex-m4

.thumb

.global _start

_start:
    ldr r0, = message                   // message direction

    ldr r1, = 0x10000100                // destination address memory 1
    bl copy                             // call the subroutine for copy a sentence

    ldr r1, = 0x10000200                // destination address memory 2
    bl copy                             // call the subroutine for copy a sentence

    ldr r1, = 0x10000300                // destination address memory 3
    bl copy                             // call the subroutine for copy a sentence

    ldr r1, = 0x10000400                // destination address memory 4
    bl copy                             // call the subroutine for copy a sentence

    ldr r1, = 0x10000500                // destination address memory 5
    bl copy                             // call the subroutine for copy a sentence

end:
    b end                               // keep in an infinity loop, an usual practice in embedded systems

copy:
    mov r2, r0                          // encapsulate the register r0 in another register r2 for avoid modify the value of the message direction (r0)
    mov r3, r1                          // encapsulate the register r1 in another register r3 for avoid modify the address where to write the sentence (r1)

copy_loop:
    // As the sentence could have a number of Bytes no specified, we write the all sentence by each Byte
    ldrb r4, [r2]                       // r4 = RAM[r2] : Obtain the Byte in the address memory r2
    strb r4, [r3]                       // RAM[r3] = r4 : Write the Byte in the address memory r3
    add r3, r3, #1                      // r3 = r3 + 1 : Increase r3 in one to obtain the next address for copy the next Byte
    add r2, r2, #1                      // r2 = r2 + 1 : Increase r2 in one to obtain the next Byte in the message to be copied
    cmp r4, #0                          // Compare if the Byte in the sentence represented by r4 is equal to 0, that means that the character is null, so is the end
    bne copy_loop                       // Repeat until r4 be null, all the bits of the Byte equal 0

    bx lr                               // Back to the caller section of code

.section .data                          // The message is saved in the memory program section named as data, in fact is the directive data

message:                                // Define the message for be stored, the compiler will define by itself the address for store it
    .string "Bonjour le monde!"
    .byte 0
