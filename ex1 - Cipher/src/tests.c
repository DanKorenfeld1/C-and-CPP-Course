#include <string.h>
#include "tests.h"

#define K_1 3
#define K_1_N -3
#define K_CYCLIC_P 29
#define K_CYCLIC_N -29
#define K_11 1

// See full documentation in header file
int test_encode_non_cyclic_lower_case_positive_k ()
{
  char in[] = "abc";
  char out[] = "def";
  encode (in, K_1);
  return strcmp (in, out) != 0;
  //check if the string equal, if equal return 0, and 0 != 0 => 0
}

// See full documentation in header file
int test_encode_cyclic_lower_case_special_char_positive_k ()
{
  char in[] = "ab,c";
  char out[] = "de,f";
  encode (in, K_CYCLIC_P);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_non_cyclic_lower_case_special_char_negative_k ()
{
  char in[] = "def";
  char out[] = "abc";
  encode (in, K_1_N);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_cyclic_lower_case_negative_k ()
{
  char in[] = "de,f";
  char out[] = "ab,c";
  encode (in, K_CYCLIC_N);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_cyclic_upper_case_positive_k ()
{
  char in[] = "ZY,ZF";
  char out[] = "AZ,AG";
  encode (in, K_11);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_non_cyclic_lower_case_positive_k ()
{
  char in[] = "def";
  char out[] = "abc";
  decode (in, K_1);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_cyclic_lower_case_special_char_positive_k ()
{
  char in[] = "de,f";
  char out[] = "ab,c";
  decode (in, K_CYCLIC_P);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_non_cyclic_lower_case_special_char_negative_k ()
{
  char in[] = "abc";
  char out[] = "def";
  decode (in, K_1_N);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_cyclic_lower_case_negative_k ()
{
  char in[] = "ab,c";
  char out[] = "de,f";
  decode (in, K_CYCLIC_N);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_cyclic_upper_case_positive_k ()
{
  char in[] = "AZ,AG";
  char out[] = "ZY,ZF";
  decode (in, K_11);
  return strcmp (in, out) != 0;
}
