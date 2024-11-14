#include "memfuncs.h"

extern uint8_t _bss_start, _bss_end;
extern uint8_t _data_start, _data_end, _data_src;
extern uint8_t _text_start, _text_end, _text_src;
extern uint8_t _isr_start, _isr_end, _isr_src;

void __attribute__((section(".bootloader"))) init_bss(){
    memset(&_bss_start, 0, &_bss_end - &_bss_start);
}   

void __attribute__((section(".bootloader"))) init_data(){
    memcpy(&_data_start, &_data_src, &_data_end - &_data_start);
}

void __attribute__((section(".bootloader"))) init_text(){
    memcpy(&_text_start, &_text_src, &_text_end - &_text_start);
}

void __attribute__((section(".bootloader"))) init_isr(){
    memcpy(&_isr_start, &_isr_src, &_isr_end - &_isr_start);
}
