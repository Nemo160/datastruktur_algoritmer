#include "analyze.h"
#include "algorithm.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//
// Private
//

//
// Public
//

void sorted_array(int *arr, int size){
  for (int i = 0; i < size; i++) {
    arr[i] = i;
  }
}
void reverse_sorted_array(int *arr, int size){
  for (int i = size-1; i >= 0; i--) {
    arr[i] = (size-1)- i;
  }
}

void random_array(int *arr, int size){
  for (int i = 0; i < size; i++){
    arr[i] = rand() % size;
  }
}

void populate_array(const algorithm_t a, const case_t c, int *arr, int size) {
  if (a == bubble_sort_t || a == insertion_sort_t) {
    switch (c) {
    case best_t:
    printf("\nBEST CASE: \n");
      for (int i = 0; i < size; i++) {
        arr[i] = i;
      }
      break;

    case worst_t:
    printf("\nWORST CASE: \n");
      for (int i = size-1; i >= 0; i--) {
        arr[i] = (size -1) - i;
      }

      return;
  printf("\nAVERAGE CASE: \n");
    case average_t:
      for (int i = 0; i < size; i++){
        arr[i] = rand() % size;
      }
      break;
    }

    if(a == quick_sort_t ){

    }
  }
}

void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n) {
    int size = SIZE_START;
    //n = 1;
    time_t time_start, time_end;
    printf("INPUT HERE:\n");
    int input;
    input = scanf("%d", &input);

    for (int j = 0; j < 1; j++) {
        int array[size];
        if(a == bubble_sort_t){
          printf("\nIN BUBBLESORT\n");
          double time_used = 0;
          populate_array(a, c, array, size);
          printf("SIZE: %d\n", size);

          time_start = clock();
          bubble_sort(array, size);
          time_end = clock();
         
          time_used = ((double)(time_end - time_start)) / CLOCKS_PER_SEC;

          printf("TIME: %f\n", time_used);

          buf[j].time = time_used;
          buf[j].size = size;

        }
        else if(a == insertion_sort_t){
          populate_array(a, c, array, size);
          insertion_sort(array,size);
        }
        else if(a == linear_search_t){
        double time_used = 0;

        sorted_array(array, size);
        time_start = clock();

        bool found = linear_search(array, size, input);
        time_end = clock();
        time_used = ((double)(time_end - time_start)) / CLOCKS_PER_SEC;

        buf[j].time = time_used;
        buf[j].size = size;

          printf("FOUND HERE: %d\n", found);

        } 

        else if(a == quick_sort_t){
          reverse_sorted_array(array, size);
          printf("NONSORTED ARRAY: \n");
          for(int i =0; i< size;i++){
            printf("%d ", array[i]);
          }
          int low = sizeof(array)/sizeof(array[0]);
          printf("low %d, array[0]%d, sizeofarray%d\n", low, array[0],sizeof(array));
          printf("size:%d\n",size);
          quick_sort(array,0, low-1);

          printf("QUICKSORTED ARRAY\n\n");
          for(int i =0; i< size;i++){
            printf("%d ", array[i]);
          }
          
        }
  
        size = size * 2;
    }
/*
    for(int i = 0; i < n; i++){
      printf("Size:%d        Time table: %f\n", buf[i].size ,buf[i].time);
    }*/
}
