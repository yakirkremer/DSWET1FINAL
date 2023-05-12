//
// Created by yakir on 5/10/2023.
//

#include "User.h"
User::User(int Id, bool vip): DbObj(Id, vip),groupId(0){
    try{
        views = new int[GENRES_NUM];
        for (int i = 0; i < GENRES_NUM; ++i)
            views[i] = 0;
        group = NULL;
        groupViews = NULL;
        groupViewsTmp = NULL;

    }
    catch (...)
    {
        throw std::bad_alloc();
    }
}

int User::genreNum(Genre genre)const{
    /* switch (genre) {
         case Genre::COMEDY:
             return 0;
         case Genre::DRAMA:
             return 1;
         case Genre::ACTION:
             return 2;
         case Genre::FANTASY:
             return 3;
     }
     return 4;
     */
    return 0;
}

const int User::getViews(Genre genre)const{
    if(groupViewsTmp != NULL)
        return views[int(genre)] + groupViewsTmp[int(genre)];
    return views[int(genre)];
}

const int User::getViews(int genre)const{
    return views[genre];
}

int User::getGroupId()const{
    return groupId;
}
void User::setGroupId(int NewgroupId, AvlTreeNew<User*>* Newgroup){
    groupId = NewgroupId;
    group = Newgroup;
}
void User::watch(Movie *movie) {
    if(movie->Vip() && !this->Vip())
        throw NotVip();
    movie->updateViews(1);
    views[int(movie->getGenre())]+=1;
    if(groupId!= 0 && groupViews != NULL)
        groupViews[int(movie->getGenre())]+=1;

}

void User::rate(Movie *movie, int rating) {
    if(movie->Vip() && !this->Vip())
        throw NotVip();
    if(rating<0 || rating >100)
        throw NotValidInput();
    movie->updateRating(rating);
}

void User::updateUserViews() {
    for (int i = 0; i <GENRES_NUM ; ++i) {
        views[i] += groupViewsTmp[i];
    }
}