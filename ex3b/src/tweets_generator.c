
#include "markov_chain.h"
//#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum ArgumentsFromCli
{
    NUMBER_OF_SEED_ARG = 1,
    NUMBER_OF_TWEETS_ARG,
    PATH_ARG,
    NUMBER_OF_WORD_TO_READ_ARG
} ArgumentsFromCli;

typedef enum ArgumentsBoundary
{
    LOWER_NUMBER_ARG = 4,
    UPPER_NUMBER_ARG
} ArgumentsBoundary;

#define READ "r"
#define ERROR_FILE_INVALID "ERROR: the file isn't open"
#define ERROR_NUMBER_ARGUMENT "Usage: the number of the argument should "\
"be 3 or 4"


#define MAXIMUM_CHAR_IN_SENTENCE 1001
#define MAX_LENGTH_TWEETS 20
//#define MAXIMUM_CHAR_IN_WORD 101

#define DECIMAL_BASE 10
#define WITHOUT_NUMBER_OF_WORDS (-1)
#define INITIAL_CHAR 0
#define EMPTY 0

#define FORMAT_START_TWEET "Tweet %d: "





/**
 * free the data from char typer
 * @param data the data to free
 */
static void free_data (void *data)
{
  free(data);
  data=NULL;
}

/**
 * function that implement like strdup in string lib
 * @param str the string to duplicate
 * @return ptr void*
 */
static void *copy_str (void *data)
{
  char *str = (char*) data;
  char *dup = calloc (1, strlen (str) + 1);
  if (!dup)
  {
    return NULL;
  }
  strcpy (dup, str);
  return dup;
}
/**
 * check if the data is the last of the sentence or the sequence
 * @param data the data to check
 * @return true if is the lase, else: false
 */
static bool is_last_str(void *data)
{
  char *word = (char*) data;
  for (int i = 0; word[i] != '\0'; i++)
  {
    if (word[i + 1] == '\0' && word[i] == '.')
    {
      return true;
    }
  }
  return false;
}

/**
 * function that print the data the get
 * @param data the data to print
 */
static void print_func_str (void *data)
{
  char *char_data = (char *) data;
  printf ("%s", char_data);
  if(!is_last_str(data))
  {
    printf (" ");
  }
}

/**
 * general function for the tests that fail, to print the message
 * @param message the message that the program need to print
 * @return int (EXIT_FAILURE)
 */
static int fail_function (char *message)
{
  fprintf (stdout, "%s", message);
  return false;
}

/**
 * function that check if the file valid
 * @param argc the number of the argument from the cli
 * @param argv the argument from the cli
 * @return if valid return true, otherwise: false
 */
static bool check_if_the_file_valid (char *argv[])
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
 * check if the number of the argc vaild
 * @param argc the number of the arguments
 * @return true if valid, else: false
 */
static bool check_number_of_arg (int argc)
{
  return (argc == LOWER_NUMBER_ARG) || (argc == UPPER_NUMBER_ARG);
}

/**
 * function that check all the test about Input/Output
 * @param argc the number of the argv
 * @param argv the arg that the program get from the CLI
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
static int all_test_io (int argc, char *argv[])
{
  if (!check_number_of_arg (argc))
  {
    return fail_function (ERROR_NUMBER_ARGUMENT);
  }
  if (argc == UPPER_NUMBER_ARG && !check_if_the_file_valid (argv))
  {
    return fail_function (ERROR_FILE_INVALID);
  }
  return true;
}

/**
 * function helper for fill_database, fill the database for each line
 * @param s the line of the words
 * @param markov_node pointer to markovchain
 * @return 0 if success, otherwise: 1
 */
static int from_line_fill_database (char *content,
                                    int *pointer_number_of_word_readed,
                                    int word_to_read,
                                    MarkovChain *markov_chain)
{
  char *ptr_data = "";
  ptr_data = strtok (content, " \n \t \r");

  MarkovNode *prev_markov_node = NULL;
  while (ptr_data != NULL && (*pointer_number_of_word_readed < word_to_read
                              || word_to_read == WITHOUT_NUMBER_OF_WORDS))
  {
    (*pointer_number_of_word_readed)++;
    Node *ptr_markov_chain = add_to_database (markov_chain, ptr_data);

    if (ptr_markov_chain == NULL)
    {
      return EXIT_FAILURE;
    }
    if (prev_markov_node == NULL)
    {
      prev_markov_node = ptr_markov_chain->data;
    }
    else
    {
      int ans = add_node_to_frequencies_list (prev_markov_node,
                                              ptr_markov_chain->data,
                                              markov_chain);

      if (!ans)
      {
        return EXIT_FAILURE;
      }
      prev_markov_node = ptr_markov_chain->data;
    }
    ptr_data = strtok (NULL, " \n \t \r");
  }
  return EXIT_SUCCESS;
}

/**
 * function that fill the database of the markov chain
 * @param fp the address for the read file
 * @param word_to_read the number of the word to read
 * @param markov_chain pointer to markov chain to fill
 * @return 0 if success, otherwise: 1
 */
static int fill_database (FILE *fp, int word_to_read,
                          MarkovChain *markov_chain)
{
  int number_of_word_readed = EMPTY;
  int *pointer_number_of_word_readed = &number_of_word_readed;
  char content[MAXIMUM_CHAR_IN_SENTENCE] = {INITIAL_CHAR};
  while (fgets (content, MAXIMUM_CHAR_IN_SENTENCE, fp) != NULL
         && ((word_to_read
              > number_of_word_readed)
             || (word_to_read == WITHOUT_NUMBER_OF_WORDS)))
  {
    int ans = from_line_fill_database (content, pointer_number_of_word_readed,
                                       word_to_read, markov_chain);

    if (ans == EXIT_FAILURE)
    {
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

/**
 * function that free the allocation of the database, and close the file
 * @param ptr_chain ptr to markov chain
 * @param fp the ptr to the file
 * @param to_return the number that need to return
 * @return EXIT_SUCCESS if all the running was valid, EXIT_FAILURE otherwise
 */
static int free_db_and_close_file (MarkovChain *ptr_markov_chain, FILE *fp, int
to_return)
{
  free_database (&ptr_markov_chain);
  fclose (fp);
  return to_return;
}


/**
 * allocation the linklist memory
 * @return linklist pointer if was ok, else NULL
 */
static LinkedList *allocate_link_list ()
{
  LinkedList *link_list = calloc (1, sizeof (LinkedList));
  if (link_list == NULL)
  {
    return NULL;
  }
  link_list->first = NULL;
  link_list->last = NULL;
  link_list->size = 0;
  return link_list;
}


/**
 * allocation the markovchain memory
 * @return MarkovChain pointer if was ok, else NULL
 */
static MarkovChain *allocate_markov_chain ()
{
  MarkovChain *markov_chain_ptr = calloc (1, sizeof (MarkovChain));
  if (markov_chain_ptr == NULL)
  {
    fail_function (ALLOCATION_ERROR_MASSAGE);
    return NULL;
  }
  LinkedList *link_list = allocate_link_list ();
  if (link_list == NULL)
  {
    if(markov_chain_ptr !=NULL)
    {
      free(markov_chain_ptr);
    }
    return NULL;
  }
  markov_chain_ptr->database = link_list;
  markov_chain_ptr->print_func = print_func_str;
  markov_chain_ptr->comp_func = (comp_func_type) strcmp;
  markov_chain_ptr->free_data = free_data;
  markov_chain_ptr->copy_func = (copy_func_type) copy_str;
  markov_chain_ptr->is_last = is_last_str;
  return markov_chain_ptr;
}


/**
 * function that check if there are number of words to read or not, and fill
 * the database
 * @param argc the number of the arguments
 * @param argv the arguments
 * @param markov_chain_ptr pointer to the markovchain
 * @param file pointer to the file
 * @return 0 if success, otherwise 1
 */
static int fill_db_return_if_fail_or_not (int argc, char *argv[],
                                          MarkovChain *markov_chain_ptr,
                                          FILE *file)
{
  int ans = EXIT_FAILURE;
  if (argc == UPPER_NUMBER_ARG)
  {
    int number_of_word_to_read_arg = (int) strtol
        (argv[NUMBER_OF_WORD_TO_READ_ARG], NULL, DECIMAL_BASE);
    ans = fill_database (file, number_of_word_to_read_arg,
                         markov_chain_ptr);
  }
  else
  {
    ans = fill_database (file, WITHOUT_NUMBER_OF_WORDS,
                         markov_chain_ptr);
  }
  return ans;
}

/**
 * main function
 * @param argc the number of the arguments
 * @param argv the arguments
 * @return 0 if success, otherwise 1
 */
int main (int argc, char *argv[])
{
  int ret = all_test_io (argc, argv);
  if (!ret)
  {
    return EXIT_FAILURE;
  }
  MarkovChain *markov_chain_ptr = allocate_markov_chain ();
  if (markov_chain_ptr == NULL)
  {
    return EXIT_FAILURE;
  }
  FILE *file = fopen (argv[PATH_ARG], READ);
  if (!file)
  {
    return fail_function (ERROR_FILE_INVALID);
  }
  int ans = fill_db_return_if_fail_or_not (argc, argv, markov_chain_ptr, file);
  if (ans == EXIT_FAILURE)
  {
    fprintf (stdout, ALLOCATION_ERROR_MASSAGE);
    return free_db_and_close_file (markov_chain_ptr, file,
                                   EXIT_FAILURE);
  }
  int seed = (int) strtol (argv[NUMBER_OF_SEED_ARG], NULL,
                           DECIMAL_BASE);
  srand (seed);
  int number_of_tweet = (int) strtol (argv[NUMBER_OF_TWEETS_ARG],
                                      NULL, DECIMAL_BASE);
  for (int i = 1; i <= number_of_tweet; i++)
  {
    MarkovNode *first = get_first_random_node (markov_chain_ptr);
    if (first == NULL)
    {
      break;
    }
    printf (FORMAT_START_TWEET, i);
    int max_len = (MAX_LENGTH_TWEETS < markov_chain_ptr->database->size) ?
                  MAX_LENGTH_TWEETS : markov_chain_ptr->database->size;
    generate_tweet(markov_chain_ptr, first, max_len);
    printf("\n");
  }
  return free_db_and_close_file (markov_chain_ptr, file, EXIT_SUCCESS);
}