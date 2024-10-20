#include <stdint.h>         // Library for handle int
#include <stdbool.h>        // library for use the boolean

/*
int i;
int a;
int c;
int h;
*/

int fibo(int n) {
    if (n <= 0) {
        return 0;  // F(0) = 0
    } else if (n == 1) {
        return 1;  // F(1) = 1
    } else {
        return fibo(n - 1) + fibo(n - 2);  // Recursive function
    }
}

int main(){
    //while (true);
    
    return fibo(8);
}
