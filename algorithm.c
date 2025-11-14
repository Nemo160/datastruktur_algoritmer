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

int partition(int *arr, int low, int high){

    /*pivot at the end. j at - 1
    if j< pivot increment i++ and swap j with i
    if(j<pivot) -> j = i and i=j 
    if not < then continue
    */
    int pivot = arr[high];
    int i = low-1; 
    for(int j = low; j< high; j++){
        if(arr[j]<pivot){
            //swap(arr[i], arr[j]); might work??
            i++;
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
    int tmp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = tmp;
    return i + 1; //return pivot point: i stops where pivot is larger than arr[j].
}

void swap(int *i, int *j){
    int tmp = *i;
    *j = *i;
    *i = tmp;
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
    
    printf("BUBBLE: BEFORE SORT\n");
        for(int i =0; i < n; i++){
        printf("%d ", a[i]);
    }
    
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
    
    printf("\nBUBBLE: AFTERSORT\n\n");
    for(int i =0; i< n; i++){
        printf("%d ", a[i]);
    }
        
    
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

void quick_sort(int *a, int low, int high)
{
    //utgår från att n redan är första pivot point
    if(low < high){
        int p = partition(a,low,high);
        /*för left används p-1 som nya pivot point. Mitten - 1 för att få högsta index för vänstra array
        och för right används n blir nya pivot. Mitten +1 för att få lägsta index på högra*/
        quick_sort(a,low,p-1); //left 
        quick_sort(a,p+1,high); //right
    }
    //high is the value that is being compared. high = a[last index]
    //low index is the first index of array
	
}

bool linear_search(const int *a, int n, int v)
{

    for(int i = 0; i<n; i++){
        if(a[i]== v){
            return true;
        }
    }
    //v från main som input?
	return false; // TODO: linear search
}

bool binary_search(const int *a, int n, int v)
{

    //v = input
    //
	//test
	return false; // TODO: binary search
}

