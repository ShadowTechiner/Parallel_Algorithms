#include <iostream>
#include <mpi.h>
#include <vector>
using namespace std;
int main(int argc, char** argv)
{
	int rank, size;
	int sum = 0;
	int sum_proc, sum_extra;
	int residual;
	int x, y;
	int n = 1000000;
	vector<int> a;
	vector<int> b;
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
		for (int i = 0; i < n; i++)
		{
			b.push_back(1);
		}
		for (int i = 1; i < size; i++)
		{
			MPI_Send(&a[(i-1)*n/(size-1)], n/(size-1), MPI_INT, i , 0, MPI_COMM_WORLD);
			MPI_Send(&b[(i - 1) * n / (size - 1)], n / (size - 1), MPI_INT, i, 0, MPI_COMM_WORLD);
			MPI_Recv(&sum_proc, 1, MPI_INT, i, 1, MPI_COMM_WORLD, &status);
			sum += sum_proc;
		}
		residual = n % (size - 1);
		for (int i = residual+1; i < size; i++)
		{
			x = 0;
			y = 0;
			MPI_Send(&x, 1, MPI_INT, i, 2, MPI_COMM_WORLD);
			MPI_Send(&y, 1, MPI_INT, i, 2, MPI_COMM_WORLD);
			MPI_Recv(&sum_extra, 1, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
		}
		while (residual != 0)
		{
			x = a[a.size() - residual];
			y = b[b.size() - residual];
			MPI_Send(&x, 1, MPI_INT, residual, 2, MPI_COMM_WORLD);
			MPI_Send(&y, 1, MPI_INT, residual, 2, MPI_COMM_WORLD);
			MPI_Recv(&sum_extra, 1, MPI_INT, residual, 2, MPI_COMM_WORLD, &status);
			sum += sum_extra;
			residual = residual - 1;
		}
		cout << "The scalar product of vectors a and b: "<<sum;
	}
	else
	{
		a.resize(n);
		b.resize(n);
		MPI_Recv(&a[(rank - 1) * n / (size - 1)], n / (size - 1), MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Recv(&b[(rank - 1) * n / (size - 1)], n / (size - 1), MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		sum_proc = 0;
		for (int i = 0; i < n; i++)
		{
			sum_proc += a[i]*b[i];
		}
		MPI_Send(&sum_proc, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		MPI_Recv(&x, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
		MPI_Recv(&y, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
		sum_extra = x * y;
		MPI_Send(&sum_extra, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
	}
	MPI_Finalize();
}
