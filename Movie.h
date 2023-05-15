//
// Created by yakir on 5/10/2023.
//

#ifndef DSWET1NOSHARED_MOVIE_H
#define DSWET1NOSHARED_MOVIE_H
#include "DbObj.h"

struct MovieKey{
    int rating;
    int views;
    int Id;
    bool operator<(const MovieKey& other)const{
        if (this->rating == other.rating) {
            if(this->views == other.views){
                return this->Id > other.Id;
            }
            return this->views < other.views;
        }
        return this->rating < other.rating;
    }
    bool operator==(const MovieKey& other)const
    {
        return this->Id == other.Id;
    }
    MovieKey(int rating, int views, int Id):rating(rating),views(views),Id(Id){}
    MovieKey():rating(0),views(0),Id(-1){}
};

class Movie: public DbObj{

int views;
int rating;
int rates;
Genre genre;
MovieKey key;
public:
    Movie(int,bool,int,Genre);

    const MovieKey& getCmp()const{
        return key;
    }
    bool operator==(const Movie& other)const;
    bool operator<(const Movie& other)const;
    void updateRating(int rating);
    void updateViews(int viewsNum = 1);
    Genre getGenre()const;
    virtual ~Movie() = default;


};






#endif //DSWET1NOSHARED_MOVIE_H
