#include "algorithm.h"

//
// Private
//
int partition(int *arr, int low, int high){
    /*Nya pivot point blir sista talet i arrayen
    if j< pivot increment i++ and swap i with j.
    Alltså if(a[j] < pivot) -> i blir j (i=j) och i blir nya j (i=j) 
    if not < then continue j++
    */
    int pivot = arr[high]; //high är slutet av arrayen (för varje subarray)
    int i = low-1; //a[0]-1
    for(int j = low; j < high; j++){
        if(arr[j]<pivot){
            //swap(arr[i], arr[j]); might work??
            i++;
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
    //i stannar där (pivot > a[i]) men också (pivot < a[i+1])
    /*Alltså är i+1 platsen där a[high] ska sitta, 
    vilket också innebär att talet a[i+1] måste byta plats med a[pivot].
    Slutligen returnerar vi indexen i+1 som får bli vår nya pivot för vänster och höger array vid nästa anrop
    */
    int tmp = arr[i+1]; //sätter talet efter i till tmp
    arr[i+1] = arr[high]; // i+1 är då talet
    arr[high] = tmp;
    return i + 1;
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

void quick_sort(int *a, int low, int high)
{
    //utgår från att n redan är första pivot point
    if(low < high){
        int p = partition(a,low,high);
        /*för left används p-1 som nya pivot point. Mitten - 1 för att få högsta index för vänstra array
        och för right blir high nya pivot. Mitten +1 för att få lägsta index på högra*/
        quick_sort(a,low,p-1); //left 
        quick_sort(a,p+1,high); //right
    }
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
    int low = 0; 
    int high = n - 1;
    int middle = (high /2);

    while (low <= high) {
        if(v == a[middle]){
            return true;
        }
        else if(v > a[middle]){ //om v är större än middle så vill vi kolla höger
            low = middle;
            middle = ((high - low)/2)+low;
        } 
    
        else{   //kontrollera vänster sida då v > middle och v != middle. Leta på vänster.
            
            high = middle;; //nya high är 
            middle /=2;
        }
    }
	return false; // TODO: binary search
}

