#include <stdio.h>
#include "mpi.h"
#include <math.h>
#define n 1000

void smod5(void *a, void *b, int *l, MPI_Datatype *type) {
	int i;
	for (i = 0; i < *l; i++)
		((int*)b)[i] = (((int*)a)[i] + ((int*)b)[i]) % 5;
}

void FindMaximum(void* a, void* c, int *len, MPI_Datatype* type)
{
	for (int i = 0; i < *len; i++)
	{
		if (((int*)c)[i] < ((int*)a)[i])
		{
			((int*)c)[i] = ((int*)a)[i];
		}
	}
}

int main(int argc, char **argv)
{
	int rank, size, i;
	int a[n];
	int b[n];
	int c[n];
	MPI_Init(&argc, &argv);
	MPI_Op op;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	for (i = 0; i < n; i++) a[i] = i - (rank-4)*(rank-2);
	printf("process %d a[0] = %d\n", rank, a[0]);
	//MPI_Op_create(&smod5, 1, &op);
	//MPI_Reduce(a, b, n, MPI_INT, op , 0, MPI_COMM_WORLD);
	//if (rank == 0) printf("b[0] = %d\n", b[0]);
	MPI_Op_create(&FindMaximum, 1, &op);
	MPI_Reduce(a, c, n, MPI_INT, op , 0, MPI_COMM_WORLD);
	MPI_Op_free(&op);
	if (rank == 0) printf("Custom Function: c[0] = %d\n", c[0]);
	MPI_Reduce(a, c, n, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	if (rank==0) printf("MPI_Reduce: c[0] = %d\n", c[0]);
	MPI_Finalize();
}