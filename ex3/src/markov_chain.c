#include "markov_chain.h"
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS_NOT_EXIST (-1)
#define STARTER_SIZE_OF_LIST_FREQUENCY 1
#define FIRST_VIEW_FREQUENCY_LIST 1
#define EMPTY 0

// See full documentation in header file
Node *get_node_from_database (MarkovChain *markov_chain, char *data_ptr)
{
    Node *first = markov_chain->database->first;
    for (int i = 0; i < markov_chain->database->size; i++)
    {
        if (strcmp ((const char *) first->data->data, data_ptr) == 0)
        {
            return first;
        }
        else
        {
            first = first->next;
        }
    }
    return NULL;
}

////debug function, not for submit
void print_markov_chain (MarkovChain *markov_chain)
{
    Node *ptr = markov_chain->database->first;
    int count = 0;
    while (count < markov_chain->database->size && ptr != NULL)
    {
        printf ("{%s}->", ptr->data->data);
        ptr = ptr->next;
    }
    printf ("\n");
}

/**
 * function that initial new markov node
 * @param new_markov_node new markov node
 * @param new_ptr_data string (the data for the markov node)
 */
void initial_new_markov_node (MarkovNode *new_markov_node, char *new_ptr_data)
{
    new_markov_node->data = new_ptr_data;
    new_markov_node->frequency_list = NULL;
    new_markov_node->current_size = EMPTY;
    new_markov_node->total_frequency = EMPTY;
}
/**
 * function that implement like strdup in string lib
 * @param str the string to duplicate
 * @return string
 */
char *strdupp (const char *str)
{
    char *dup = calloc (1, strlen (str) + 1);
    if (!dup)
    {
        return NULL;
    }
    strcpy (dup, str);
    return dup;
}

/**
 * build the Node and add to the data base
 * @param markov_chain the markov chain
 * @param data_ptr the word of the chain
 * @return Node if success, otherwise: NULL
 */
Node *build_the_node_data_base (MarkovChain *markov_chain, char *data_ptr)
{
    MarkovNode *new_markov_node = calloc (1, sizeof (MarkovNode));
    if (!new_markov_node)
    {
        return NULL;
    }
    char *new_ptr_data = strdupp (data_ptr);
    if (!new_ptr_data)
    {
        free (new_markov_node);
        return NULL;
    }
    initial_new_markov_node (new_markov_node, new_ptr_data);
    int ans = add (markov_chain->database, new_markov_node);
    if (ans)
    {
        if (new_markov_node != NULL)
        {
            free (new_markov_node);
        }
        if (new_ptr_data != NULL)
        {
            free (new_ptr_data);
        }
        return NULL;
    }
    return markov_chain->database->last;
}

// See full documentation in header file
Node *add_to_database (MarkovChain *markov_chain, char *data_ptr)
{
    if (markov_chain->database->size == EMPTY)
    {
        return build_the_node_data_base (markov_chain, data_ptr);
    }
    else
    {
        Node *ptr = get_node_from_database (markov_chain, data_ptr);
        if (ptr)
        { //exist
            return ptr;
        }
        else
        { //isn't exist
            return build_the_node_data_base (markov_chain, data_ptr);
        }
    }
}

////debug function, not for submit
void print_node_frequency_list (MarkovNode *markov_node)
{
    yellow ();
    printf ("{ %s } total-freq: %d >> ", markov_node->data,
            markov_node->total_frequency);
    for (int i = 0; i < markov_node->current_size; i++)
    {
        red ();
        printf ("{node:%s, freq: %d} ->",
                markov_node->frequency_list[i].markov_node->data,
                markov_node->frequency_list[i].frequency);
    }
    reset ();
    printf ("\n");
}

/**
 * check if the second node in the frequency_list of first_node
 * @param first_node the first node
 * @param second_node the second node
 * @return if exist: returnthe index of the markov node in the
 * frequency_list, otherwise: return -1
 */
int search_node_in_frequency_list (MarkovNode *first_node,
                                   MarkovNode *second_node)
{
    for (int i = 0; i < first_node->current_size; i++)
    {
        if ((first_node->frequency_list)[i].markov_node == second_node)
        {
            return i;
        }
    }
    return IS_NOT_EXIST;
}

/**
 * function that realloc, but safe
 * @param old_p the old pointer
 * @param new_size the new size to allocate
 * @return new pointer if success, otherwise NULL
 */
void *safe_realloc (void *old_p, size_t new_size)
{
    if (new_size == 0)
    {
        return NULL;
    }
    void *new_p = realloc (old_p, new_size);
    if (!new_size)
    {
        free (old_p);
        return NULL;
    }
    return new_p;
}

/**
 * function that free the markov node frequency stuct and print error message
 * @param first_node the MarkovNode that contain the frequency list
 * @return
 */
bool *free_markov_node_frequency_error (MarkovNode *first_node)
{
    if (first_node != NULL)
    {
        free (first_node->frequency_list);
        first_node->frequency_list = NULL;
    }
    fprintf (stdout, ALLOCATION_ERROR_MASSAGE);
    return false;
}

/**
 * function that free the markov node frequency stuct
 * @param first_node the MarkovNode that contain the frequency list
 * @return
 */
void free_markov_node_frequency (MarkovNode *first_node)
{
    if (first_node != NULL)
    {
        free (first_node->frequency_list);
        first_node->frequency_list = NULL;
    }
}

// See full documentation in header file
bool add_node_to_frequencies_list (MarkovNode *first_node, MarkovNode
*second_node)
{
    if (first_node != NULL && first_node->frequency_list == NULL)
    {
        MarkovNodeFrequency *freq_list = calloc (STARTER_SIZE_OF_LIST_FREQUENCY,
                                                 sizeof (MarkovNodeFrequency));
        if (!freq_list) //error allocate
        {
            return false;
        }
        freq_list[first_node->current_size].markov_node = second_node;
        freq_list[first_node->current_size].frequency =
            STARTER_SIZE_OF_LIST_FREQUENCY;
        first_node->frequency_list = freq_list;
        first_node->current_size = FIRST_VIEW_FREQUENCY_LIST;
        first_node->total_frequency++;
        return true;
    }
    else
    {
        int index = search_node_in_frequency_list (first_node, second_node);
        if (index != IS_NOT_EXIST)
        { //exist
            first_node->frequency_list[index].frequency++;
            first_node->total_frequency++;
        }
        else
        {
            MarkovNodeFrequency *check_pointer = safe_realloc
                (first_node->frequency_list,
                 (first_node->current_size + 1)
                 * sizeof (MarkovNodeFrequency));
            if (!check_pointer)
            {
                return free_markov_node_frequency_error (first_node);
            }
            check_pointer[first_node->current_size] = (MarkovNodeFrequency) {
                second_node, FIRST_VIEW_FREQUENCY_LIST};
            first_node->frequency_list = check_pointer;
            first_node->frequency_list[first_node->current_size]
                .frequency = FIRST_VIEW_FREQUENCY_LIST;
            first_node->total_frequency++;
            (first_node->current_size)++;
        }
        return true;
    }
}
/**
 * function that check  if the markovchain or the database is null
 * @param ptr_chain pointer to pointer to markovchain
 * @return boolean: true if null, otherwise false
 */
int is_markovchain_or_db_null (MarkovChain **ptr_chain)
{
    if (ptr_chain == NULL)
    {
        return true;
    }
    if ((*ptr_chain)->database == NULL)
    {
        free (ptr_chain);
        return true;
    }
    return false;
}

/**
 * function that free the markovchain and the db
 * @param ptr_chain ptr to markovchain
 */
void free_markov_chain_and_db (MarkovChain **ptr_chain)
{
    if ((*ptr_chain)->database != NULL)
    {
        free ((*ptr_chain)->database);
    }
    if (ptr_chain != NULL)
    {
        free (*ptr_chain);
    }
}

// See full documentation in header file
void free_database (MarkovChain **ptr_chain)
{
    if (is_markovchain_or_db_null (ptr_chain))
    {
        return;
    }
    LinkedList *database = (*ptr_chain)->database;
    int counter = 0;
    while (database->first != database->last) //counter<=database->size
    {
        MarkovNode *markov_node = database->first->data;
        free_markov_node_frequency (markov_node);
        if (markov_node != NULL)
        {
            free (markov_node->data);
            markov_node->data = NULL;
        }
        free (markov_node);
        markov_node = NULL;
        Node *cur = database->first;
        database->first = database->first->next;
        if (cur != NULL)
        {
            free (cur);
        }
        counter++;
    }
    database->last = NULL;
    if (database != NULL)
    {
        if (database->first != NULL)
        {
            MarkovNode *markov_node = database->first->data;
            free_markov_node_frequency (markov_node);
            if (markov_node != NULL)
            {
                free (markov_node->data);
                markov_node->data = NULL;
            }
            free (markov_node);
            markov_node = NULL;
            Node *cur = database->first;
            if (cur != NULL)
            {
                free (cur);
            }
        }
    }
    free_markov_chain_and_db (ptr_chain);
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
/**
 * function that check if the word is the end of the sentence
 * @param word the word that checked
 * @return boolean: true if the end of the sentence, false otherwise
 */
bool is_end_of_sentence (const char *word)
{
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (word[i + 1] == '\0' && word[i] == '.')
        {
            return true;
        }
    }
    return false;
}

// See full documentation in header file
MarkovNode *get_first_random_node (MarkovChain *markov_chain)
{
    if (markov_chain->database->size == 0)
    {
        return NULL;
    }
    int random_number = get_random_number (markov_chain->database->size);
    Node *node = markov_chain->database->first;
    int counter = 0;
    while (counter < markov_chain->database->size)
    {
        if (counter == random_number)
        {
            if (!is_end_of_sentence (node->data->data))
            {
                return node->data;
            }
            else
            {
                break;
            }
        }
        counter++;
        node = node->next;
    }
    return get_first_random_node (markov_chain);
}

// See full documentation in header file
MarkovNode *get_next_random_node (MarkovNode *state_struct_ptr)
{
    int random_number = get_random_number (state_struct_ptr->total_frequency);
    for (int i = 0; i < state_struct_ptr->total_frequency; i++)
    {
        if (state_struct_ptr->frequency_list[i].frequency > random_number)
        {
            return state_struct_ptr->frequency_list[i].markov_node;
        }
        else
        {
            random_number -= state_struct_ptr->frequency_list[i].frequency;
        }
    }

    return NULL;
}

// See full documentation in header file
void generate_tweet (MarkovChain *markov_chain, MarkovNode *
first_node, int max_length)
{
    if (first_node == NULL)
    {
        first_node = get_first_random_node (markov_chain);
    }
    int counter = 1;
    MarkovNode *markov_node = first_node;
    counter++;
    while (counter < max_length && counter <= MAX_LEN_TWEET
           && !is_end_of_sentence
               (markov_node->data))
    {
        markov_node = get_next_random_node (markov_node);
        printf (" %s", markov_node->data);
        counter++;
    }
    printf ("\n");

}




