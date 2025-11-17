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
  printf("size: %d\n", size);
  for(int i = 0; i < size; i++){
    printf("%d ",arr[i]);
  }
}

void print_result(result_t *buf, int n){
  for(int i = 0; i<n;i++){
    printf("Size: %d        %f\n", buf[i].size, buf[i].time);
  }

}

void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n) {
    int size = SIZE_START;
    time_t time_start, time_end;
    //n =1;
    //printf("INPUT HERE:\n");
    //int input = 5;
    int *array = malloc(size * sizeof(int));
    for (int j = 0; j < n; j++) {
          int input = 5;

        if(a == bubble_sort_t){
          double time_used = 0;
          reverse_ordered_array(array, size);

          time_start = clock();
          bubble_sort(array, size);
          time_end = clock();
          time_used = ((double)(time_end - time_start)) / CLOCKS_PER_SEC;
          buf[j].time = time_used;
          buf[j].size = size;

        }
        else if(a == insertion_sort_t){
          double time_used = 0;
          reverse_ordered_array(array, size);
          time_start = clock();
          insertion_sort(array,size);
          time_end = clock();
          time_used = ((double)(time_end - time_start)) / CLOCKS_PER_SEC;
          buf[j].time = time_used;
          buf[j].size = size;
        }

        else if(a == quick_sort_t){
          double time_used = 0;
          reverse_ordered_array(array,size);
          //print_array(array,size);
          
          time_start = clock();

          quick_sort(array,0, size-1); //(array, första index, sista index)

          time_end = clock();
          time_used = ((double)(time_end - time_start)) / CLOCKS_PER_SEC;
          //print_array(array,size);

          
          buf[j].time = time_used;
          buf[j].size = size; 
        }
        
        else if(a == linear_search_t){
        double time_used = 0;

        ordered_array(array, size);
        time_start = clock();

        //bool found = linear_search(array, size, input);
        //printf("found?: %d", found);

        time_end = clock();
        time_used = ((double)(time_end - time_start)) / CLOCKS_PER_SEC;
        buf[j].time = time_used;
        buf[j].size = size;
        } 

        else if(a == binary_search_t){
          ordered_array(array, size);
          double time_used = 0;
          time_start = clock();

          bool found = binary_search(array, size, input); 
          time_end = clock();
          printf("foiund:%d", found);

          time_used = ((double)(time_end - time_start)) / CLOCKS_PER_SEC;

          buf[j].time = time_used;
          buf[j].size = size;
        }

        size = size * 2;
        array = realloc(array, size* sizeof(int));
    }
    
    print_result(buf, n);
    free(array);
}
