#include "memfuncs.h"

void __attribute__((section(".bootloader"))) *memcpy(void *dest, const void *src, size_t n) {
    uint8_t *d = dest;
    const uint8_t *s = src;
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}

void __attribute__((section(".bootloader"))) *memmove(void *dest, const void *src, size_t n) {
    uint8_t *d = dest;
    const uint8_t *s = src;
    if (d < s) {
        while (n--) {
            *d++ = *s++;
        }
    } else {
        d += n;
        s += n;
        while (n--) {
            *(--d) = *(--s);
        }
    }
    return dest;
}


void __attribute__((section(".bootloader"))) *memset(void *s, int c, size_t n) {
    uint8_t *p = s;
    while (n--) {
        *p++ = (uint8_t)c;
    }
    return s;
}


int __attribute__((section(".bootloader"))) memcmp(const void *s1, const void *s2, size_t n) {
    const uint8_t *p1 = s1;
    const uint8_t *p2 = s2;
    while (n--) {
        if (*p1 != *p2) {
            return *p1 - *p2;
        }
        p1++;
        p2++;
    }
    return 0;
}

