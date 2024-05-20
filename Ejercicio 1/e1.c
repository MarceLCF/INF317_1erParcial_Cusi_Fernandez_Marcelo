#include <stdio.h>

void suma(int*a, int*b, int*r){
    *r = *a + *b;
}

void resta(int*a, int*b, int*r){
    *r = *a - *b;
}

void multiplicacion(int*a, int*b, int*r){
    *r = 0;
    for(int i=0; i<*b; i++){
        suma(r, a, r);
        //suma(&*r, a, &*r);
    }
}

void division(int*a, int*b, int*r){
    *r = 0;
    while(*a >= *b){
        resta(a,b,a);
        *r += 1;
    }
}

int main() {
    int x, y, res;
    printf("Introduzca valor x: ");
    scanf("%d",&x);
    
    printf("Introduzca valor y: ");
    scanf("%d",&y);
    
    //punteros
    int *p1 = &x;
    int *p2 = &y;
    
    suma(p1, p2, &res);
    printf("\nSUMA: %d + %d = %d\n\n", *p1, *p2, res);

    resta(p1, p2, &res);
    printf("RESTA: %d - %d = %d\n\n", *p1, *p2, res);

    multiplicacion(p1, p2, &res);
    printf("MULTIPLICACION: %d * %d = %d\n\n", *p1, *p2, res);

    printf("DIVISION: %d / %d = ", *p1, *p2);
    division(p1, p2, &res);
    printf("%d\n", res);

    return 0;
}
