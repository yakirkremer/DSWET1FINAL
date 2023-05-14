//
// Created by yakir on 5/10/2023.
//

#ifndef DSWET1NOSHARED_MOVIE_H
#define DSWET1NOSHARED_MOVIE_H
#include "DbObj.h"


class Movie: public DbObj{
int views;
int rating;
int rates;
Genre genre;
public:
    Movie(int,bool,int,Genre);


    bool operator==(const Movie& other)const;
    bool operator<(const Movie& other)const;
    void updateRating(int rating);
    void updateViews(int viewsNum = 1);
    Genre getGenre()const;
    virtual ~Movie() = default;


};






#endif //DSWET1NOSHARED_MOVIE_H
