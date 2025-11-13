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
int find_pivot_index(){
    return 15;
}
void quick_recursive(int arr, int start, int end){
    
    if(start <= end) return;
    int pivot = find_pivot_index(arr,start,end);
    quick_recursive(arr,start,pivot-1);
}


void test_printarray(int *a, int n){
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

void bubble_sort(int *a, int n)
{
    /*
    printf("BUBBLE: BEFORE SORT\n");
        for(int i =0; i < n; i++){
        printf("%d ", a[i]);
    }
        */
    //n = size
   for(int i = 0; i < n;i++){
        for(int j = 0 ; j < n - 1; j++){
            if(a[j] > a[j+1]){
                int tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
            }
        }
    }
    /*
    printf("\nBUBBLE: AFTERSORT\n\n");
    for(int i =0; i< n; i++){
        printf("%d ", a[i]);
    }
        */
    
}

void insertion_sort(int *a, int n)
{
    /*INSERTION: 
    1. Börja på element 2 (i=1) och lägg det i temp
    kontrollera om talet till vänster är mindre än tmp
    talet är större flytta det till höger. REPEAT
    */
    printf("INSERTION: BEFORE SORT\n");
    for(int i =0; i < n; i++){ printf("%d ", a[i]); }    
  
    for(int i = 1; i<n;i++){
        int tmp = a[i];
        int j = i-1;
        while(j >=0  && a[j] > tmp){
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = tmp;
    }
    printf("\nINSERTION: AFTERSORT\n\n");
    for(int i =0; i< n; i++){ printf("%d ", a[i]); }
    
	// TODO: insertion sort
}

void quick_sort(int *a, int n)
{
	// TODO: quick sort
}

bool linear_search(const int *a, int n, int v)
{
    //v från main som input?
	return false; // TODO: linear search
}

bool binary_search(const int *a, int n, int v)
{
	//test
	return false; // TODO: binary search
}

