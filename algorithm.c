#include "algorithm.h"
#include <stdio.h>
//
// Private
//

//
// Public
//

//1 for loop = O(n)
//2 nested forloop = O(n^2)
//3 recursive with halving = O(log n)
//4 recursive with two calls = O(2^n)

void bubble_sort(int *a, int n)
{
printf("\nIn bubblesort func!\n");
    printf("First 3: ");
    for(int i = 0; i < 3; i++)
    {
        printf("%d ", a[i]);
    }

    printf("\nLast 3: ");
    for(int i = (n - 3); i < n; i++)
    {
        printf("%d ", a[i]);
    }

    printf("\n\n");
}

void insertion_sort(int *a, int n)
{
	// TODO: insertion sort
}

void quick_sort(int *a, int n)
{
	// TODO: quick sort
}

bool linear_search(const int *a, int n, int v)
{
	return false; // TODO: linear search
}

bool binary_search(const int *a, int n, int v)
{
	return false; // TODO: binary search
}
