
# Bus Line Sorting Project

This project implements sorting functionality for bus lines based on distance or duration. It allows users to input a set of bus lines and sort them according to the selected criteria. Additionally, the project includes tests to verify the correctness of the sorting functions.

## Project Structure

- `sort_bus_lines.h`: Header file defining the `BusLine` structure and the sorting functions.
- `sort_bus_lines.c`: Implementation of the bus line sorting functions.
- `test_bus_lines.h`: Header file defining test functions to check if the array is sorted correctly.
- `test_bus_lines.c`: Implementation of the test functions.
- `main.c`: The main file that handles user input and executes the sorting and testing logic.

## Functionality

### Sorting
- The program can sort bus lines based on:
  - **Distance**: Sorts bus lines in ascending order of distance.
  - **Duration**: Sorts bus lines in ascending order of travel time.

### Tests
- **is_sorted_by_distance**: Verifies if the bus lines are sorted by distance.
- **is_sorted_by_duration**: Verifies if the bus lines are sorted by duration.

## Usage

To compile the project using GCC:
```bash
gcc -o sort_lines main.c sort_bus_lines.c test_bus_lines.c
```

Then, run the program, providing input to sort the bus lines.

Example:
```bash
./sort_lines
```

You will be prompted to enter the number of bus lines and the sorting criteria (either by distance or by duration).

## Compilation and Execution

Make sure to have a C compiler installed. To compile and run:
```bash
gcc -o sort_lines main.c sort_bus_lines.c test_bus_lines.c
./sort_lines
```
