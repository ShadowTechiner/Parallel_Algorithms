#include <cstdlib>
#include "mpi.h"

using namespace std;

int main(int argc, char** argv)
{
	int rank, size;
	double time_start, time_finish;
	double T = 0;
	const int n = 500;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int matrix1[n][n], matrix2[n][n], matrix3[n][n];
	for (int times = 0; times < 10; times++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				matrix1[i][j] = 1;
				matrix2[i][j] = 1;
				matrix3[i][j] = 0;
			}
		}
		MPI_Barrier(MPI_COMM_WORLD); //barrier process synchronization
		time_start = MPI_Wtime();
		for (int i = 0; i < n; i++)
		{
			for (int k = 0; k < n; k++)
			{
				for (int j = 0; j < n; j++)
				{
					matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
				}
			}
		}
		time_finish = MPI_Wtime();
		T+= time_finish - time_start;
	}
	printf("Process %d: Time = %f\n", rank, T/10);
	MPI_Finalize();
}