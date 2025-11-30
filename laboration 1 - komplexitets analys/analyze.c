#define _POSIX_C_SOURCE 200809L 
#include "analyze.h"
#include "algorithm.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
//PS


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
    if(a == binary_search_t){
        ordered_array(array,size);
        return;
    }
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
int set_search_target(int *array, int size, const case_t c, const algorithm_t a){
    //linear
    if(a == linear_search_t){
        switch(c){
            case best_t:
                return array[0]; //first
            
            case worst_t:
                return array[size-1]; //last
            
            case average_t:
                return array[(size-1)/2]; //middle
        }
    }
    //binary
    if(a == binary_search_t){
        switch(c){
            case best_t:
                return array[(size-1)/2]; //middle
            case worst_t:
                return array[0]; //first
            case average_t:
                return array[size/4]; //mellan två halvor
        }
    }
    return 0;
}

void run_algorithm(int *array, int size, const algorithm_t a, int input){
  switch(a){
    case bubble_sort_t:
      bubble_sort(array,size);
      break;

    case insertion_sort_t:
      insertion_sort(array,size);
      break;

    case quick_sort_t:
      quick_sort(array,size);
      break;

    case linear_search_t:
      linear_search(array,size,input);
      break;

    case binary_search_t:
      binary_search(array,size,input);
      break;
  }
}
void set_result(result_t *buf, struct timespec start, struct timespec stop, int index, int size){
    long int startT, stopT, diff;
    
    startT = start.tv_sec * 1E9 + start.tv_nsec; //
    stopT = stop.tv_sec * 1E9 + stop.tv_nsec; //
    
    diff = stopT - startT;
    buf[index].time = diff;
    buf[index].size = size;
}


//
// Public
//

void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n) {
  int size = SIZE_START;
  int input = 0;
  int *array = malloc(size * sizeof(int));
  struct timespec time_start, time_stop;
  for (int j = 0; j < n; j++) {      
    check_case(array, size, c, a);
    if(a == linear_search_t || a == binary_search_t){
        input = set_search_target(array,size,c,a);

    }
    clock_gettime(CLOCK_MONOTONIC, &time_start);
    run_algorithm(array, size, a, input);
    clock_gettime(CLOCK_MONOTONIC, &time_stop);
      
    set_result(buf, time_start, time_stop, j, size);

    size *= 2;
    array = realloc(array, size * sizeof(int));
  }
  free(array);
}
