//
// general important function to save
//
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>


#define SAFE_MALLOC(var, size, fail_val) var = malloc(size); if (!(var)) return fail_val;

//! same as realloc(), but free old_p if fails
void* safe_realloc (void* old_p, size_t new_size)
{
  void *new_p = realloc (old_p, new_size);
  if (!new_p)
  {
    free (old_p);
    return NULL;
  }
  return new_p;
}

char *strdup (const char *str) // <string.h>
{
  char *dup = malloc (strlen (str) + 1); // +1 for '\0'
  if (!dup)
  {
    return NULL;
  }
  strcpy (dup, str); // Copy the characters
  return dup; // Return the new string
}



void *memcpy (void *destination,		  const void *source,
    size_t n)
{
  char *d = destination; // implicit cast
  const char *s = source;
  const char *s_end = s + n; // ok for char*, not for void*
  while (s < s_end)
  {
    *d++ = *s++; // ok for char*, not for void*
  }
  return destination;
}


//! return true if successful
bool gswap (void *pa, void *pb, size_t num)
{
  void *tmp = malloc (num);
  if (!tmp)
  {
    return false;
  }
  memcpy (tmp, pa, num);
  memcpy (pa, pb, num);
  memcpy (pb, tmp, num);
  free (tmp); // don’t forget!
  return true;
}

//! return true if successful (always does!)
bool gswap_without_malloc (void *pa, void *pb, size_t num)
{
  char *pa_char = pa; // implicit cast
  char *pb_char = pb;
  char *end_a = pa_char + num;
  while (pa_char != end_a)
  {
    char tmp_char = *pa_char;
    *pa_char++ = *pb_char;
    *pb_char++ = tmp_char;
  }
  return true;
}

/**
 * function that check if the s[] is number
 * @param s array of char "string"
 * @return 0 (false) 1 (true)
 */
int is_number (const char s[])
{ //todo change the option that have "-" without number, check with +\-\*
  // and so on
  if (s[0] == '-' && s[1] == '\0')
  {
    return 0;
  }
  for (int i = 1; s[i] != '\0'; i++)
  {
    if (isdigit(s[i]) == 0)
    {
      return 0;
    }
  }
  return 1;
}

/**
 * general function for the tests that fail, to print the message
 * @param message the message that the program need to print
 * @return int (EXIT_FAILURE)
 */
int fail_function (char message[])
{
  fprintf (stderr, message);
  return EXIT_FAILURE;
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

bool check_if_the_file_valid (char *argv[])
{
  FILE *in_file = fopen (argv[PATH_ARG], READ);
  if (in_file == NULL)
  {
    return false;
  }
  fclose (in_file);
  return true;
}


/**
 * Get random number between 0 and max_number [0,max_number).
 * @param max_number maximal number to return (not including).
 * @return Random number
 */
int get_random_number (int max_number)
{
  return rand () % max_number;
}

// assert(x>=0); // aborts if x<0
// #define NDEBUG // all asserts will be disabled! in assert


//open file:
//FILE *in_file = fopen (argv[INPUT_ADD], "r");
//FILE *out_file = fopen (argv[OUTPUT_ADD], "w");


//close file
//fclose(file);

//fgets (read line from file)
// example: char content[MAX_LINE] = {0};
// example: fgets (content, MAX_LINE, in_file)

//strtol (convert string to long)
// example: long k = strtol (argv[STEPS], NULL, DECIMAL_BASE);

//fputs: fputs (content, out_file);

//strcmp (compare 2 string) == 0 if equal
// example: strcmp (argv[COMMAND], "decode") == 0)


//strtok:
//example: ptr_data = strtok (content, " \n \t \r");
//ptr_data = strtok (NULL, " \n \t \r");


// using ?:
// (conditional expression) ? (expression 1) : (expression 2);
// if the considional write, do expression 1, else do expression 2.

