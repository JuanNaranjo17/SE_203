#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const int32_t rodata_instance_cons = 2;
int32_t bss_declaration_var;
int32_t data_instance_var = 4;
// Is not possible do a constant declaration because is not possible change the value after in the program, the constants only alllow instance

int main() {
    int32_t stack_declaration_var;
    int32_t stack_instance_var1 = 8;
    int32_t stack_instance_var2 = 16;
    int32_t *heap_declaration_var = malloc(sizeof(int32_t));

    printf("Main address: %p\n", main);
    printf("ROM data address: %p\n", &rodata_instance_cons);
    printf("Instance static variable in data address: %p\n", &data_instance_var);
    printf("Declaration static variable in bss address: %p\n", &bss_declaration_var);
    printf("Declaration dynamic variable in the stack address: %p\n", &stack_declaration_var);
    printf("Instance dynamic variable 1 in the stack address: %p\n", &stack_instance_var1);
    printf("Instance dynamic variable 2 in the stack address: %p\n", &stack_instance_var2);
    printf("Declaration pointer in the stack address: %p\n", &heap_declaration_var);
    printf("Pointed address in the heap: %p\n", heap_declaration_var);

    return 0;
}
