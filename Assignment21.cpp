﻿#include <stdio.h>
#include "mpi.h"

using namespace std;
int main(int argc, char** argv)
{
	int rank;
	int bufsize = 250;
	MPI_Init(&argc, &argv);
	MPI_File fh;
	char buf[bufsize];
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_File_open(MPI_COMM_WORLD, "file1.txt", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
	MPI_File_set_view(fh, rank * bufsize, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);
	MPI_File_read_all(fh, buf, bufsize, MPI_CHAR, MPI_STATUS_IGNORE);
	printf("process %d, buf=%s\n", rank, buf);
	MPI_File_close(&fh);
	MPI_Finalize();
}