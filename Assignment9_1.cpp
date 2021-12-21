#include <iostream>
#include <mpi.h>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

int main(int argc, char** argv)
{
	int rank, size;
	int subsize, subsum, sum;
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
	MPI_Reduce(&subsum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (rank == 0)
	{
		time_finish = MPI_Wtime();
		cout << sum << endl;
		cout << time_finish - time_start<<endl;
	}
	MPI_Finalize();
}