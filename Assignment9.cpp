#include <iostream>
#include <mpi.h>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

int main(int argc, char** argv)
{
	int rank, size;
	int subsize, subsum, intermediate;
	int n = 1000000;
	int h = 0;
	vector<int> a;
	double time_start, time_finish, T;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0)
	{
		for (int i = 0; i < n; i++)
		{
			a.push_back(1);
		}
	}
	subsize = n / size;
	vector<int> sub_a = vector<int>(subsize);
	MPI_Bcast(&subsize, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(&a[0], subsize, MPI_INT, &sub_a[0], subsize, MPI_INT, 0, MPI_COMM_WORLD);
	subsum = 0;
	for (int i = 0; i < subsize; i++)
	{
		subsum += sub_a[i];
	}
	if (rank == 0)
	{
		time_start = MPI_Wtime();
	}
	while (pow(2, h) < size)
	{
		if (rank % (int)pow(2, h + 1) == pow(2,h))
		{
			MPI_Send(&subsum, 1, MPI_INT, rank - pow(2, h), rank, MPI_COMM_WORLD);
			break;
		}
		if (rank % (int)pow(2, h + 1) == 0)
		{
			intermediate = subsum;
			MPI_Recv(&subsum, 1, MPI_INT, rank + pow(2, h), rank + pow(2, h), MPI_COMM_WORLD, &status);
			subsum = intermediate + subsum;
		}
		h++;
	}
	if (rank == 0)
	{
		time_finish = MPI_Wtime();
		cout << subsum << endl;
		cout << time_finish - time_start<<endl;
	}

	MPI_Finalize();
}