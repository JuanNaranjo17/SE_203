#include <stdint.h>

extern uint8_t _bss_start, _bss_end;

void init_bss() {
    uint8_t* bss = &_bss_start;
    while (bss < &_bss_end) {
        *bss++ = 0;  // Each bit is inicialized in 0
    }
}
