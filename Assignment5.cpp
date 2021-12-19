#include <iostream>
#include "mpi.h"
#define NTIMES 100
using namespace std;

int main(int argc, char** argv)
{
	int rank, n, i;
	double message, rang, time_start, time_finish;
	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	time_start = MPI_Wtime();
	for (int j = 0; j < NTIMES; j++)
	{
		if (rank == 4)
		{
			//cout << "Hello from process " << rank << "\n";
			for (i = 1; i < n; i++) {
				MPI_Recv(&message, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
				//cout << "Hello from process " << message << endl;
			}
		}
		else
		{
			rang = (double)rank;
			MPI_Send(&rang, 1, MPI_DOUBLE, 4, 4, MPI_COMM_WORLD);
		}
		time_finish = MPI_Wtime();
	}
	cout <<"rank "<<rank<<" " << "time=" << (time_finish - time_start) / NTIMES << endl;
	MPI_Finalize();
}