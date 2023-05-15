//
// Created by yakir on 5/10/2023.
//

#ifndef DSWET1NOSHARED_GROUP_H
#define DSWET1NOSHARED_GROUP_H

#include "UsersTree.h"





class Group:public UsersTreeAbs{
    int groupId;
    int vips;
    bool isVip;
    int * groupViews;
    int * groupViewsTmp;
    void deleteNode(Node * cur){
        cur->right = NULL;
        cur->left = NULL;
        delete cur;
    }


public:

    ~Group(){
        delete[] groupViews;
        delete[] groupViewsTmp;
    }
    const int& getId(){
        return groupId;
    }
    Group(int groupId):groupId(groupId),vips(0),isVip(false){
        try{
            groupViews = new int [GENRES_NUM];
            groupViewsTmp = new int [GENRES_NUM];
            for (int i = 0; i < GENRES_NUM; ++i) {
                groupViews[i]=0;
                groupViewsTmp[i] = 0;
            }
        }
        catch (...)
        {
            throw std::bad_alloc();
        }
    }



    Genre getMostViewedGenre(){
        Genre res = Genre::COMEDY;
        int maxViews = groupViews[0];
        if(groupViews[1]>maxViews)
        {
            maxViews =groupViews[1];
            res = Genre::DRAMA;
        }
        if(groupViews[2]>maxViews)
        {
            maxViews =groupViews[2];
            res = Genre::ACTION;
        }
        if(groupViews[3]>maxViews)
        {
            maxViews =groupViews[3];
            res = Genre::FANTASY;
        }
        return res;
    }

    void add(User* user) override{
        addUser(user);
        Node* newNode = new Node(user);
        head = addNode(head, newNode);
        size++;
        if(user->Vip())
            addVip();
    }

    void remove(const int& userId) override{
        User* user = getData(userId);
        removeUser(user);
        if(user->Vip())
            removeVip();
        head = removeNode(head, userId);
        size--;

    }

    void updateViewsAux(Node* cur){
        if(cur == NULL)
            return;
        cur->data->updateUserViews();
        updateViewsAux(cur->right);
        updateViewsAux(cur->left);
        return;
    }

    void updateViews(){
        updateViewsAux(head);
        for (int i = 0; i < GENRES_NUM; ++i) {
            groupViewsTmp[i] = 0;
        }
    }

    void addUser(User * user){
        updateViews();
        for (int i = 0; i <GENRES_NUM ; ++i) {
            groupViews[i]+=user->getViews(i);
        }
        user->setGroupId(groupId, this);
        user->groupViews = groupViews;
        user->groupViewsTmp = groupViewsTmp;

    }

    void removeUser(User* user){
        updateViews();
        for (int i = 0; i <GENRES_NUM ; ++i) {
            groupViews[i]-=user->getViews(i);
        }
        user->groupViewsTmp = NULL;
        user->groupViews = NULL;
        //remove(user->getId());
        user->setGroupId(0,NULL);
        user = NULL;
    }

    void addVip(){
        vips++;
        isVip = true;
    }
    void removeVip(){
        vips--;
        if(vips <= 0){
            vips = 0;
            isVip = false;
        }
    }
    void watch(Movie* movie) {
        groupViews[int(movie->getGenre())] += size;
        groupViewsTmp[int(movie->getGenre())] += size;
        movie->updateViews(size);
    }
    void clearGroup(Node* cur){
        if(cur == NULL)
            return;
        clearGroup(cur->right);
        clearGroup(cur->left);
        cur->data->groupViews = NULL;
        cur->data->groupViewsTmp = NULL;
        cur->data->setGroupId(0, NULL);
    }

};



#endif //DSWET1NOSHARED_GROUP_H
