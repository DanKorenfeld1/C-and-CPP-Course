#include "sort_bus_lines.h"
#include "test_bus_lines.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>


//options for input from CLI
#define BY_DURATION  "by_duration"
#define BY_DISTANCE "by_distance"
#define BY_NAME "by_name"
#define TEST "test"


//Message or Error options
#define MESSAGE_NUMBER_LINE "Enter number of lines. Then enter\n"
#define THE_NUMBER_OF_LINES_INVALID "ERROR: the number of the line is "\
"invalid, the number must be natural number, enter number, then enter\n"
#define MESSAGE_FOR_ENTER_LINE_INFO "Enter line info. Then enter\n"
#define MESSAGE_ERROR_INVALID_NAME "ERROR: use only a-z and 0-9 char\n"
#define MESSAGE_ERROR_OUT_OF_THE_RANGE_DISTANCE "ERROR: the distance out of "\
"the range [0-1000]\n"
#define MESSAGE_ERROR_OUT_OF_THE_RANGE_DURATION "ERROR: the duration out of "\
"the range [10-100]\n"
#define MESSAGE_ERROR_ARGUMENT_INVALID "ERROR: one of the argument is "\
"invalid enter again\n"
#define MESSAGE_ERROR_WITH_MEMORY_ALLOCATION "ERROR: there is problem with "\
"Memory allocation"
#define MESSAGE_USAGE_ARGUMENT "USAGE: It is important to pay attention to "\
"insert one argument, with an appropriate name"
#define IS_SORTED_BY_DURATION_MESSAGE "the test check if the array sorted by"\
" duration"
#define IS_EQUAL_DURATION_MESSAGE "the test check if the array stay the same \
array remains and all the bus lines remain after sorted by duration"
#define IS_SORTED_BY_DISTANCE_MESSAGE "the test check if the array sorted by"\
" distance"
#define IS_EQUAL_DISTANCE_MESSAGE "the test check if the array stay the same \
array remains and all the bus lines remain after sorted by distance"
#define IS_SORTED_BY_NAME_MESSAGE "the test check if the array sorted by"\
" name"
#define IS_EQUAL_NAME_MESSAGE "the test check if the array stay the same \
array remains and all the bus lines remain after sorted by name"


// numbers
#define MAX_LEN_LINE 61
#define MAX_LEN_NAME 20
#define CLI_INPUT 1
#define BASE 10
/**
 * the range of the boundary for the distance
 */
typedef enum BoundaryDistance
{
    MIN_DISTANCE = 0,
    MAX_DISTANCE = 1000
} BoundaryDistance;

/**
 * the range of the boundary for the duration
 */
typedef enum BoundaryDuration
{
    MIN_DURATION = 10,
    MAX_DURATION = 100
} BoundaryDuration;
/**
 * the numbers of the test
 */
typedef enum Tests
{
    IS_SORTED_DISTANCE = 1,
    IS_EQUAL_DISTANCE,
    IS_SORTED_DURATION,
    IS_EQUAL_DURATION,
    IS_SORTED_NAME,
    IS_EQUAL_NAME
} Tests;

/**
 * function that check if the s[] is number
 * @param s array of char "string"
 * @return 0 (false) 1 (true)
 */
bool is_number (const char s[])
{
    if (s[0] == '\n') // check if the input it not empty
    {
        return false;
    }
    if (s[0] == '0' && s[1] == '\n')
    {
        return false;
    }
    for (int i = 0; *(s + i) != '\0' && *(s + i) != '\n'; i++)
    {
        if (isdigit (*(s + i)) == false || *(s + i) == '.' || *(s + i) == '-')
        {
            return false;
        }
    }
    return true;
}
/**
 * check if the name of the line valid
 * @param name_line the name of the line
 * @return true (1) if valid, false (0) otherwise
 */
bool check_name_line (const char name_line[])
{
    for (int i = 0; name_line[i] != '\0'; i++)
    {
        if (!(name_line[i] <= 'z' && name_line[i] >= 'a'))
        {
            if (!(name_line[i] <= '9' && name_line[i] >= '0'))
            {
                return false;
            }
        }
    }
    return true;
}
/**
 * function that check the input for every BusLine
 * @param name_line the name of the bus
 * @param distance the distance of the bus
 * @param duration the duration of the bus
 * @return true (1) if valid, false (0) otherwise.
 */
bool check_the_input_for_bus_line (const char name_line[], int distance, int
duration)
{
    if (!check_name_line (name_line))
    {
        fprintf (stdout, MESSAGE_ERROR_INVALID_NAME);
        return false;
    }
    if (distance < MIN_DISTANCE || distance > MAX_DISTANCE)
    {
        fprintf (stdout, MESSAGE_ERROR_OUT_OF_THE_RANGE_DISTANCE);
        return false;
    }
    if (duration < MIN_DURATION || duration > MAX_DURATION)
    {
        fprintf (stdout, MESSAGE_ERROR_OUT_OF_THE_RANGE_DURATION);
        return false;
    }
    return true;
}
/**
 * function that return the number of the line from the user
 * @return (int) the number of the bus line
 */
int get_the_number_of_the_line ()
{
    fprintf (stdout, MESSAGE_NUMBER_LINE);
    char *string_input_number_line = malloc (sizeof (char) * MAX_LEN_LINE);
    if (string_input_number_line == NULL)
    {
        fprintf (stdout, MESSAGE_ERROR_WITH_MEMORY_ALLOCATION);
        return EXIT_FAILURE;
    }
    fgets (string_input_number_line, MAX_LEN_LINE, stdin);
    while (!is_number (string_input_number_line))
    {
        fprintf (stdout, THE_NUMBER_OF_LINES_INVALID);
        fgets (string_input_number_line, MAX_LEN_LINE, stdin);
    }
    long int number_of_lines = 0;
    number_of_lines = strtol (string_input_number_line, NULL, BASE);
    free (string_input_number_line);
    string_input_number_line = NULL;
    return (int) number_of_lines;
}

/**
 * function that build the array of the BusLine and check the input
 * @param bus_lines pointer for the array of the BusLine
 * @param number_of_lines the number of the lines
 * @return EXIT_SUCCESS if the test pass, otherwise: EXIT_FAILURE
 */
int build_the_array_of_busline (BusLine *bus_lines, int number_of_lines)
{

    int i = 0;
    while (i < number_of_lines)
    {
        fprintf (stdout, MESSAGE_FOR_ENTER_LINE_INFO);
        char *string_input_bus_line = malloc (sizeof (char) * MAX_LEN_LINE);
        fgets (string_input_bus_line, MAX_LEN_LINE, stdin);
        char name_line[MAX_LEN_NAME] = {0};
        int distance = 0;
        int duration = 0;
        int is_ok = sscanf (string_input_bus_line, "%[^,],%d,%d", name_line,
                            &distance, &duration);
        free (string_input_bus_line);
        string_input_bus_line = NULL;
        if (is_ok == 3)
        {
            if (check_the_input_for_bus_line (name_line, distance, duration))
            {
                BusLine bus_line = {"0", distance, duration};
                memcpy (bus_line.name, name_line,
                        sizeof (char) * MAX_LEN_NAME);
                *(bus_lines + i) = bus_line;
                i++;
            }
        }
        else
        {
            fprintf (stdout, MESSAGE_ERROR_ARGUMENT_INVALID);
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
/**
 * function that free the allocate memory and clear the pointer to NULL
 * return EXIT_FAILURE or EXIT_SUCCESS
 * @param pointer the pointer
 */
int free_memory_allocate_return_exit (BusLine *pointer, int value_to_return)
{
    free (pointer);
    pointer = NULL;
    return value_to_return;
}
/**
 * A function that checks if the correctness of the sorting quick by distance
 * @param start_original pointer for the start of the array (original)
 * @param end_original pointer for the end of the array (original)
 * @param tests_array pointer for the start of the array (copy)
 * @param tests_array_end pointer for the end of the array (copy)
 */
void quick_sort_distance_tests (BusLine *start_original, BusLine
*end_original, BusLine *tests_array, BusLine *tests_array_end)
{
    quick_sort (tests_array, tests_array_end, DISTANCE);
    // quick sort distance
    if (!is_sorted_by_distance (tests_array, tests_array_end))
    {
        fprintf (stdout, "TEST %d FAILED: %s\n", IS_SORTED_DISTANCE,
                 IS_SORTED_BY_DISTANCE_MESSAGE);
    }
    else
    {
        fprintf (stdout, "TEST %d PASSED: %s\n", IS_SORTED_DISTANCE,
                 IS_SORTED_BY_DISTANCE_MESSAGE);
    }
    if (!is_equal (tests_array, tests_array_end, start_original, end_original))
    {
        fprintf (stdout, "TEST %d FAILED: %s\n", IS_EQUAL_DISTANCE,
                 IS_EQUAL_DISTANCE_MESSAGE);
    }
    else
    {
        fprintf (stdout, "TEST %d PASSED: %s\n", IS_EQUAL_DISTANCE,
                 IS_EQUAL_DISTANCE_MESSAGE);
    }
}
/**
 * A function that checks if the correctness of the sorting quick by duration
 * @param start_original pointer for the start of the array (original)
 * @param end_original pointer for the end of the array (original)
 * @param tests_array pointer for the start of the array (copy)
 * @param tests_array_end pointer for the end of the array (copy)
 */
void quick_sort_duration_tests (BusLine *start_original, BusLine
*end_original, BusLine *tests_array, BusLine *tests_array_end)
{
    quick_sort (tests_array, tests_array_end, DURATION);
    if (!is_sorted_by_duration (tests_array, tests_array_end))
    {
        fprintf (stdout, "TEST %d FAILED: %s\n", IS_SORTED_DURATION,
                 IS_SORTED_BY_DURATION_MESSAGE);
    }
    else
    {
        fprintf (stdout, "TEST %d PASSED: %s\n", IS_SORTED_DURATION,
                 IS_SORTED_BY_DURATION_MESSAGE);
    }
    if (!is_equal (tests_array, tests_array_end, start_original, end_original))
    {
        fprintf (stdout, "TEST %d FAILED: %s\n", IS_EQUAL_DURATION,
                 IS_EQUAL_DURATION_MESSAGE);
    }
    else
    {
        fprintf (stdout, "TEST %d PASSED: %s\n", IS_EQUAL_DURATION,
                 IS_EQUAL_DURATION_MESSAGE);
    }
}
/**
 * A function that checks if the correctness of the sorting bubbles by name
 * @param start_original pointer for the start of the array (original)
 * @param end_original pointer for the end of the array (original)
 * @param tests_array pointer for the start of the array (copy)
 * @param tests_array_end pointer for the end of the array (copy)
 */
void bubble_sort_name_tests (BusLine *start_original, BusLine
*end_original, BusLine *tests_array, BusLine *tests_array_end)
{
    bubble_sort (tests_array, tests_array_end);
    if (!is_sorted_by_name (tests_array, tests_array_end))
    {
        fprintf (stdout, "TEST %d FAILED: %s\n", IS_SORTED_NAME,
                 IS_SORTED_BY_NAME_MESSAGE);
    }
    else
    {
        fprintf (stdout, "TEST %d PASSED: %s\n", IS_SORTED_NAME,
                 IS_SORTED_BY_NAME_MESSAGE);
    }
    if (!is_equal (tests_array, tests_array_end, start_original, end_original))
    {
        fprintf (stdout, "TEST %d FAILED: %s\n", IS_EQUAL_NAME,
                 IS_EQUAL_NAME_MESSAGE);
    }
    else
    {
        fprintf (stdout, "TEST %d PASSED: %s\n", IS_EQUAL_NAME,
                 IS_EQUAL_NAME_MESSAGE);
    }
}

/**
 * function that check if the tests pass or not
 * @param start the start of the array (pointer).
 * @param end the end of the array (pointer).
 * @return EXIT_SUCCESS if the test pass, otherwise: EXIT_FAILURE
 */
int tests_function (BusLine *start, BusLine *end)
{
    BusLine *tests_array = malloc (sizeof (BusLine) * (end - start));
    if (tests_array == NULL)
    {
        fprintf (stdout, MESSAGE_ERROR_WITH_MEMORY_ALLOCATION);
        return free_memory_allocate_return_exit (tests_array,
                                                 EXIT_FAILURE);
    }
    memcpy (tests_array, start, (end - start) * sizeof (BusLine));
    BusLine *tests_array_end = tests_array + (end - start);
    //quick sort distance
    quick_sort_distance_tests (start, end, tests_array, tests_array_end);
    //quick sort duration
    quick_sort_duration_tests (start, end, tests_array, tests_array_end);
    // bubble sort (name)
    bubble_sort_name_tests (start, end, tests_array, tests_array_end);
    return free_memory_allocate_return_exit (tests_array,
                                             EXIT_SUCCESS);
}
/**
 * check if the input from the CLI (the mode of the program) is one of the 4
 * that ok
 * @param input the name
 * @return true (1) of ok, false (0) otherwise
 */
bool is_ok_input_from_cli (const char input[])
{
    if (strcmp (input, BY_DURATION) == 0)
    {
        return true;
    }
    if (strcmp (input, BY_DISTANCE) == 0)
    {
        return true;
    }
    if (strcmp (input, BY_NAME) == 0)
    {
        return true;
    }
    if (strcmp (input, TEST) == 0)
    {
        return true;
    }
    return false;
}

/**
 * Main function for sorting and printing bus lines.
 * This function takes command line arguments and uses them to sort and print
 * bus lines based on their duration, distance, or name.. Finally, the
 * function frees the memory allocated for the array and returns EXIT_SUCCESS.
 * @param argc The number of arguments passed in from the command line.
 * @param argv An array of strings containing the command line arguments.
 * @return EXIT_SUCCESS if the function completes successfully, or
 *         EXIT_FAILURE if there is an error in the input or in memory
 *         allocation.
 */
int main (int argc, char *argv[])
{
    if (argc != 2 || !is_ok_input_from_cli (argv[CLI_INPUT]))
    {
        fprintf (stdout, MESSAGE_USAGE_ARGUMENT);
        return EXIT_FAILURE;
    }
    int number_of_lines = get_the_number_of_the_line ();
    BusLine *bus_lines = malloc (sizeof (BusLine) * number_of_lines);
    if (bus_lines == NULL)
    {
        fprintf (stdout, MESSAGE_ERROR_WITH_MEMORY_ALLOCATION);
        return EXIT_FAILURE;
    }
    int ok = build_the_array_of_busline (bus_lines, number_of_lines);
    BusLine *end = NULL;
    if (!ok)
    {
        end = (bus_lines + number_of_lines);
    }

    if (strcmp (argv[CLI_INPUT], BY_DURATION) == 0)
    {
        quick_sort_with_print (bus_lines, end, DURATION);
    }
    if (strcmp (argv[CLI_INPUT], BY_DISTANCE) == 0)
    {
        quick_sort_with_print (bus_lines, end, DISTANCE);
    }
    if (strcmp (argv[CLI_INPUT], BY_NAME) == 0)
    {
        bubble_sort_with_print (bus_lines, end);
    }
    if (strcmp (argv[CLI_INPUT], TEST) == 0)
    {
        int return_value = tests_function (bus_lines, end);
        return free_memory_allocate_return_exit (bus_lines, return_value);
    }
    return free_memory_allocate_return_exit (bus_lines, EXIT_SUCCESS);
}