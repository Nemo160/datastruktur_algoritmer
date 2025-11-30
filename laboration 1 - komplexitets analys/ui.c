#include "ui.h"
#include "io.h"
#include "analyze.h"
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

//
// Private
//
static void ui_invalid_input()
{
	printf("info> bad input\n");
}

static void ui_exit()
{
	printf("info> bye\n");
}

static char ui_get_choice()
{
	char buf[3];

	printf("input> ");
	return read_line(buf, 3) ? buf[0] : 0;
}

static void ui_line(char c, int n)
{
	while (n-- > 0) {
		putchar(c);
	}
	putchar('\n');
}

static void ui_menu_options(const char *options[], int num_options)
{
	int i;

	for (i=0; i<num_options; i++) {
		printf("    %c) %s\n", 'a'+i, options[i]);
	}
}

static void ui_menu()
{
	const char *options[] = {
		"Menu",
		"Exit\n",
		"Bubble sort best case",
		"Bubble sort worst case",
		"Bubble sort average case\n",

		"Insertion sort best case",
		"Insertion sort worst case",
		"Insertion sort average case\n",

		"Quick sort best case",
		"Quick sort worst case",
		"Quick sort average case\n",

		"Linear search best case",
		"Linear search worst case",
		"Linear search average case\n",
		
		"Binary search best case",
		"Binary search worst case",
		"Binary search average case\n",
		
	};

	ui_line('=', MENU_WIDTH);
	ui_menu_options(options, sizeof(options) / sizeof(char *));
	ui_line('-', MENU_WIDTH);
}

char* get_algorithm_str(algorithm_t a){    
    switch (a){
        case bubble_sort_t:  return "bubble sort: ";
        case insertion_sort_t: return "insertion sort: "; 
        case quick_sort_t:  return "quick sort: "; 
        case linear_search_t:  return "linear search: "; 
        case binary_search_t:  return"binary search: "; 
    }
    return "";
}

char *get_case_str(case_t c){
        switch(c){
        case best_t: return "best"; 
        case worst_t: return "worst"; 
        case average_t: return "average"; 
    }
    return "";
}

void print_result(result_t *buf, int n, algorithm_t a, case_t c){
    char *algo_str = get_algorithm_str(a);
    char *case_str = get_case_str(c);
    ui_line('*',RESULT_WIDTH);
	printf("%40s%s\n", algo_str,case_str);
	ui_line('-',RESULT_WIDTH);
    printf("%s %15s %8s %12s %23s %10s\n", "size", "Time T(s)", "T/log n", "T/n", "T/(n log n)","T/n^2");
    ui_line('-',RESULT_WIDTH);

	for(int i = 0; i<n;i++){
        int size = buf[i].size;
        double time = buf[i].time / 1E9;
        double logn = log2(size);
        double T_logn = time / logn; // t/log n
        double T_n = time / size; // t/size
        double T_nlog= time / (size * logn); // t/size * log n -> t/n * log n
        double T_n2 = time/(pow(size,2));
		printf("%6d %12lf %15e %15e %15e %15e\n", size,time,T_logn,T_n,T_nlog, T_n2);
	}
	ui_line('-',RESULT_WIDTH);
}

//
// Public
//

void ui_run()
{
	bool running, show_menu;
	result_t result[RESULT_ROWS];
	
	show_menu = true;
	running = true;
	while (running) {
		if (show_menu) {
			show_menu = false;
			ui_menu();
		}
		switch (ui_get_choice()) {
			// House keeping
			case 'a':
				show_menu = true;
				break;
			case 'b':
				running = false;
				break;
			// Bubble sort
			case 'c':
				benchmark(bubble_sort_t, best_t, result, RESULT_ROWS);
				print_result(result,RESULT_ROWS,bubble_sort_t,best_t);
				break;			

			case 'd':
				benchmark(bubble_sort_t, worst_t, result, RESULT_ROWS);
				print_result(result,RESULT_ROWS,bubble_sort_t,worst_t);
				break;

			case 'e':
				benchmark(bubble_sort_t, average_t, result, RESULT_ROWS);
				print_result(result,RESULT_ROWS,bubble_sort_t,average_t);
				break;

			//Insertion
			case 'f':
				benchmark(insertion_sort_t, best_t, result, RESULT_ROWS);
				print_result(result,RESULT_ROWS,insertion_sort_t,best_t);
				break;

			case 'g':
				benchmark(insertion_sort_t, worst_t, result, RESULT_ROWS);
				print_result(result,RESULT_ROWS,insertion_sort_t,worst_t);
				break;

			case 'h':
				benchmark(insertion_sort_t, average_t, result, RESULT_ROWS);
				print_result(result,RESULT_ROWS,insertion_sort_t,average_t);
				break;

			//Quick sort
			case 'i':
				benchmark(quick_sort_t, best_t, result, RESULT_ROWS);
				print_result(result,RESULT_ROWS,quick_sort_t,best_t);
				break;

			case 'j':
				benchmark(quick_sort_t, worst_t, result, RESULT_ROWS);
				print_result(result,RESULT_ROWS,quick_sort_t,worst_t);
                break;
			
			case 'k':
				benchmark(quick_sort_t, average_t, result, RESULT_ROWS);
				print_result(result,RESULT_ROWS,quick_sort_t,average_t);
				break;

			//Linear  Search
			case 'l':
				benchmark(linear_search_t, best_t, result, RESULT_ROWS);
				print_result(result,RESULT_ROWS,linear_search_t,best_t);
				break;

			case 'm':
				benchmark(linear_search_t, worst_t, result, RESULT_ROWS);
				print_result(result,RESULT_ROWS,linear_search_t,worst_t);
				break;

			case 'n':
				benchmark(linear_search_t, average_t, result, RESULT_ROWS);
				print_result(result,RESULT_ROWS,linear_search_t,average_t);
				break;

			//Binary search
			case 'o':
				benchmark(binary_search_t, best_t, result, RESULT_ROWS);
				print_result(result,RESULT_ROWS,binary_search_t,best_t);
				break;

			case 'p':
				benchmark(binary_search_t, worst_t, result, RESULT_ROWS);
				print_result(result,RESULT_ROWS,binary_search_t,worst_t);
				break;

			case 'q':
				benchmark(binary_search_t, average_t, result, RESULT_ROWS);
				print_result(result,RESULT_ROWS,binary_search_t,average_t);
				break;

			default:
				show_menu = false;
				ui_invalid_input();
				break;
		}
	}
	ui_exit();
}
