#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define REQUEST_TERM 1
#define TERM_RESPONSE 2
#define END_WORK 3

// Función para calcular el n-ésimo término de Fibonacci
unsigned long long fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    unsigned long long a = 0, b = 1, c;
    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}

int main(int argc, char* argv[]) {
    int proc, cant, N, MASTER = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc);
    MPI_Comm_size(MPI_COMM_WORLD, &cant);

    if (proc == MASTER) {
        printf("Introducir N: ");
        scanf("%d", &N);
		printf("\n");
        unsigned long long *fib_sequence = malloc(N * sizeof(unsigned long long));
        int term_index = 0;

        // enviar respuesta inicial a los SLAVES
        for (int i = 1; i < cant && term_index < N; ++i) {
            MPI_Send(&term_index, 1, MPI_INT, i, REQUEST_TERM, MPI_COMM_WORLD);
            ++term_index;
        }

        while (term_index < N) {
            unsigned long long term;
            int received_index;
            MPI_Status status;

            // Recibir el termino calculado por un priceso SLAVE
            MPI_Recv(&term, 1, MPI_UNSIGNED_LONG_LONG, MPI_ANY_SOURCE, TERM_RESPONSE, MPI_COMM_WORLD, &status);
            MPI_Recv(&received_index, 1, MPI_INT, status.MPI_SOURCE, TERM_RESPONSE, MPI_COMM_WORLD, &status);
            fib_sequence[received_index] = term;

            // Enviar nueva solicitud a un SLAVE
            MPI_Send(&term_index, 1, MPI_INT, status.MPI_SOURCE, REQUEST_TERM, MPI_COMM_WORLD);
            ++term_index;
        }

        // Juntar los resultado
        for (int i = 1; i < cant; ++i) {
            unsigned long long term;
            int received_index;
            MPI_Status status;

            MPI_Recv(&term, 1, MPI_UNSIGNED_LONG_LONG, MPI_ANY_SOURCE, TERM_RESPONSE, MPI_COMM_WORLD, &status);
            MPI_Recv(&received_index, 1, MPI_INT, status.MPI_SOURCE, TERM_RESPONSE, MPI_COMM_WORLD, &status);
            fib_sequence[received_index] = term;
        }

        // Finalizar los procesos SLAVE
        for (int i = 1; i < cant; ++i) {
            MPI_Send(0, 0, MPI_INT, i, END_WORK, MPI_COMM_WORLD);
        }

        printf("Secuencia de los %d terminos: ", N);
        for (int i = 0; i < N; ++i) {
            printf("%llu ", fib_sequence[i]);
        }
        printf("\n");

        free(fib_sequence);

    } else {
        // proceso SLAVE
        while (1) {
            int term_index;
            MPI_Status status;
            MPI_Recv(&term_index, 1, MPI_INT, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            if (status.MPI_TAG == END_WORK) {
                break;
            }
            unsigned long long term = fibonacci(term_index);
            MPI_Send(&term, 1, MPI_UNSIGNED_LONG_LONG, MASTER, TERM_RESPONSE, MPI_COMM_WORLD);
            MPI_Send(&term_index, 1, MPI_INT, MASTER, TERM_RESPONSE, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}
