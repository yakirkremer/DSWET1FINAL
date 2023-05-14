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

 int User::getViews(Genre genre)const{
    if(groupViewsTmp != NULL)
        return views[int(genre)] + groupViewsTmp[int(genre)];
    return views[int(genre)];
}

int User::getGroupViews(int genre)const{
    if(groupViewsTmp == NULL)
        return 0;
    if(genre == 4)
    {
        return  groupViewsTmp[0]+groupViewsTmp[1]+groupViewsTmp[2]+groupViewsTmp[3];
    }
    return groupViewsTmp[genre];
}
 int User::getViews(int genre)const{
    if(genre == 4)
    {
        return  views[0]+views[1]+views[2]+views[3]+ getGroupViews(genre);
    }

    return views[genre] + getGroupViews(genre);

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

bool User::operator==(User *other) const {
    return this->getId() == other->getId();
}