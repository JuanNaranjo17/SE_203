#include "memfuncs.h"

extern uint8_t _bss_start, _bss_end;
extern uint8_t _data_start, _data_end, _data_src;

void init_bss() {
    memset(&_bss_start, 0, &_bss_end - &_bss_start);
}   

void init_data(){
    memcpy(&_data_start, &_data_src, &_data_end - &_data_start);
}
