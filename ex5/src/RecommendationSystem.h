
#ifndef RECOMMENDATIONSYSTEM_H
#define RECOMMENDATIONSYSTEM_H
#include "User.h"
#include <map>
#include <vector>
#include <cmath>

#define ERROR_MSG_INVALID_LEN_VECTORS "ERROR: the sizes of the vectors should"\
" be equal"
#define NOT_FOUND (-1)
//#define BAD_VALUE 1
#define THE_INITIAL_VALUE_OF_COS_A (-1.1)
using std::vector;
using std::map;
using std::string;

/** std::vector<double> (type)*/
typedef std::vector<double> vec_double_t;
typedef std::unordered_map<sp_movie, double, hash_func, equal_func> rank_map;

/** the database of all the rank movie (from the file) (type) */
typedef map<sp_movie, vec_double_t, equal_func> db_rank_movie_t;

class RecommendationSystem
{
 private:
  /** compare function for sorting the map */
  friend bool compare_func (const sp_movie &m1, const sp_movie &m2);

  db_rank_movie_t _db_rank_movie;
  /**
   * function that returns the average ranking of a particular user
   * @param user the user
   * @return the avg of the ranking movie
   */
  double average (const User &user) const;

  /**
   * function that normalizes the user's movie ranking list according to the
   * ranking average.
   * @param user the user
   * @return normalized rank_map
   */
  rank_map normalize_vector (const User &user) const;

  /**
   * function that calculates and returns the user's preferences vector
   * @param user the user
   * @return the user's preferences vector
   */
  vector<double> get_preference_vector (const User &user);

  /**
   * fucntion that multiple scalar and vector
   * @param vec <double> vector
   * @param num the scalar
   * @return new vactor<double> after the multiplication
   */
  vector<double> multiple_scalar_and_vector (const vector<double> &vec,
                                             double num) const;

  /** function that plus vector+vector */
  vector<double> plus_vector (vector<double> &v1, vector<double> &
  v2);

  /** funciton that calculate the norma of the vector*/
  double norma_vector (const vector<double> &vec) const;

  /** function that calculate the scalar multiplication of the vectors*/
  double scalar_multiplication (const vector<double> &v1, const
  vector<double> &v2) const;

  /** funciton that return the cos(a) after the scalar multiplication */
  double get_cos_a (vector<double> &pref_vector, double norma_pref_vec,
                    vector<double> &cur_movie_vec) const;

  /** return if the user viewed the movie or not*/
  bool is_viewed_movie (const User &user, const sp_movie &movie) const;

  /** return the ranking of the movie from the user*/
  double get_ranking_of_movie_user (const User &user, const sp_movie &movie);

 public:
  /** constractor for RecommendationSystem class */
  explicit RecommendationSystem ();
  /**
   * adds a new movie to the system
   * @param name name of movie
   * @param year year it was made
   * @param features features for movie
   * @return shared pointer for movie in system
   */
  sp_movie add_movie (const std::string &name, int year,
                      const std::vector<double> &features);

  /**
   * a function that calculates the movie with highest score based on movie
   * features
   * @param ranks user ranking to use for algorithm
   * @return shared pointer to movie in system
   */
  sp_movie recommend_by_content (const User &user);

  /**
   * a function that calculates the movie with highest predicted score based
   * on ranking of other movies
   * @param ranks user ranking to use for algorithm
   * @param k
   * @return shared pointer to movie in system
   */
  sp_movie recommend_by_cf (const User &user, int k);

  /**
   * Predict a user rating for a movie given argument using item cf procedure
   * with k most similar movies.
   * @param user_rankings: ranking to use
   * @param movie: movie to predict
   * @param k:
   * @return score based on algorithm as described in pdf
   */
  double predict_movie_score (const User &user, const sp_movie &movie,
                              int k);

  /**
   * gets a shared pointer to movie in system
   * @param name name of movie
   * @param year year movie was made
   * @return shared pointer to movie in system
   */
  sp_movie get_movie (const std::string &name, int year) const;

  /**
   * operator<< for RecommendationSystem
   * @param os ostream to output info with
   * @param recommendation_system recommendation_system to output
   */
  friend std::ostream &operator<< (std::ostream &os, const
  RecommendationSystem &recommendation_system);

};

#endif //RECOMMENDATIONSYSTEM_H
