#ifndef EX2_REPO_SORTBUSLINES_H
#define EX2_REPO_SORTBUSLINES_H
// write only between #define EX2_REPO_SORTBUSLINES_H and #endif

// EX2_REPO_SORTBUSLINES_H
#include <string.h>
#define NAME_LEN 21

/**
 * BusLine struct contains name of the bus line, distance and the duration
 */
typedef struct BusLine
{
    char name[NAME_LEN];
    int distance, duration;
} BusLine;
typedef enum SortType
{
    DISTANCE,
    DURATION
} SortType;

/**
 * function that print the array of the BusLine
 * @param start the start of the array (pointer).
 * @param end the end of the array (pointer).
 */
void print_array_of_bus_line (BusLine *start, BusLine *end);

void print_array_of_bus_line_debage (BusLine *start, BusLine *end);

/**
 * function that swap between 2 cells
 * @param first_cell the start of the array (pointer).
 * @param sec_cell the end of the array (pointer).
 */
void swap (BusLine *first_cell, BusLine *sec_cell);

/**
 * function that sort the array of BusLine objects using Bubble sort algorithm
 * @param start the start of the array (pointer).
 * @param end the end of the array (pointer).
 */
void bubble_sort (BusLine *start, BusLine *end);

/**
 * function that sort the array of BusLine objects using Bubble sort algorithm
 * and print the array
 * @param start the start of the array (pointer).
 * @param end the end of the array (pointer).
 */
void bubble_sort_with_print (BusLine *start, BusLine *end);

/**
 * function that sort the array of BusLine objects using Quick sort algorithm
 * @param start the start of the array (pointer).
 * @param end the end of the array (pointer).
 * @param sort_type distance/duration
 */
void quick_sort (BusLine *start, BusLine *end, SortType sort_type);

/**
 * function helper for quick sort, We will use the pivot, we will divide the
 * array into values that are larger than it and smaller than it, and thus we
 * will sort that each side has values that are larger or smaller than it,
 * respectively
 * @param start the start of the array (pointer).
 * @param end the end of the array (pointer).
 * @param sort_type distance/duration
 * @return the current pivot
 */
BusLine *partition (BusLine *start, BusLine *end, SortType sort_type);
/**
 * function that sort the array of BusLine objects using Quick sort algorithm
 * and print the array
 * @param start the start of the array (pointer).
 * @param end the end of the array (pointer).
 */
void quick_sort_with_print (BusLine *start, BusLine *end, SortType sort_type);

// write only between #define EX2_REPO_SORTBUSLINES_H and #endif
// EX2_REPO_SORTBUSLINES_H

#endif //EX2_REPO_SORTBUSLINES_H
