#include "analyze.h"
#include "algorithm.h"
#include <stdlib.h>
#include <stdio.h>

//
// Private
//

//
// Public
//
void populate_array(const algorithm_t a, const case_t c, int *arr, int size) {
  if (a == bubble_sort_t || a == insertion_sort_t) {
    switch (c) {
    case best_t:
    printf("best_t");
      for (int i = 0; i < size; i++) {
        arr[i] = i;
      }
      break;

    case worst_t:
    printf("worst_t");
      for (int i = size-1; i < 0; i--) {
        arr[i] = i;
      }

      break;

    case average_t:
    printf("avg_t");
      for (int i = 0; i < size; i++)
        arr[i] = rand() % size;
      break;
    }
  }
}

void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n) {

    int size = SIZE_START;
    for (int j = 0; j < n; j++) {
        int array[size];
        populate_array(a, c, array, size);
        bubble_sort(array, size);
        size = size * 2;
    }
}
