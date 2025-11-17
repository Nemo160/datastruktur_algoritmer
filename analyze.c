#include "analyze.h"
#include "algorithm.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


//
// Private
//
void ordered_array(int *arr, int size){
  for (int i = 0; i < size; i++) {
    arr[i] = i;
  }
}
void reverse_ordered_array(int *arr, int size){
  for (int i = size-1; i >= 0; i--) {
    arr[i] = (size-1)- i;
  }
}

void random_array(int *arr, int size){
  for (int i = 0; i < size; i++){
    arr[i] = rand() % size;
  }
}

void print_array(int *arr, int size){
  for(int i = 0; i < size; i++){
    printf("%d ",arr[i]);
  }
  printf("\n\n");
  
}

void check_case(int *array, int size, const case_t c, const algorithm_t a){
  switch(c){
    case best_t:
      ordered_array(array,size);
      break;

    case worst_t:
      reverse_ordered_array(array,size);
      break;

    case average_t:
      random_array(array,size);
      break;
  }
}

void run_algorithm(int *array, int size, const case_t c, const algorithm_t a, int input){
  switch(a){
    case bubble_sort_t:
      bubble_sort(array,size);
      break;

    case insertion_sort_t:
      insertion_sort(array,size);
      break;

    case quick_sort_t:
      quick_sort(array,0,size-1);
      break;

    case linear_search_t:
      linear_search(array,size,input);
      break;

    case binary_search_t:
      //print_array(array,size);
      quick_sort(array,0,size-1);
     // print_array(array,size);

      binary_search(array,size,input);
      break;
  }
}

//
// Public
//

void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n) {
  int size = SIZE_START;
  int input = 0;
  int *array = malloc(size * sizeof(int));
  if(a == linear_search_t || a == binary_search_t){
    printf("INPUT\n");
          scanf("%d", &input);
          getchar();
  }
  //n=1;
  //time_t time_start,time_end;
  clock_t start, end;
  for (int j = 0; j < n; j++) {
    check_case(array, size, c, a);
    start = clock();
    run_algorithm(array, size, c, a,input);
    end = clock();
    double time_used = ((double)end - start) / CLOCKS_PER_SEC;
    
    buf[j].time = time_used;
    buf[j].size = size;

    size *= 2;
    array = realloc(array, size * sizeof(int));
  }
  free(array);
}
