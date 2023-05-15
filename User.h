//
// Created by yakir on 5/10/2023.
//


#ifndef DSWET1NOSHARED_USER_H
#define DSWET1NOSHARED_USER_H
#include "Movie.h"



const int GENRES_NUM = 4;

class User: public DbObj{

    int* views;
    int groupId;
    AvlTreeNew<User*, int>* group;

public:
    AvlTreeNew<User*, int>* getGroup() {
        return group;
    }

    int* groupViews;
    int* groupViewsTmp;
    User(int Id, bool vip);
    virtual ~User(){
        delete[] views;
        views = NULL;
    }
        int genreNum(Genre genre)const;

    int getGroupViews(int genre)const;

     int getViews(Genre genre)const;
     int getViews(int genre)const;

    int getGroupId()const;
    void setGroupId(int group, AvlTreeNew<User*, int>* Newgroup);
    void watch(Movie* movie);
    void rate(Movie* movie, int);
    void updateUserViews();
    bool operator==(User* other)const;
};






#endif //DSWET1NOSHARED_USER_H
