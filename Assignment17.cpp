#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	int size, rank, position, i;
	char s_a[20], s_b[20];
	float a[10];
	char b[10], buf[100];
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	for (i = 0; i < 10; i++) {
		a[i] = rank + 1.0;
		if (rank == 0) b[i] = 'a';
		else b[i] = 'b';
	}
	if (rank == 0)
	{
		cout << "Before packing and distribution"<<endl;
	}
	for (i = 0; i < 20; i++)
	{
		if (i % 2 == 0)
		{
			s_a[i] = (int)a[i/2] + 48;
			s_b[i] = b[i/2];
		}
		else
		{
			s_a[i] = ' ';
			s_b[i] = ' ';
		}
	}
	cout << "Rank: " << rank << " a= [ "<<((string)s_a).substr(0,20)<<"]" << " b= [ " << ((string)s_b).substr(0, 20) << "]"<< endl;
	position = 0;

	if (rank == 0) {
		MPI_Pack(a, 10, MPI_FLOAT, buf, 100, &position, MPI_COMM_WORLD);
		MPI_Pack(b, 10, MPI_CHAR, buf, 100, &position, MPI_COMM_WORLD);
		MPI_Bcast(buf, 100, MPI_PACKED, 0, MPI_COMM_WORLD);
	}
	else {
		MPI_Bcast(buf, 100, MPI_PACKED, 0, MPI_COMM_WORLD);
		position = 0;
		MPI_Unpack(buf, 100, &position, a, 10, MPI_FLOAT, MPI_COMM_WORLD);
		MPI_Unpack(buf, 100, &position, b, 10, MPI_CHAR, MPI_COMM_WORLD);
	}
	if (rank == 0)
	{
		cout << "After packing and distribution"<<endl;
	}
	for (i = 0; i < 20; i++)
	{
		if (i % 2 == 0)
		{
			s_a[i] = (int)a[i / 2] + 48;
			s_b[i] = b[i / 2];
		}
		else
		{
			s_a[i] = ' ';
			s_b[i] = ' ';
		}
	}
	cout << "Rank: " << rank << " a= [ " << ((string)s_a).substr(0, 20) << "]" << " b= [ " << ((string)s_b).substr(0, 20) << "]" << endl;
	MPI_Finalize();
}