//
// Created by yakir on 5/10/2023.
//



#include "Movie.h"



Movie::Movie(int Id, bool vip, int views, Genre genre): DbObj(Id,vip),views(views),rating(0), rates(0),genre(genre),
                                                        key(MovieKey(0,views,Id)) {
    if(genre == Genre::NONE)
    {

        throw NotValidInput();
    }
}
bool Movie::operator==(const Movie& other)const{
    return this->getId() == other.getId();
}
bool Movie::operator<(const Movie& other)const {
    if (this->rating == other.rating) {
        if(this->views == other.views){
            return this->getId() > other.getId();
        }
        return this->views < other.views;
    }
    return this->rating < other.rating;
}
void Movie::updateRating(int newRate) {
    int sumRating = rating * rates;
    sumRating += newRate;
    rates++;
    //rating = sumRating/rates;
    key.rating = sumRating/rates;
}

void Movie::updateViews(int viewsNum) {
    //views+= viewsNum;
    key.views += viewsNum;
}

Genre Movie::getGenre() const {
    return genre;
}
