#include <iostream>
#include "search.h"
#include <time.h>
#include <fstream>

using namespace std;

void inputarray(int a[], int n, char* filename)
{
    fstream fi(filename, ios::in);
    fi >> n;
    a = new int[n+1];
    for (int i = 1; i <= n; i++)
    {
        fi >> a[i];
    }
}

void GenerateSortedData(int a[], int n)
{
    cin >> n;
    a = new int[n+1];
	a[0] = 0;
    for (int i = 1; i <= n; i++)
	{
		a[i] = (rand() + a[i-1]) % n;
	}
    for (int i = 1; i <= n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

int Fibonaccisearch(int a[], int n, int x)
{
    int fib1 = 0;
    int fib2 = 1;
    int fib = fib1 + fib2;

    while (fib < n)
    {
        fib1 = fib2;
        fib2 = fib;
        fib = fib1 + fib2;
    }
    int offset = 0;
    while (fib > 1) {
        int i = min(offset + fib1, n);

        if (a[i] < x) {
            fib = fib2;
            fib2 = fib1;
            fib1 = fib - fib2;
            offset = i;
        }
        else if (a[i] > x) {
            fib = fib1;
            fib2 = fib2 - fib1;
            fib1 = fib - fib2;
        }
        else return i;
    }
    if (fib2 && a[offset] == x)
        return offset;
    return -1;
}

int runningtime(searchingalgorithms S, int a[], int n, int x)
{
    int start_t = clock();
    S(a, n, x);
    int end_t = clock();
    return end_t - start_t;
}

void output(searchingalgorithms S, int a[], int n, int x)
{
    int i = S(a, n, x);
    if (i > 0)
    {
        cout << "Found " << x << " at index: " << i << endl;
    }
    else
    {
        cout << "Don't find any " << x << " in the array!";
    }
}