#include <stdio.h>
#include <omp.h>

int multiplicacion(int a, int b) {
    int res = 0;
    #pragma omp parallel for reduction(+:res)
    for (int i = 0; i < b; i++) {
        res = res + a;
    }
    return res;
}

int division(int a, int b) {
    int res = 0;
    while (a >= b) {
        a = a - b;
        res++;
    }
    return res;
}

int main() {
    //valores
    int x = 12, y = 4;
    
    printf("MULTIPLICACION: %d * %d = %d\n\n", x, y, multiplicacion(x, y));
    
    printf("DIVISION: %d / %d = %d\n\n", x, y, division(x, y));

    return 0;
}