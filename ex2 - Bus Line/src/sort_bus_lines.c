#include "sort_bus_lines.h"
#include <stdbool.h>
#include <stdio.h>

/**
 * function that print the array of the BusLine
 * @param start the start of the array (pointer).
 * @param end the end of the array (pointer).
 */
void print_array_of_bus_line (BusLine *start, BusLine *end)
{
    for (int i = 0; i < end - start; i++)
    {
        printf ("%s,%d,%d\n", (start + i)->name, (start + i)
            ->distance, (start + i)->duration);
    }
}
void print_array_of_bus_line_debage (BusLine *start, BusLine *end)
{
    for (int i = 0; i < end - start; i++)
    {
        printf ("{name:%s,distance:%d,duration:%d}->", (start + i)->name, (
            start
            + i)
            ->distance, (start + i)->duration);
    }
    printf ("\n");
}

/**
 * function that swap between 2 cells
 * @param first_cell the start of the array (pointer).
 * @param sec_cell the end of the array (pointer).
 */
void swap (BusLine *first_cell, BusLine *sec_cell)
{
    BusLine temp = *first_cell;
    *first_cell = *sec_cell;
    *sec_cell = temp;
}

// See full documentation in header file
void bubble_sort (BusLine *start, BusLine *end)
{
    for (int i = 0; i < end - start; i++)
    {
        bool swapped = false;
        for (int j = 0; j < end - start - i - 1; j++)
        {
            if (strcmp ((start + j)->name, (start + j + 1)->name) > 0)
            {// if the cell with the smaller index bigger than the bigger cell
                swap (start + j, start + j + 1);
                swapped = true;
            }
        }
        if (!swapped) // the array is sorted
        {
            break;
        }
    }
}

// See full documentation in header file
void bubble_sort_with_print (BusLine *start, BusLine *end)
{
    bubble_sort (start, end);
    print_array_of_bus_line (start, end);
}

// See full documentation in header file
BusLine *partition (BusLine *start, BusLine *end, SortType sort_type)
{
    BusLine *start_bus_line = start;
    BusLine *pivot = end - 1;
    int i = -1;
    for (int j = 0; j < end - start - 1; j++)
    {
        if (sort_type == DISTANCE)
        {
            if ((start + j)->distance <= pivot->distance)
            {
                i++;
                swap (start + i, start + j);
            }
        }
        if (sort_type == DURATION)
        {
            if ((start + j)->duration <= pivot->duration)
            {
                i++;
                swap (start + i, start + j);
            }
        }
    }
    swap (start + i + 1, end - 1);
    return start_bus_line + i + 1;
}

// See full documentation in header file
void quick_sort (BusLine *start, BusLine *end, SortType sort_type)
{
    if (end - start > 0)
    {
        BusLine *pivot = partition (start, end, sort_type);
        quick_sort (start, pivot, sort_type);
        quick_sort (pivot + 1, end, sort_type);
    }
}
// See full documentation in header file
void quick_sort_with_print (BusLine *start, BusLine *end, SortType sort_type)
{
    quick_sort (start, end, sort_type);
    print_array_of_bus_line (start, end);
}