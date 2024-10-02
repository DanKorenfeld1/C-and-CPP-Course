//
// Created by 24565 on 6/1/2022.
//

#include "RecommendationSystemLoader.h"
#include "UsersLoader.h"
#include "Movie.h"

#define EXIT_FAIL_TEST 1
#define EXIT_SUCCESS_TEST 0

int main(){
//    Movie m("A",1999);
//    std::cout << m << std::endl;
//    auto rs = RecommendationSystemLoader::create_rs_from_movies
//        ("/mnt/c/Users/danko/CLionProjects/ex5/ex5-dankorenfeld"
//         "/RecommendationSystemLoader_input.txt");
//    std::cout << *rs << std::endl;
//    auto users = UsersLoader::create_users
//        ("/mnt/c/Users/danko/CLionProjects/ex5/ex5-dankorenfeld/UsersLoader_input.txt",std::move(rs));
//    std::cout << users[0] << std::endl;
//  Movie m("ABC",1999);
//  std::cout << m << std::endl;
//  auto rs = RecommendationSystemLoader::create_rs_from_movies
//      (        "RecommendationSystemLoader_input.txt");
//  std::cout << *rs << std::endl;
//  auto users = UsersLoader::create_users
//      ("UsersLoader_input.txt",std::move(rs));
//    std::cout << users[2] << std::endl;
//    std::cout << *users[0].get_recommendation_by_content() << std::endl;
//  std::cout << users[2].get_prediction_score_for_movie ("Titanic",1997,2) << std::endl;
//  std::cout << *users[2].get_recommendation_by_cf(2) << std::endl;
//  users[0].add_movie_to_rs ("Avatar", 2008,{1,2,3,4},6);
//  std::cout << users[0] << std::endl;
//
//  Movie m1("A",1998);
//  Movie m2("B",1996);
//  Movie m3("C",1998);
//  std::cout << "m1<m3: " << (m1<m3) << " m3<m1: "<<(m3<m1)<<std::endl;


  auto rs = RecommendationSystemLoader::create_rs_from_movies ("presubmit.in_m5");
  std::vector<User> user = UsersLoader::create_users ("presubmit.in_u5", std::move (rs));
//  std::cout<<user[0].get_recommendation_by_content ()->get_name ()<<std::endl;
//  std::cout<<user[2].get_recommendation_by_content ()->get_name ()<<std::endl;
//  std::cout<<user[4].get_recommendation_by_content ()->get_name ()<<std::endl;
//  std::cout<<user[6].get_recommendation_by_content ()->get_year ()<<std::endl;
//  std::cout<<user[14].get_recommendation_by_content ()->get_name ()<<std::endl;
  if (user[0].get_recommendation_by_content ()->get_name () != "TheSilence"
      || user[2].get_recommendation_by_content ()->get_name () !=
         "HighandLow" ||
      user[4].get_recommendation_by_content ()->get_name () != "CityLights" ||
      user[6].get_recommendation_by_content ()->get_year () != 1992 ||
      user[14].get_recommendation_by_content ()->get_name () != "Casablanca")
  {
    std::cout
        << "get_recommendation_by_content from User didn't return the correct output (only negative scores)"
        << std::endl;
    return EXIT_FAIL_TEST;
  }

  return EXIT_SUCCESS_TEST;
}