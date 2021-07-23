#include <iostream>
#include "search.h"
#include <time.h>
#include <fstream>
#define oo 1000000007
using namespace std;

void GenerateSortedData(int*& a, int& n)
{
    cin >> n;
    a = new int[n+1];
	a[0] = 0;
    for (int i = 0; i <= n; i++)
	{
        int x = rand() % n;
        a[i] = (x >= a[i-1]) ? x : a[i-1] + rand() % 100;
	}
}

//jumpSearch
int jumpSearch(int a[], int n, int x) {
    int step = sqrt(n);	//step is sqrt of n . example: n=9--> step =3   n=15--> step=3
    int prev = 0;  //prev is the variable to save the starting position
    //find element x
    int jump = step;
    while (a[jump - 1] < x)
    {
        prev = jump;
        jump += step;
        if (jump > n)
            jump = n;

        if (prev >= n)
            return -1;
    }
    int mid;
    while (prev <= jump)
    {
        mid = (prev + jump) / 2;

        if (a[mid] == x)	return mid;
        // if x > a[mid] , x will just to the right of mid
        if (x > a[mid])
            prev = mid + 1;
        else		// else x<a[mid] , x will just to the left of mid
            jump = mid - 1;
    }

}

int BinarySearch(int* a, int l, int r, int k) {
    while (l <= r) {
        int m = (l + r) / 2;
        if (a[m] == k)
            return m;
        if (k > a[m])
            l = m + 1;
        else
            r = m - 1;
    }
    //if we can't find the elements, return -1
    return -1;
}

int ExponetialSearch(int* a, int n, int k) {       //array must be sorted in ascending order
    if (a[0] == k)
        return 0;
    int i = 1;

    while (i < n && a[i] < k)
        i *= 2;
    // l = i / 2 because at that index, the elements: a[i] < k
    //call min(i, n - 1) to prevent out of bound
    return BinarySearch(a, i / 2, min(i, n - 1), k);
}

int Fibonaccisearch(int a[], int n, int key)
{
    int fib1 = 0; // 0'th fibonacci = 0
    int fib2 = 1; //1'st fibonacci  = 1
    int fib = fib1 + fib2; //2'nd fibonacci  = 1
    //find i'th fibonacci is smallest and greater than or equal to n to divide the array into 2 parts i-1'th fibonacci elements and i-2'th fibonacci elements
    while (fib < n)
    {
        fib1 = fib2; //i-2'th fibonacci
        fib2 = fib; //i-1'th fibonacci
        fib = fib1 + fib2; //i'th fibonacci
    }
    int flag = 1; //mark the left position
    while (fib > 1) {
        int i = min(flag + fib1, n);
        if (a[i] == key) return i; //found the key in the array
        if (a[i] < key) {
            //the key belongs in the range from i to fib so the subarray is considered to have fib2 elements
            fib = fib2; //i'th fibonacci
            fib2 = fib1; //i-1'th fibonacci
            fib1 = fib - fib2; //i-2'th fibonacci
            flag = i; //the left position is now i
        }
        else {
            //the key belongs in the range from flag to flat+fib1-1 so the subarray is considered to have fib1 elements 
            fib = fib1; //i'th fibonacci
            fib2 = fib2 - fib1; //i-1'th fibonacci
            fib1 = fib - fib2; //i-2'th fibonacci
        }
    }
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
        cout << "Don't find any " << x << " in the array!" << endl;
    }
}