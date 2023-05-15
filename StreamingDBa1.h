// 
// 234218 Data Structures 1.
// Semester: 2023B (spring).
// Wet Exercise #1.
// 
// Recommended TAB size to view this file: 8.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef STREAMINGDBA1_H_
#define STREAMINGDBA1_H_

#include "wet1util.h"
#include "MoviesTree.h"
#include "GenreMoviesTree.h"
#include "GroupsTree.h"

class streaming_database {
private:
	//
	// Here you may add anything you want
	//
	MoviesTree* movies;
    GenreMoviesTree* moviesSortedByRating;
    GenreMoviesTree* comedy;
    GenreMoviesTree* drama;
    GenreMoviesTree* action;
    GenreMoviesTree* fantasy;
    UsersTree* users;
    GroupsTree* groups;

    GenreMoviesTree* getGenreTree(Movie* movie){
        if(movie->getGenre() == Genre::COMEDY)
            return comedy;
        if(movie->getGenre() == Genre::DRAMA)
            return drama;
        if(movie->getGenre() == Genre::ACTION)
            return action;
        if(movie->getGenre() == Genre::FANTASY)
            return fantasy;
        return moviesSortedByRating;
    }

    GenreMoviesTree* getGenreTree(Genre genre){
        if(genre == Genre::COMEDY)
            return comedy;
        if(genre == Genre::DRAMA)
            return drama;
        if(genre == Genre::ACTION)
            return action;
        if(genre == Genre::FANTASY)
            return fantasy;
        return moviesSortedByRating;

    }

    int genreToInt(Genre genre){
        if(genre == Genre::COMEDY)
            return 0;
        if(genre == Genre::DRAMA)
            return 1;
        if(genre == Genre::ACTION)
            return 2;
        if(genre == Genre::FANTASY)
            return 3;
        return 4;
    }
    void check_input( int Id1,int Id2,int rating) {
        if ( rating <0 ||rating >100 || Id1 <=0 || Id2 <= 0)
            throw NotValidId();
    }

    void check_input(int Id) {
        if (Id <= 0 )
            throw NotValidId();
    }
    void check_input(int Id, Genre genre, int views) {
        if (Id <= 0 || genre == Genre::NONE || views < 0)
            throw NotValidInput();
    }

public:
	// <DO-NOT-MODIFY> {
	
	streaming_database();

	virtual ~streaming_database();
	
	StatusType add_movie(int movieId, Genre genre, int views, bool vipOnly);
	
	StatusType remove_movie(int movieId);
	
	StatusType add_user(int userId, bool isVip);
	
	StatusType remove_user(int userId);
	
	StatusType add_group(int groupId);
	
	StatusType remove_group(int groupId);

	StatusType add_user_to_group(int userId, int groupId);
	
	StatusType user_watch(int userId, int movieId);

    StatusType group_watch(int groupId,int movieId);

    output_t<int> get_all_movies_count(Genre genre);

    StatusType get_all_movies(Genre genre, int *const output);
	
	output_t<int> get_num_views(int userId, Genre genre);

    StatusType rate_movie(int userId, int movieId, int rating);
	
	output_t<int> get_group_recommendation(int groupId);
	
	// } </DO-NOT-MODIFY>
};

#endif // STREAMINGDBA1_H_
