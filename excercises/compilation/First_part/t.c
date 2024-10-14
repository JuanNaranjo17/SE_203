#include <stdint.h>

void g(){
}

uint32_t a; // global variable
__attribute__((naked)) void f() {
    for (uint8_t i=0; i<=a; i++)
    g();
}