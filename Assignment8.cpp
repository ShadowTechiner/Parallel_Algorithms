#include <iostream>
#include <mpi.h>
#include <vector>
#include <math.h>
using namespace std;
int main(int argc, char** argv)
{
	int rank, size;
	vector<int> message;
	double time_start, time_finish, T;
	long int n = 1000000;
	int N = 10;
	unsigned int L;
	for (int i = 0; i < n; i++)
	{
		message.push_back(1);
	}
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	for (int j = 0; j < n+1; j=j*10)
	{
		if (rank == 0)
		{
			time_start = MPI_Wtime();
		}
		for (int i = 0; i < N; i++)
		{
			if (rank == 0)
			{
				message.resize(j);
				MPI_Send(&message[0], j, MPI_INT, 1, 0, MPI_COMM_WORLD);
				MPI_Recv(&message[0], j, MPI_INT, 1, 1, MPI_COMM_WORLD, &status);
			}
			if (rank == 1)
			{
				MPI_Recv(&message[0], j, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
				MPI_Send(&message[0], j, MPI_INT, 0, 1, MPI_COMM_WORLD);
			}
			time_finish = MPI_Wtime();
		}
		if (rank == 0)
		{
			L = j * sizeof(int);
			T = (time_finish - time_start) / N;
			if (j == 0)
			{
				cout << "Latency= " << T / 2 << " s" << endl;
			}
			cout << "Length= " << L <<" Bytes ; Time " << T << " s ; Bandwidth= " << 2 * L / (1024*1024 * T) << " MB/s" << endl;
		}
		if (j==0) j = j + 1;
	}
	MPI_Finalize();
}