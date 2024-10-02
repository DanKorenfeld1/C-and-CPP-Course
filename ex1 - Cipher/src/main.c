#include "cipher.h"
#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// your code goes here

#define MAX_LINE 1030
#define FIVE_ARGUMENT 5
#define TWO_ARGUMENT 2
#define DECIMAL_BASE 10
#define COMMAND 1
#define STEPS 2
#define INPUT_ADD 3
#define OUTPUT_ADD 4

/**
 * function that check if the s[] is number
 * @param s array of char "string"
 * @return 0 (false) 1 (true)
 */
int is_number (const char s[])
{
    // and so on
    if (s[0] == '-' && s[1] == '\0')
    {
        return 0;
    }
    for (int i = 1; s[i] != '\0'; i++)
    {
        if (isdigit (s[i]) == 0)
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
 * function that check all the test about Input/Output
 * @param argc the number of the argv
 * @param argv the arg that the program get from the CLI
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int all_test_io (int argc, char *argv[])
{
    if (argc != FIVE_ARGUMENT && argc != TWO_ARGUMENT)
    {
        return fail_function ("The program receives 1 or"
                              " 4 arguments only.\n");
    }
    if (argc == TWO_ARGUMENT)
    {
        if (strcmp (argv[1], "test") == 0)
        {
            return EXIT_SUCCESS;
        }
        else
        {
            return fail_function ("Usage: cipher test\n");
        }
    }
    else if ((strcmp (argv[COMMAND], "encode") != 0 && (strcmp (argv[COMMAND],
                                                                "decode")
                                                        != 0)))
    {
        return fail_function ("The given command is invalid.\n");
    }
    else if (!is_number (argv[STEPS]))
    {
        return fail_function ("The given shift value is invalid.\n");
    }
    long k = strtol (argv[STEPS], NULL, DECIMAL_BASE);
    if ((int) k - k != 0)
    {
        return fail_function ("The given shift value is invalid.\n");
    }
    FILE *in_file = fopen (argv[INPUT_ADD], "r");
    if (in_file == NULL)
    {
        fail_function ("The given file is invalid.\n");
        return EXIT_FAILURE;
    }
    else
    {
        fclose (in_file);
    }
    FILE *out_file = fopen (argv[OUTPUT_ADD], "w");
    if (out_file == NULL)
    {
        fail_function ("The given file is invalid.\n");
        return EXIT_FAILURE;
    }
    else
    {
        fclose (out_file);
    }
    return EXIT_SUCCESS;
}
/**
 * function that include all the test from the test.c file
 * @param argc the number of the argv
 * @param argv the arg that the program get from the CLI
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int tests_functions ()
{
    if (test_encode_non_cyclic_lower_case_positive_k ())
    {
        return EXIT_FAILURE;
    }
    if (test_encode_cyclic_lower_case_special_char_positive_k ())
    {
        return EXIT_FAILURE;
    }
    if (test_encode_cyclic_lower_case_special_char_positive_k ())
    {
        return EXIT_FAILURE;
    }
    if (test_encode_non_cyclic_lower_case_special_char_negative_k ())
    {
        return EXIT_FAILURE;
    }
    if (test_encode_cyclic_lower_case_negative_k ())
    {
        return EXIT_FAILURE;
    }
    if (test_encode_cyclic_upper_case_positive_k ())
    {
        return EXIT_FAILURE;
    }
    if (test_decode_non_cyclic_lower_case_positive_k ())
    {
        return EXIT_FAILURE;
    }
    if (test_decode_cyclic_lower_case_special_char_positive_k ())
    {
        return EXIT_FAILURE;
    }
    if (test_decode_non_cyclic_lower_case_special_char_negative_k ())
    {
        return EXIT_FAILURE;
    }
    if (test_decode_cyclic_lower_case_negative_k ())
    {
        return EXIT_FAILURE;
    }
    if (test_decode_cyclic_upper_case_positive_k ())
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int main (int argc, char *argv[])
{
    if (all_test_io (argc, argv))
    {
        return EXIT_FAILURE;
    }
    if (strcmp (argv[COMMAND], "test") == 0)
    {
        return tests_functions ();
    }
    if (argc == FIVE_ARGUMENT)
    {
        FILE *in_file = fopen (argv[INPUT_ADD], "r");
        FILE *out_file = fopen (argv[OUTPUT_ADD], "w");
        if (in_file == NULL)
        {
            fail_function ("The given file is invalid.\n");
            if (out_file != NULL)
            {
                fclose (out_file);
            }
            return EXIT_FAILURE;
        }

        if (out_file == NULL)
        {
            if (in_file != NULL)
            {
                fclose (in_file);
            }
            return EXIT_FAILURE;
        }
        long k = strtol (argv[STEPS], NULL, DECIMAL_BASE);
        char content[MAX_LINE] = {0};
        while (fgets (content, MAX_LINE, in_file))
        {
            if (strcmp (argv[COMMAND], "encode") == 0)
            {
                encode (content, (int) k);
            }
            else if (strcmp (argv[COMMAND], "decode") == 0)
            {
                decode (content, (int) k);
            }
            fputs (content, out_file);
        }
        fclose (in_file);
        fclose (out_file);
    }

    return EXIT_SUCCESS;
}
