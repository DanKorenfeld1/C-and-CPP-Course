CC = gcc
CXX_FLAGS = -Wall -Wextra -Wvla -std=c99
tweets: linked_list.o tweets_generator.o markov_chain.o
	${CC} ${CXX_FLAGS} linked_list.o tweets_generator.o markov_chain.o -o tweets
snake: linked_list.o snakes_and_ladders.o markov_chain.o
	${CC} ${CXX_FLAGS} linked_list.o snakes_and_ladders.o markov_chain.o -o snake
linked_list.o: linked_list.c linked_list.h
	${CC} ${CXX_FLAGS} -c linked_list.c
markov_chain.o: markov_chain.c markov_chain.h linked_list.h
	${CC} ${CXX_FLAGS} -c markov_chain.c
tweets_generator.o: tweets_generator.c markov_chain.h
	${CC} ${CXX_FLAGS} -c tweets_generator.c
snakes_and_ladders.o: snakes_and_ladders.c markov_chain.h
	${CC} ${CXX_FLAGS} -c snakes_and_ladders.c
clean:
	rm *.o