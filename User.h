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
    AvlTreeNew<User*>* group;

public:
    AvlTreeNew<User*>* getGroup() {
        return group;
    }

    int* groupViews;
    int* groupViewsTmp;
    User(int Id, bool vip);
    virtual ~User(){
        delete[] views;
    }
        int genreNum(Genre genre)const;

    int getGroupViews(int genre)const;

     int getViews(Genre genre)const;
     int getViews(int genre)const;

    int getGroupId()const;
    void setGroupId(int group, AvlTreeNew<User*>* Newgroup);
    void watch(Movie* movie);
    void rate(Movie* movie, int);
    void updateUserViews();
    bool operator==(User* other)const;
};


class UsersTreeAbs:public AvlTreeNew<User*> {
protected:

    virtual bool leftSmallOperator(Node * cur, Node * other)const override {
        return cur->data->getId() < other->data->getId();
    }
    virtual bool equalOperator(Node * cur, Node * other)const override{
        return cur->data  == other->data;
    }
    virtual bool leftSmallOperator(int tmpKey, Node * other)const override{
        return tmpKey < other->data->getId();
    }
    virtual bool equalOperator(int tmpKey, Node * other) const override{
        return tmpKey == other->data->getId();
    }



    int getKey(Node* cur)const override{
        return cur->data->getId();
    }
public:
    UsersTreeAbs():AvlTreeNew<User *>(){}


    void remove(int UserKey) override{
        head = removeNode(head, UserKey);
        size--;
    }

};

class UsersTree:public UsersTreeAbs{
    void deleteDatas(Node *cur) {
        if (cur == NULL)
            return;


        deleteDatas(cur->right);
        deleteDatas(cur->left);
        delete cur->data;
        cur->data = NULL;
        return;
    }

    void deleteNode(Node * cur){
        delete cur->data;
        cur->right = NULL;
        cur->left = NULL;
        delete cur;
    }


public:
    ~UsersTree(){
        deleteDatas(head);
    }

};



#endif //DSWET1NOSHARED_USER_H
