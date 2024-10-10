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
  ldr r5, = 0x10000000          // address direction for copy

  bl init                       // subroutine for fill a zone with a specific sentence
  bl copy                       // subroutine for fill a zone with the value filled in another zone

  // We can repeat the copy of a sentence in diferent zones in memory with diferent sizes

  ldr r3, = 0x80                // counter 2
  ldr r4, = 0x10000600          // address 2
  ldr r5, = 0x10000010          // address direction for copy
  bl copy

  // We can repeat the init of a sentence in diferent zones in memory with diferent sizes

  ldr r0, = 0xdead0000          // sentence
  ldr r1, = 0x70                // counter 1
  ldr r2, = 0x10000400          // address 1
  bl init

end:
  b end                   // b = branch, is a jump to the target end

init:
  mov r6, r0              // r6 = r0 : copy the sentence
  mov r7, r1              // r7 = r1 : copy the counter
  mov r8, r2              // r8 = r2 : copy the address

init_loop:
  str r6, [r8]            // RAM[r8] = r6 : save the sentence in a memory address
  add r8, r8, #4          // r2 = r2 + 4 : increase the memory address for save a new sentence
  subs r7, r7, #4         // r1 = r1 - 4 : decrease the counter
  bne init_loop           // do the loop until r7 = 0 : r7 represents the memory zone that has not yet been filled

  bx lr                   // back to the caller section, the PC was saved in the lr register

copy:
  mov r6, 0x0             // variable for read the value to be copied
  mov r7, r3              // r7 = r3 counter
  mov r8, r4              // r8 = r4 address where copy the sentence
  mov r9, r5              // r9 = r5 address where read the sentence for copy

copy_loop:
  ldr r6, [r9]            // r6 = RAM[r9] : obtain the sentence stored in r9 for copy it
  str r6, [r8]            // RAM[r8] = r6 : copy the sentence in the RAM space with the address r8
  add r9, r9, #4          // r9 = r9 + 4 : increase the address for obtain the sentence to copy
  add r8, r8, #4          // r8 = r8 + 4 : increase the address for copy the sentence
  subs r7, r7, #4         // r7 = r7 - 4 : decrease the counter that represents the size of memory that has not yet been filled
  bne copy_loop           // do the loop until r7 = 0

  bx lr                   // back to the caller
