


#include "User.h"
#include "RecommendationSystem.h"
#include <vector>

using std::vector;

// See full documentation in header file
User::User (const string &name, const rank_map &rank_movie,
            shared_ptr_reco_system_t &shared_ptr_reco_sys) : _name (name),
                                                             _rank_map_user (rank_movie), _ptr_recommendation_system
                                                                 (shared_ptr_reco_sys)
{
}

// See full documentation in header file
void User::add_movie_to_rs (const string &name, int year, const
vector<double> &features, double rate)
{
    _ptr_recommendation_system->add_movie (name, year, features);
    sp_movie ptr_movie = _ptr_recommendation_system->get_movie (name, year);
    _rank_map_user[ptr_movie] = rate;
}

// See full documentation in header file
sp_movie User::get_recommendation_by_content () const
{
    return _ptr_recommendation_system->recommend_by_content (*this);
}

// See full documentation in header file
double User::get_prediction_score_for_movie (const string &name, int year,
                                             int k) const
{
    sp_movie ptr_movie = _ptr_recommendation_system->get_movie (name, year);
    return _ptr_recommendation_system->predict_movie_score
        (*this, ptr_movie, k);
}

// See full documentation in header file
sp_movie User::get_recommendation_by_cf (int k) const
{
    return _ptr_recommendation_system->recommend_by_cf (*this, k);
}

// See full documentation in header file
std::ostream &operator<< (std::ostream &os, const User &user)
{
    os << "name: " << user._name << std::endl;
    os << *user._ptr_recommendation_system;
    return os;
}



