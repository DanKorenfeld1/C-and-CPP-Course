
#include "markov_chain.h"
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STARTER_SIZE_OF_LIST_FREQUENCY 1
#define FIRST_VIEW_FREQUENCY_LIST 1
#define IS_NOT_EXIST (-1)
#define EMPTY 0

//debug function, not for submit
void print_node_frequency_list (MarkovNode *markov_node)
{
    yellow ();
    printf ("{ %s } total-freq: %d >> ", (char *) markov_node->data,
            markov_node->total_frequency);
    for (int i = 0; i < markov_node->current_size; i++)
    {
        red ();
        printf ("{node:%s, freq: %d} ->",
                (char *) markov_node->frequency_list[i].markov_node->data,
                markov_node->frequency_list[i].frequency);
    }
    reset ();
    printf ("\n");
}

//////debug function, not for submit
void print_markov_chain (MarkovChain *markov_chain)
{
    Node *ptr = markov_chain->database->first;
    int count = 0;
    while (count < markov_chain->database->size && ptr != NULL)
    {
        printf ("{%s}->", (char *) ptr->data->data);
        ptr = ptr->next;
    }
    printf ("\n");
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

// See full documentation in header file
MarkovNode *get_first_random_node (MarkovChain *markov_chain)
{
    if (markov_chain->database->size == EMPTY)
    {
        return NULL;
    }
    int random_number = get_random_number (markov_chain->database->size);
    Node *node = markov_chain->database->first;
    int counter = EMPTY;
    while (counter < markov_chain->database->size)
    {
        if (counter == random_number)
        {
            if (!markov_chain->is_last (node->data->data))
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
    markov_chain->print_func (first_node->data);
    MarkovNode *markov_node = first_node;
    counter++;
    while (counter <= max_length &&
           !markov_chain->is_last (markov_node->data))
    {
        markov_node = get_next_random_node (markov_node);
        markov_chain->print_func (markov_node->data);
        counter++;
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
void free_database (MarkovChain **markov_chain)
{
    if (is_markovchain_or_db_null (markov_chain))
    {
        return;
    }
    LinkedList *database = (*markov_chain)->database;
    int counter = EMPTY;
    while (database->first != database->last) //counter<=database->size
    {
        MarkovNode *markov_node = database->first->data;
        free_markov_node_frequency (markov_node);
        if (markov_node != NULL)
        {
            (*markov_chain)->free_data (markov_node->data);
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
    free_markov_chain_and_db (markov_chain);
}

/**
 * function that realloc, but safe
 * @param old_p the old pointer
 * @param new_size the new size to allocate
 * @return new pointer if success, otherwise NULL
 */
void *safe_realloc (void *old_p, size_t new_size)
{
    if (new_size == EMPTY)
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
 * check if the second node in the frequency_list of first_node
 * @param first_node the first node
 * @param second_node the second node
 * @return if exist: returnthe index of the markov node in the
 * frequency_list, otherwise: return -1
 */
int search_node_in_frequency_list (MarkovNode *first_node,
                                   MarkovNode *second_node,
                                   MarkovChain *markov_chain)
{
    for (int i = 0; i < first_node->current_size; i++)
    {
        if (markov_chain->comp_func ((first_node->frequency_list)[i]
                                         .markov_node->data,
                                     second_node->data) == 0)
        {
            return i;
        }
    }
    return IS_NOT_EXIST;
}

// See full documentation in header file
bool add_node_to_frequencies_list (MarkovNode *first_node, MarkovNode
*second_node, MarkovChain *markov_chain)
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
        int index = search_node_in_frequency_list (first_node, second_node,
                                                   markov_chain);
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

// See full documentation in header file
Node *get_node_from_database (MarkovChain *markov_chain, void *data_ptr)
{
    Node *first = markov_chain->database->first;
    for (int i = 0; i < markov_chain->database->size; i++)
    {
        if (markov_chain->comp_func (first->data->data, data_ptr) == 0)
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

/**
 * function that initial new markov node
 * @param new_markov_node new markov node
 * @param new_ptr_data string (the data for the markov node)
 * @param markov_chain the current markovchain
 */
void initial_new_markov_node (MarkovNode *new_markov_node, void *new_ptr_data)
{
    new_markov_node->data = new_ptr_data;
    new_markov_node->frequency_list = NULL;
    new_markov_node->current_size = EMPTY;
    new_markov_node->total_frequency = EMPTY;
}

/**
 * build the Node and add to the data base
 * @param markov_chain the markov chain
 * @param data_ptr the word of the chain
 * @return Node if success, otherwise: NULL
 */
Node *build_the_node_data_base (MarkovChain *markov_chain, void *data_ptr)
{
    MarkovNode *new_markov_node = calloc (1, sizeof (MarkovNode));
    if (!new_markov_node)
    {
        return NULL;
    }
    void *new_ptr_data = markov_chain->copy_func (data_ptr);
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
            new_markov_node = NULL;
        }
        markov_chain->free_data (new_ptr_data);
        return NULL;
    }
    return markov_chain->database->last;
}

// See full documentation in header file
Node *add_to_database (MarkovChain *markov_chain, void *data_ptr)
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

