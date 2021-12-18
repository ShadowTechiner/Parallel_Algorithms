#include <iostream>
#include <ctime>
#include <omp.h>
#include <cstdlib>
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
    int N = atoi (argv[1]);
    vector<vector<int>> A(N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i].push_back(rand()/1000);
        }
    }
    vector<vector<int>> B(N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            B[i].push_back(rand() / 1000);
        }
    }
    vector<vector<int>> C(N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            C[i].push_back(0);
        }
    }
    
    double start_time = 0;
    double delta=0;
    double end_time = 0;
    int eff = 0;
    for (int num = 1; num < 11; num++)
    {
        start_time = omp_get_wtime();
#pragma omp parallel num_threads(num)
        {
#pragma omp for collapse(3)
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    for (int k = 0; k < N; k++)
                    {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }
        end_time = omp_get_wtime();
        delta = end_time-start_time;
        if (num == 1)
        {
            eff = delta;
        }
        cout << "ijk-order " <<num<<" " << delta <<" "<<eff/delta<< endl;
    }
    for (int num = 1; num < 11; num++)
    {
        start_time = omp_get_wtime();
#pragma omp parallel num_threads(num)
        {
#pragma omp for collapse(3)
            for (int i = 0; i < N; i++)
            {
                for (int k = 0; k < N; k++)
                {
                    for (int j = 0; j < N; j++)
                    {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }
        end_time = omp_get_wtime();
        delta = end_time - start_time;
        if (num == 1)
        {
            eff = delta;
        }
        cout << "ikj-order " << num << " " << delta <<" "<<eff/delta<< endl;
    }

    for (int num = 1; num < 11; num++)
    {
        start_time = omp_get_wtime();
#pragma omp parallel num_threads(num)
        {
#pragma omp for collapse(3)
            for (int j = 0; j < N; j++)
            {
                for (int i = 0; i < N; i++)
                {
                    for (int k = 0; k < N; k++)
                    {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }
        end_time = omp_get_wtime();
        delta = end_time - start_time;
        if (num == 1)
        {
            eff = delta;
        }
        cout << "jik-order " << num << " " << delta << " "<< eff/delta<< endl;
    }
    for (int num = 1; num < 11; num++)
    {
        start_time = omp_get_wtime();
#pragma omp parallel num_threads(num)
        {
#pragma omp for collapse(3)
            for (int j = 0; j < N; j++)
            {
                for (int k = 0; k < N; k++)
                {
                    for (int i = 0; i < N; i++)
                    {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }
        end_time = omp_get_wtime();
        delta = end_time - start_time;
        if (num == 1)
        {
            eff = delta;
        }
        cout << "jki-order " << num << " " << delta <<" "<<eff/delta<< endl;
    }
    for (int num = 1; num < 11; num++)
    {
        start_time = omp_get_wtime();
#pragma omp parallel num_threads(num)
        {
#pragma omp for collapse(3)
            for (int k = 0; k < N; k++)
            {
                for (int j = 0; j < N; j++)
                {
                    for (int i = 0; i < N; i++)
                    {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }
        end_time = omp_get_wtime();
        delta = end_time - start_time;
        if (num == 1)
        {
            eff = delta;
        }
        cout << "kji-order " << num << " " << delta <<" " << eff/delta<< endl;
    }
    for (int num = 1; num < 11; num++)
    {
        start_time = omp_get_wtime();
#pragma omp parallel num_threads(num)
        {
#pragma omp for collapse(3)
            for (int k = 0; k < N; k++)
            {
                for (int i = 0; i < N; i++)
                {
                    for (int j = 0; j < N; j++)
                    {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }
        end_time = omp_get_wtime();
        delta = end_time-start_time;
        if (num == 1)
        {
            eff = delta;
        }
        cout << "kij-order " <<num<<" " << delta <<" " <<eff/delta<< endl;
    }
}

