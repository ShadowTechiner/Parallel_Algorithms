#include <stdio.h>
#include "mpi.h"
#include <iostream>
using namespace std;
int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	int rank, n, i;
	double message;
	double rang;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 4)
	{
		cout << "Hello from process " << rank << "\n";
		for (i = 1; i < n; i++) {
			MPI_Recv(&message, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			cout << "Hello from process " << message << endl;
		}
	}
	else 
	{
		rang = (double)rank;
		MPI_Send(&rang, 1, MPI_DOUBLE, 4, 4, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}