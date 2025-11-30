#include "algorithm.h"

//
// Private
//
int partition(int *arr, int low, int high){

    int pivot = arr[high];
    int i = low-1; 
    for(int j = low; j < high; j++){
        if(arr[j]<pivot){
            i++;
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
    
    int tmp = arr[i+1]; 
    arr[i+1] = arr[high]; 
    arr[high] = tmp;
    return i + 1;
}

void quick_sort_internal(int *a, int low, int high)
{
    if(low < high){
        int p = partition(a,low,high);
        quick_sort_internal(a,low,p-1); 
        quick_sort_internal(a,p+1,high); 
    }
}

//
// Public
//

void bubble_sort(int *a, int n)
{   
    for(int i = 0; i < n;i++){
        for(int j = 0 ; j < n - 1; j++){
            if(a[j] > a[j+1]){
                int tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
            }
        }
    }
}

void insertion_sort(int *a, int n)
{
    /*INSERTION: 
    1. Börja på element 2 (i=1) och lägg det i temp
    kontrollera om talet till vänster är mindre än tmp
    talet är större flytta det till höger. REPEAT
    */
    for(int i = 1; i<n;i++){
        int tmp = a[i];
        int j = i-1;
        while(j >=0  && a[j] > tmp){ //medans a[j] är större än a[i]
            a[j+1] = a[j]; 
            j--;
        }
        a[j+1] = tmp;
    }
}



void quick_sort(int *arr, int n){
    quick_sort_internal(arr,0,n-1);
}
bool linear_search(const int *a, int n, int v)
{
    for(int i = 0; i<n; i++){
        if(a[i]== v){
            return true;
        }
    }
    //v från main som input?
	return false; 
}

bool binary_search(const int *a, int n, int v)
{
    int low = 0; 
    int high = n-1;

    while (low <= high) {
        int middle = low + (high-low)/2;

        if(a[middle] == v){
            return true;
        }
        else if(a[middle] < v){ //om v är större än middle så vill vi kolla höger
            low = middle+1;
        } 
    
        else{   
            high = middle-1; //nya high är 
        }
    }
	return false; 
}

