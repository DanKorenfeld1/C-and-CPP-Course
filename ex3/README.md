
# Linked List and Markov Chain Project

This project implements a linked list data structure and a Markov chain generator for text content. The Markov chain is used to generate random text based on input tweets, leveraging the linked list data structure for efficient word transitions. 

This project is designed as a starting point for Natural Language Processing (NLP) tasks. The generated text aims to simulate tweets by learning patterns from the provided input and producing new, coherent sentences based on those patterns.

## Project Structure

- `linked_list.h`: Header file defining the structure and operations of a linked list.
- `linked_list.c`: Implementation of the linked list functions.
- `markov_chain.h`: Header file defining the Markov chain structure and operations.
- `markov_chain.c`: Implementation of the Markov chain functions.
- `tweets_generator.c`: The main file that reads tweets and generates text using the Markov chain.
- `justdoit_tweets.txt`: A text file containing a list of tweets related to the "Just Do It" campaign.

## Functionality

### Linked List
The linked list is used to store words and manage transitions between them. Each node represents a word, and the list tracks which words follow each other in the source text.

### Markov Chain
The Markov chain uses the linked list to generate new sentences. It selects a random word based on the frequency of occurrences in the original text and continues building the sentence by following word transitions.

### NLP Simulation
The program serves as an introduction to NLP concepts by generating text that mimics real tweets. It demonstrates how Markov chains can be applied to text generation tasks by learning the structure and flow of sentences from a given dataset.

## Usage

To compile the project using GCC:
```bash
gcc -o tweets_generator tweets_generator.c linked_list.c markov_chain.c
```

Then, run the program with the tweets input file:
```bash
./tweets_generator justdoit_tweets.txt
```

The program will generate random tweets based on the input.

## Purpose
This project serves as a simple demonstration of how basic NLP techniques can be used to generate coherent text. It can be extended for more complex NLP tasks such as text prediction, language modeling, and chatbot development.
