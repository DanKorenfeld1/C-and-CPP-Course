#include "test_bus_lines.h"
#include <stdbool.h>
#include <stdio.h>





// See full documentation in header file
int is_sorted_by_distance (BusLine *start, BusLine *end)
{
  for (int i = 1; i < end - start; i++)
  {
    if ((start + i - 1)->distance > (start + i)->distance)
    { // if the array is not increase
      return false;
    }
  }
  return true;
}

// See full documentation in header file
int is_sorted_by_duration (BusLine *start, BusLine *end)
{
  for (int i = 1; i < end - start; i++)
  {
    if ((start + i - 1)->duration > (start + i)->duration)
    { // if the array is not increase
      return false;
    }
  }
  return true;
}

// See full documentation in header file
int is_sorted_by_name (BusLine *start, BusLine *end)
{
  for (int i = 1; i < end - start; i++)
  {
    if (strcmp ((start + i - 1)->name, (start + i)->name) > 0)
    { // if the array is not increase by name (the char of [lower] bigger
      // than the char of [higher]
      return false;
    }
  }
  return true;
}
// See full documentation in header file
int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original)
{
  if ((end_sorted - start_sorted) != (end_original - start_original))
  {
    printf ("the size isn't ok\n");
    return false;
  }
  for (int i = 0; i < end_sorted - start_sorted; i++)
  {
    char founded = false;
    for (int j = 0; j < end_original - start_original; j++)
    {
      if (strcmp (start_sorted[i].name, start_original[j].name) == 0)
      {
        founded = true;
        break;
      }
    }
    if (!founded)
    {
      return false;
    }
  }
  return true;
}


