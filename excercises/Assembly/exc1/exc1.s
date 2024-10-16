.syntax unified
.arch armv7-m
.cpu cortex-m4

.thumb

.global _start

_start:
  ldr r0, = 0xdeadbeef          // sentence
  ldr r1, = 0x100               // counter
  ldr r2, = 0x10000000          // address

loop:
  str r0, [r2]            // RAM[r2] = r0 : save the value of the sentence in the RAM with the address specified
  add r2, r2, #4          // r2 = r2 + 4  : increase the value of the address in 4 because the sentence need 4 Bytes in memory for be written
  subs r1, r1, #4         // r1 = r1 - 4  : decrease the counter in 4 because the goal is fill a memory zone with a size 0x100, and each word takes 4 Bytes in memory
  bne loop                // do the loop until r1 = 0 : r1 represents the memory zone that has not yet been filled

end:
  b end                   // b = branch, is a jump to the target end
