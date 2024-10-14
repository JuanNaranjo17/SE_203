.syntax unified
.arch armv7-m
.cpu cortex-m4

.thumb

.global _start

_start:
    // Instance of the parameters for the loop execution

    mov r0, #0          // We use r0 as the counter
    ldr r1, =a          // r1 = &a
    ldr r1, [r1]        // r1 = RAM[&a] then r1 = a : We use r1 as the limit for the for

loop:
    // Loop condition
    cmp r0, r1          // r0 - r1
    bgt end             // bit greater than: r0 > r1, if r0 is greater than r1, it means that we did all the loop executions, then the loop is finished
    // Loop body
    bl g                // Go to execute the subroutine g
    add r0, r0, #1      // r0 = r0 + 1, increase the counter, like a loop for a sentence in C
    b loop              // Repeat the loop until the condition bgt end be executed
  
g:
    // ... code         // subrutine g
    bx lr               // back to the main loop

end:
    b end               // b = branch, is a jump to the target end

.section .data:         // Section data in the hardware memory

a:                      // Define the value of a variable a in the data zone of memory, the address is defined by the compiler by itself
    .word 0x0000000a
