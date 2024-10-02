#include "cipher.h"

/// IN THIS FILE, IMPLEMENT EVERY FUNCTION THAT'S DECLARED IN cipher.h.


enum AsciiFirstLastChar
{
    A_ASCII = 'A',
    Z_ASCII = 'Z',
    A_LOWER_ASCII = 'a',
    Z_LOWER_ASCII = 'z'
};

/**
 * Shifts c by k within the cyclic range [first_char..last_char]
 * @param c character to be shifted
 * @param k shift size
 * @param first_char first character in range
 * @param last_char last character in range
 * @return the shifted character
*/
char shift_char_in_range (char c, int k, char first_char, char last_char)
{
  /** for better memory (but lower understanding) It is possible not to define
   * the range and the step as additional variables and write directly to
   * return, but it is better to leave the code like that
   */
  int range = last_char - first_char + 1;
  int step = (k % range + range) % range;
  char after_c = (c - first_char + step) % range + first_char;
  return after_c;
}

// See full documentation in header file
void encode (char s[], int k)
/**function that encode the s array with Caesar cipher encode, the k is the **/
{
  for (int i = 0; s[i] != '\0'; i++)
  {
    if (s[i] >= A_ASCII && s[i] <= Z_ASCII) //the char is upper case
    {
      s[i] = shift_char_in_range (s[i], k, A_ASCII, Z_ASCII);
    }
    if (s[i] >= A_LOWER_ASCII
        && s[i] <= Z_LOWER_ASCII) // the char is lower case
    {
      s[i] = shift_char_in_range (s[i], k, A_LOWER_ASCII, Z_LOWER_ASCII);
    }
  }
}

// See full documentation in header file
void decode (char s[], int k)
{
  encode (s, -k);
}
