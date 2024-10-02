#include <string.h> // For strlen(), strcmp(), strcpy()
#include "markov_chain.h"

#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

#define EMPTY -1
#define BOARD_SIZE 100
#define DECIMAL_BASE 10
#define NUMBER_ARG 3
#define MAX_GENERATION_LENGTH 60

#define DICE_MAX 6
#define NUM_OF_TRANSITIONS 20

typedef enum ArgumentsFromCli
{
    NUMBER_OF_SEED_ARG = 1,
    NUMBER_OF_TWEETS_ARG,
} ArgumentsFromCli;

#define READ "r"
#define ERROR_FILE_INVALID "ERROR: the file isn't open"
#define ERROR_NUMBER_ARGUMENT "Usage: the number of the argument should "\
"be 2"

#define FORMAT_START_ROUND "Random Walk %d: "
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

static bool check_number_of_arg (int argc)
{
    return (argc == NUMBER_ARG);
}

/**
 * function that check all the test about Input/Output
 * @param argc the number of the argv
 * @param argv the arg that the program get from the CLI
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
static int all_test_io (int argc)
{
    if (!check_number_of_arg (argc))
    {
        return fail_function (ERROR_NUMBER_ARGUMENT);
    }
    return true;
}

/**
 * represents the transitions by ladders and snakes in the game
 * each tuple (x,y) represents a ladder from x to if x<y or a snake otherwise
 */
const int transitions[][2] = {{13, 4},
                              {85, 17},
                              {95, 67},
                              {97, 58},
                              {66, 89},
                              {87, 31},
                              {57, 83},
                              {91, 25},
                              {28, 50},
                              {35, 11},
                              {8,  30},
                              {41, 62},
                              {81, 43},
                              {69, 32},
                              {20, 39},
                              {33, 70},
                              {79, 99},
                              {23, 76},
                              {15, 47},
                              {61, 14}};

/**
 * struct represents a Cell in the game board
 */
typedef struct Cell
{
    int number; // Cell number 1-100
    int ladder_to;  // ladder_to represents the jump of the ladder in case
    // there is one from this square
    int snake_to;  // snake_to represents the jump of the snake in case there
    // is one from this square
    //both ladder_to and snake_to should be -1 if the Cell doesn't have them
} Cell;

/** Error handler **/
static int handle_error (char *error_msg, MarkovChain **database)
{
    printf ("%s", error_msg);
    if (database != NULL)
    {
        free_database (database);
    }
    return EXIT_FAILURE;
}

static int create_board (Cell *cells[BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        cells[i] = malloc (sizeof (Cell));
        if (cells[i] == NULL)
        {
            for (int j = 0; j < i; j++)
            {
                free (cells[j]);
            }
            handle_error (ALLOCATION_ERROR_MASSAGE, NULL);
            return EXIT_FAILURE;
        }
        *(cells[i]) = (Cell) {i + 1, EMPTY, EMPTY};
    }

    for (int i = 0; i < NUM_OF_TRANSITIONS; i++)
    {
        int from = transitions[i][0];
        int to = transitions[i][1];
        if (from < to)
        {
            cells[from - 1]->ladder_to = to;
        }
        else
        {
            cells[from - 1]->snake_to = to;
        }
    }
    return EXIT_SUCCESS;
}

/**
 * fills database
 * @param markov_chain
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
static int fill_database (MarkovChain *markov_chain)
{
    Cell *cells[BOARD_SIZE];
    if (create_board (cells) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }
    MarkovNode *from_node = NULL, *to_node = NULL;
    size_t index_to;
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        add_to_database (markov_chain, cells[i]);
    }

    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        from_node = get_node_from_database (markov_chain, cells[i])->data;

        if (cells[i]->snake_to != EMPTY || cells[i]->ladder_to != EMPTY)
        {
            index_to = MAX(cells[i]->snake_to, cells[i]->ladder_to) - 1;
            to_node = get_node_from_database (markov_chain, cells[index_to])
                ->data;
            add_node_to_frequencies_list (from_node, to_node,
                                          markov_chain);
        }
        else
        {
            for (int j = 1; j <= DICE_MAX; j++)
            {
                index_to = ((Cell *) (from_node->data))->number + j - 1;
                if (index_to >= BOARD_SIZE)
                {
                    break;
                }
                to_node = get_node_from_database (markov_chain, cells[index_to])
                    ->data;
                add_node_to_frequencies_list (from_node, to_node,
                                              markov_chain);
            }
        }
    }
    // free temp arr
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        free (cells[i]);
    }
    return EXIT_SUCCESS;
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
 * function that print the data the get
 * @param data the data to print
 */
static void print_func_cell (void *data)
{
    Cell *cell_data = (Cell *) data;
    if (cell_data->ladder_to != EMPTY)
    {
        printf ("[%d]-ladder to %d -> ", cell_data->number, cell_data->ladder_to);
    }
    else if (cell_data->snake_to != EMPTY)
    {
        printf ("[%d]-snake to %d -> ", cell_data->number, cell_data->snake_to);
    }
    else if (cell_data->number == BOARD_SIZE)
    {
        printf ("[%d]", cell_data->number);
    }
    else
    {
        printf ("[%d] -> ", cell_data->number);
    }

}
/**
 * free the data from char typer
 * @param data the data to free
 */
static void free_data (void *data)
{
    free (data);
    data = NULL;
}

/**
 * function that implement like strdup in string lib
 * @param str the string to duplicate
 * @return string
 */
static void *copy_cell (const Cell *cell)
{
    Cell *cellcpy = calloc (1, sizeof (Cell));
    if (!cellcpy)
    {
        return NULL;
    }
    cellcpy->number = cell->number;
    cellcpy->ladder_to = cell->ladder_to;
    cellcpy->snake_to = cell->snake_to;
    return cellcpy;
}

/**
 * check if the data is the last of the sentence or the sequence
 * @param data the data to check
 * @return true if is the lase, else: false
 */
static bool is_last_cell (void *data)
{
    Cell *cell = (Cell *) data;
    if (cell->number == BOARD_SIZE)
    {
        return true;
    }
    return false;
}
/**
 * function that compare between cell1 and cell2
 * @param cell1 the first cell
 * @param cell2 the second cell
 * @return int (if + cell1 bigger, if - cell2 bigger, if 0 ->equal)
 */
static int comp_func_cell (void *cell1, void *cell2)
{
    Cell *cell1_c = (Cell *) cell1;
    Cell *cell2_c = (Cell *) cell2;
    return (cell1_c->number - cell2_c->number);
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
        if (markov_chain_ptr != NULL)
        {
            free (markov_chain_ptr);
        }
        return NULL;
    }
    markov_chain_ptr->database = link_list;
    markov_chain_ptr->print_func = print_func_cell;
    markov_chain_ptr->comp_func = (comp_func_type) comp_func_cell;
    markov_chain_ptr->free_data = free_data;
    markov_chain_ptr->copy_func = (copy_func_type) copy_cell;
    markov_chain_ptr->is_last = is_last_cell;
    return markov_chain_ptr;
}

/**
 * function that free the allocation of the database, and close the file
 * @param ptr_chain ptr to markov chain
 * @param to_return the number that need to return
 * @return EXIT_SUCCESS if all the running was valid, EXIT_FAILURE otherwise
 */
static int free_db_and_close_file (MarkovChain *ptr_markov_chain,
                                   int to_return)
{
    free_database (&ptr_markov_chain);
    return to_return;
}

/**
 * @param argc num of arguments
 * @param argv 1) Seed
 *             2) Number of sentences to generate
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int main (int argc, char *argv[])
{
    int ret = all_test_io (argc);
    if (!ret)
    {
        return EXIT_FAILURE;
    }
    int seed = (int) strtol (argv[NUMBER_OF_SEED_ARG], NULL,
                             DECIMAL_BASE);
    srand (seed);
    MarkovChain *markov_chain_ptr = allocate_markov_chain ();
    if (markov_chain_ptr == NULL)
    {
        return EXIT_FAILURE;
    }
    int ans = fill_database (markov_chain_ptr);
    if (ans == EXIT_FAILURE)
    {
        fprintf (stdout, ALLOCATION_ERROR_MASSAGE);
        return free_db_and_close_file (markov_chain_ptr, EXIT_FAILURE);
    }
    int number_of_tweet = (int) strtol (argv[NUMBER_OF_TWEETS_ARG],
                                        NULL, DECIMAL_BASE);
    for (int i = 1; i <= number_of_tweet; i++)
    {
        MarkovNode *first = markov_chain_ptr->database->first->data;
        if (first == NULL)
        {
            break;
        }
        printf (FORMAT_START_ROUND, i);
        int max_len = (MAX_GENERATION_LENGTH
                       < markov_chain_ptr->database->size) ?
                      MAX_GENERATION_LENGTH : markov_chain_ptr->database->size;
        generate_tweet (markov_chain_ptr, first, max_len);
        printf ("\n");
    }
    return free_db_and_close_file (markov_chain_ptr, EXIT_SUCCESS);
}
