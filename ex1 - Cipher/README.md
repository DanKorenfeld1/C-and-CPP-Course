
# Cipher Project

This project implements a simple encryption and decryption mechanism based on shifting characters within a given range. It includes functions to encode and decode strings using a shift (or key) provided as input.

## Project Structure

- `cipher.h`: Header file defining the interfaces for encoding and decoding functions.
- `cipher.c`: Implementation of the encoding and decoding algorithms.
- `main.c`: Contains the main function and utilities to test the cipher operations.
- `tests.h`: (Assumed) for testing the encoding and decoding functions (not explicitly found in the files provided).

## Functionality

### Encoding
The `encode(char s[], int k)` function encrypts the input string `s` by shifting each character by `k` positions in the ASCII table, keeping it within a specific range of letters (A-Z, a-z).

### Decoding
The `decode(char s[], int k)` function reverses the encoding process, shifting characters back by `k` positions to retrieve the original message.

### Usage
Compile the project using a C compiler. For example, to compile with GCC:
```bash
gcc -o cipher main.c cipher.c
```

Then, run the executable, providing the appropriate arguments for encryption or decryption.

Example:
```bash
./cipher encode "Hello" 3
```

This will shift each letter in "Hello" by 3 positions.

## Compilation and Execution

Make sure to have a C compiler installed. To compile the project, use the following commands:
```bash
gcc -o cipher main.c cipher.c
```

To run:
```bash
./cipher
```

You can pass different arguments to test encoding and decoding with varying shift values.
