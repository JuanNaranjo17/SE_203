#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void function2(){
    int32_t stack_var4, stack_var5;
    printf("Init address stack var4: %p\n", &stack_var4);
    printf("Init address stack var5: %p\n", &stack_var5);

}

void function1(){
    int32_t stack_var3;
    printf("Init address stack var3: %p\n", &stack_var3);

    function2();

}

int main() {

    int32_t stack_var1;
    printf("Init address stack var1: %p\n", &stack_var1);
    int32_t stack_var2;
    printf("Second address stack var1: %p\n", &stack_var1);
    printf("Init address stack var2: %p\n", &stack_var2);

    function1();

    printf("Final address stack var1: %p\n", &stack_var1);
    printf("Final address stack var2: %p\n", &stack_var2);

    return 0;
}