

#include <algorithm>
#include <set>
#include "RecommendationSystem.h"

using std::set;
typedef std::pair<double, sp_movie> t_pair_d_sp;

// See full documentation in header file
sp_movie RecommendationSystem::add_movie (const string &name, int year,
                                          const vector<double> &features)
{
  sp_movie new_movie = std::make_shared<Movie> (name, year);
  _db_rank_movie[new_movie] = features;
  return new_movie;
}

// See full documentation in header file
sp_movie RecommendationSystem::get_movie (const string &name, int year) const
{
  sp_movie temp = std::make_shared<Movie> (name, year);

  if (_db_rank_movie.find (temp) != _db_rank_movie.end ())
  {
    return _db_rank_movie.find (temp)->first;
  }
  return nullptr;
}

// See full documentation in header file
double RecommendationSystem::average (const User &user) const
{
  double sum = 0;
  rank_map rank_map_user = user.get_ranks ();
  for (const auto &movie: rank_map_user)
  {
    sum += movie.second;
  }
  return (sum / (int) rank_map_user.size ());

}

// See full documentation in header file
rank_map RecommendationSystem::normalize_vector (const User &user) const
{
  double avg = average (user);
  rank_map rank_map_user = user.get_ranks ();
  for (auto &movie: rank_map_user)
  {
    movie.second -= avg;
  }
  return rank_map_user;
}

// See full documentation in header file
vector<double> RecommendationSystem::multiple_scalar_and_vector
    (const vector<double> &vec, double num) const
{
  vector<double> new_v;
  for (auto elem: vec)
  {
    new_v.push_back (elem * num);
  }
  return new_v;
}

// See full documentation in header file
vector<double> RecommendationSystem::plus_vector (vector<double> &v1,
                                                  vector<double> &v2)
{

  vector<double> temp;
  for (int i = 0; i < (int) v1.size (); i++)
  {
    temp.push_back (v1[i] + v2[i]);
  }
  return temp;
}

// See full documentation in header file
vector<double> RecommendationSystem::get_preference_vector (const User
                                                            &user)
{
  rank_map rank_map_user = normalize_vector (user);
  size_t size =0;
  for(const auto &movie1: _db_rank_movie)
  {
    size = movie1.second.size();
    break;
  }
  vector<double> calculate_vec (size);
  for (const auto &movie: rank_map_user)
  {
    vector<double> temp = multiple_scalar_and_vector (_db_rank_movie
                                                          .at (movie.first),
                                                          movie.second);
    calculate_vec = plus_vector (calculate_vec, temp);
  }
  return calculate_vec;
}

// See full documentation in header file
double RecommendationSystem::norma_vector (const vector<double> &vec) const
{
  double sum = 0;
  for (auto elem: vec)
  {
    sum += pow (elem, 2);
  }
  return std::sqrt (sum);
}

// See full documentation in header file
double RecommendationSystem::scalar_multiplication (const vector<double>
                                          &v1,const vector<double> &v2) const
{

  double res = 0;
  for (int i = 0; i < (int) v1.size (); i++)
  {
    res += v1[i] * v2[i];
  }
  return res;
}

// See full documentation in header file
bool RecommendationSystem::is_viewed_movie (const User &user, const sp_movie
&movie) const
{
  auto ranks_map = user.get_ranks ();
  return ranks_map.find (movie) != ranks_map.end ();
}

// See full documentation in header file
double RecommendationSystem::get_cos_a (vector<double> &pref_vector, double
norma_pref_vec, vector<double> &cur_movie_vec) const
{
  double scalar_result = scalar_multiplication (pref_vector,
                                                cur_movie_vec);
  double norma_vector_movie_result = norma_vector (cur_movie_vec);
  return scalar_result / (norma_pref_vec * norma_vector_movie_result);
}

// See full documentation in header file
sp_movie RecommendationSystem::recommend_by_content (const User &user)
{
  vector<double> pref_vector = get_preference_vector (user);
  double norma_pref_vector = norma_vector (pref_vector);
  double max_value_cos_a = THE_INITIAL_VALUE_OF_COS_A;
  sp_movie most_pref_movie = nullptr;
  for (auto &pair_movie: _db_rank_movie)
  {
    if (!is_viewed_movie (user, pair_movie.first))
    {
      double ans_cos_a = get_cos_a (pref_vector, norma_pref_vector,
                                    pair_movie.second);
      if (ans_cos_a > max_value_cos_a)
      {
        max_value_cos_a = ans_cos_a;
        most_pref_movie = pair_movie.first;
      }
    }
  }
  return most_pref_movie;
}

// See full documentation in header file
bool compare_func (const sp_movie &m1, const sp_movie
&m2)
{
  return (*m1 < *m2);
}

// See full documentation in header file
RecommendationSystem::RecommendationSystem () : _db_rank_movie (compare_func)
{
}

/** compare function for pair map in the redict_movie_score */
bool
vec_compare (const std::pair<double, sp_movie> &p1, const std::pair<double,
    sp_movie> &p2)
{
  return p2.first < p1.first;
}

// See full documentation in header file
double RecommendationSystem::get_ranking_of_movie_user (const User &user,
                                                        const sp_movie &movie)
{
  auto ranks_map = user.get_ranks ();

  if (ranks_map.find (movie) != ranks_map.end ())
  {
    return ranks_map.find (movie)->second;
  }
  return NOT_FOUND;
}

// See full documentation in header file
double RecommendationSystem::predict_movie_score (const User &user,
                                                  const sp_movie &movie, int k)
{
  vec_double_t vec_movie = _db_rank_movie.at (movie);
  double norma_vec_movie = norma_vector (vec_movie);
  vector<t_pair_d_sp> vec_calculate;
  for (auto pair_movie: _db_rank_movie)
  {
    if (is_viewed_movie (user, pair_movie.first))
    {
      double result_cos_a = get_cos_a (vec_movie,
                     norma_vec_movie, pair_movie.second);
      vec_calculate.emplace_back (result_cos_a, pair_movie.first);
    }
  }
  std::sort (vec_calculate.begin (), vec_calculate.end (),
             vec_compare);
  int count = 0;
  std::map<double, sp_movie> most_similar_movie;
  for (const t_pair_d_sp &pair_double_movie: vec_calculate)
  {
    most_similar_movie[pair_double_movie.first] = pair_double_movie.second;
    count++;
    if (count >= k)
    {
      break;
    }
  }
  double sum_similarity_and_ranking = 0, sum_similarity = 0;
  for (auto temp_movie: most_similar_movie)
  {
    sum_similarity_and_ranking += temp_movie.first * get_ranking_of_movie_user
        (user, temp_movie.second);
    sum_similarity += temp_movie.first;
  }
  return (sum_similarity_and_ranking / sum_similarity);
}
sp_movie RecommendationSystem::recommend_by_cf (const User &user, int k)
{
  sp_movie best_movie = nullptr;
  double best_rank = 0;
  for (auto &pair_movie_vector: _db_rank_movie)
  {
    if (!is_viewed_movie (user, pair_movie_vector.first))
    {
      double cur_predict_movie_score = predict_movie_score (user,
                                            pair_movie_vector.first, k);
      if (best_rank < cur_predict_movie_score)
      {
        best_rank = cur_predict_movie_score;
        best_movie = pair_movie_vector.first;
      }
    }
  }
  return best_movie;
}
std::ostream &operator<< (std::ostream &os, const RecommendationSystem
&recommendation_system)
{
  for (const auto &pair_movie_vector:
                recommendation_system._db_rank_movie)
  {
    os << *pair_movie_vector.first;
  }
  return os;
}












