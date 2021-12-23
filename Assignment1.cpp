#include <iostream>
#include <string>
#include <omp.h>
#include <vector>
#include <ctime>
using namespace std;

int main(int argc, char* argv[])
{
    int x = 0;
    int n = atoi (argv[1]);
    vector<int> array;
    for (int i = 0; i < n; i++)
    {
        array.push_back(rand());
        cout << array[i]<<endl;
    }
    int number = 1;
    for (int j = 1; j < 11; j++)
    {
        double delta = 0;
        for (int k = 0; k < 20; k++)
        {
            double start_time = omp_get_wtime();
#pragma omp parallel num_threads(j)
            {
#pragma omp for reduction(max:x)
                for (int i = 0; i < array.size(); i++)
                {
                    if (x < array[i])
                    {
                        x = array[i];
                    }
                }
            }
            delta += omp_get_wtime() - start_time;
        }
        //cout << "Number of threads:" << j << endl << "Execution Time (s):" << delta/20<<endl;
    }
    cout << "Maximum is " << x << endl;
}
