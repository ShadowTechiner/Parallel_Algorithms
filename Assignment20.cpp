#include <stdio.h>
#include "mpi.h"
#include <iostream>
#define BUFSIZE 100

using namespace std;
int main(int argc, char** argv)
{
	int bufsize, num, sum;
	char input[250];
	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_File fh;
	char buf[BUFSIZE];
	for (int i = 0; i < 250; i++)
	{
		input[i] = 'H';
	}

	MPI_File_open(MPI_COMM_WORLD, "file.txt", MPI_MODE_CREATE|MPI_MODE_RDWR, MPI_INFO_NULL, &fh);
	MPI_File_write(fh,input,250, MPI_CHAR, &status);
	MPI_File_close(&fh);

	MPI_File_open(MPI_COMM_WORLD, "file.txt", MPI_MODE_RDONLY|MPI_MODE_DELETE_ON_CLOSE, MPI_INFO_NULL, &fh);
	MPI_File_set_view(fh, 0, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);
	sum = 0;
	do {
		MPI_File_read(fh, buf, BUFSIZE, MPI_CHAR, &status);
		MPI_Get_count(&status, MPI_CHAR, &num);
		printf("buf=%s\n", buf);
		sum += num;
	} while (num >= BUFSIZE);
	MPI_File_close(&fh);
	printf("Sum is %d\n", sum);
	MPI_Finalize();
}