# Movie Recommendation System

This project implements a movie recommendation system in C++. It provides functionality to recommend movies to users based on their preferences and viewing history.

## Features

- User management
- Movie database
- Content-based recommendation
- Collaborative filtering recommendation
- Prediction of movie scores for users

## Components

### 1. User

- Represents a user in the system
- Stores user's name and movie rankings
- Provides methods for adding movies and getting recommendations

### 2. Movie

- Represents a movie with its name and release year
- Implements comparison and output stream operators

### 3. RecommendationSystem

- Core component for generating movie recommendations
- Implements content-based and collaborative filtering algorithms
- Manages the movie database

### 4. UsersLoader

- Utility class for loading user data from files

### 5. RecommendationSystemLoader

- Utility class for loading movie data and creating the recommendation system

## Technical Details

### Data Structures

- `std::unordered_map`: Used for efficient storage and retrieval of movie rankings (`rank_map`)
- `std::map`: Used for storing the movie database with features (`db_rank_movie_t`)
- `std::vector`: Used for storing movie features and user preference vectors
- Smart Pointers: `std::shared_ptr<Movie>` (alias `sp_movie`) is used for movie objects to manage memory efficiently

### Algorithms

1. Content-based Recommendation:
   - Calculates user preference vector based on their movie rankings
   - Uses vector operations (scalar multiplication, vector addition, normalization)
   - Computes cosine similarity between user preferences and movie features

2. Collaborative Filtering:
   - Implements item-based collaborative filtering
   - Uses k-nearest neighbors algorithm to find similar movies
   - Predicts user ratings based on ratings of similar movies

3. Score Prediction:
   - Combines collaborative filtering with user's average rating
   - Normalizes user ratings to account for individual rating tendencies

### Key C++ Features Used

- Templates: Used in various container types
- Operator Overloading: Implemented for `Movie` class (e.g., `operator<`, `operator<<`)
- Function Objects: Custom hash and equality functions for `sp_movie`
- Move Semantics: Used in `UsersLoader::create_users` for efficient transfer of `RecommendationSystem`

### File I/O

- Uses `std::ifstream` for reading movie and user data from files
- Implements custom parsing logic to handle the specific file formats for movies and user rankings

### Error Handling

- Uses exceptions to handle potential errors in file loading and data processing
- Custom error messages defined for specific error conditions

## Usage

1. Load the movie database using `RecommendationSystemLoader`
2. Create users using `UsersLoader`
3. Use the `User` class methods to get recommendations and predictions

