#include <stdio.h>
#include <omp.h>

int main() {
	int N,M;
	printf("Numero de terminos: ");
	scanf("%d",&N);
	
	printf("Numero de procesadores: ");
	scanf("%d",&M);
	
    int serie[M][N]; 
    #pragma omp parallel num_threads(M)
    {
        int idh = omp_get_thread_num(); //ID de hilo
        int ini = idh * (N/M);

        for (int i = 0; i < N/M; i++)
            serie[idh][i] = (ini + i + 1) * 2;
    }

    printf("Serie:\n");
    for (int i = 0; i < M; i++) {
        printf("Procesador %d:", i);
        for (int j = 0; j < N/M; j++)
            printf(" %d", serie[i][j]);
        printf("\n");
    }
}
