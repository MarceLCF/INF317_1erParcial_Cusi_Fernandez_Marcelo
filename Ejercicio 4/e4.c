#include <stdio.h>
#include <omp.h>


int main() {
	int N,i,j;    
    printf("Introduzca N: ");
    scanf("%d", &N);
    int matriz[N][N];
    int vector[N];
    int res[N];

    // Leer
    printf("Introduzca la matriz de %dx%d:\n",N,N);
    #pragma omp parallel for
    {
		for(i = 0; i < N; i++){
			for (j = 0; j < N; j++) {
				int x;
				scanf("%d", &x);
				matriz[i][j] = x;
			}
		}
	}
    
    printf("Introduzca el vector de dimension %d:\n",N);
    #pragma omp parallel for
    {
		for(i = 0; i < N; i++){
			int x;
			scanf("%d", &x);
			vector[i] = x;
		}
	}
       
    // Multiplicación de matriz por vector
	#pragma omp parallel for
	{
		for (i = 0; i < N; i++) {
		    int temp = 0;
		    for (j = 0; j < N; j++) {
		        temp += matriz[i][j] * vector[j];
		    }
		    res[i] = temp;
		}
	}

    printf("\nResultado:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", res[i]);
    }
}
