.syntax unified
.arch armv7-m
.cpu cortex-m4

.thumb

.global _start

_start:
  ldr r0, = 0xdeadbeef          // sentence
  ldr r1, = 0x100               // counter 1
  ldr r2, = 0x10000000          // address 1
  ldr r3, = 0x100               // counter 2
  ldr r4, = 0x10000300          // address 2
  ldr r5, = 0x10000000          // address zone for copy
  ldr r6, = 0x0                 // auxiliar variable

loop1:
  str r0, [r2]            // RAM[r2] = r0 :  save the value of the sentence in the RAM with the address specified
  add r2, r2, #4          // r2 = r2 + 4 : increase the value of the address in 4 because the sentence need 4 Bytes in memory for be written
  subs r1, r1, #4         // r1 = r1 - 4 : decrease the counter in 4 because the goal is fill a memory zone with a size 0x100, and each word takes 4 Bytes in memory
  bne loop1               // do the loop until r1 = 0 : r1 represents the memory zone that has not yet been filled

loop2:
  ldr r6, [r5]            // r6 = RAM[r5] : take the value stored in the direction given by r5 
  str r6, [r4]            // RAM[r4] = r6 : save the value in the direction given by r4
  add r5, r5, #4          // r5 = r5 + 4 : increase the memory direction for take a new value for be stored
  add r4, r4, #4          // r4 = r4 + 4 : increase the memory direction for save a new value in that address
  subs r3, r3, #4         // r3 = r3 - 4 : decrease the counter in 4 : r3 represents the memory zone that has not yet been filled
  bne loop2               // do the loop until r3 = 0

end:
  b end                   // b = branch, is a jump to the target end
