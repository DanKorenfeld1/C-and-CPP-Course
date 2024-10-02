#ifndef EX2_REPO_TESTBUSLINES_H
#define EX2_REPO_TESTBUSLINES_H
// write only between #define EX2_REPO_TESTBUSLINES_H and #endif
// EX2_REPO_TESTBUSLINES_H
#include "sort_bus_lines.h"

/**
 * test that check if the array of the bus lines sorted by distance.
 * @param start the start of the array (pointer).
 * @param end the end of the array (pointer).
 * @return 1 for successful, 0 otherwise.
 */
int is_sorted_by_distance (BusLine *start, BusLine *end);

/**
 * test that check if the array of the bus lines sorted by duration.
 * @param start the start of the array (pointer).
 * @param end the end of the array (pointer).
 * @return 1 for successful, 0 otherwise.
 */
int is_sorted_by_duration (BusLine *start, BusLine *end);

/**
* test that check if the array of the bus lines sorted by name.
 * @param start the start of the array (pointer).
 * @param end the end of the array (pointer).
 * @return 1 for successful, 0 otherwise.
 */
int is_sorted_by_name (BusLine *start, BusLine *end);

/**
 * test that check for equal BusLine array
 * @param start_sorted pointer for start array new BusLine array (pointer)
 * @param end_sorted pointer for end array new BusLine array (pointer)
 * @param start_original pointer for start array original BusLine array
 * (pointer)
 * @param end_original pointer for end array original BusLine array
 * (pointer)
 * @return 1 for successful, 0 otherwise.
 */
int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original);
// write only between #define EX2_REPO_TESTBUSLINES_H and #endif
// EX2_REPO_TESTBUSLINES_H
#endif //EX2_REPO_TESTBUSLINES_H
