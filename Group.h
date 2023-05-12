//
// Created by yakir on 5/10/2023.
//

#ifndef DSWET1NOSHARED_GROUP_H
#define DSWET1NOSHARED_GROUP_H

#include "User.h"


class UsersTree:public AvlTreeNew<User*>{
protected:
    Node * find(Node *cur, int tmpKey) override
    {
        if(cur == NULL)
            throw NoNodeExist();
        if(cur->data->getId() == tmpKey)//if(tmpKey == (cur->data->getCmp()))
            return cur;
        if(cur->right == NULL && cur->left == NULL)
            throw NoNodeExist();
        if(tmpKey < cur->data->getId())        //if(!ifSmaller( cur->data,tmpKey))//if(tmpKey < (cur->data->getCmp()))
            return find(cur->left,tmpKey);
        else
            return find(cur->right,tmpKey);
    }

    virtual Node* removeNode(Node * cur, int UserId){
        if(cur == NULL)
            throw NoNodeExist();

        if(cur->data->getId() == UserId){
            if(cur->right == NULL && cur->left == NULL)
            {
                delete cur->data;
                cur = NULL;
                return cur;
            }

            else if (cur->right == NULL && cur->left != NULL)
            {
                cur = deleteLeftChild(cur);
            }
            else if (cur->left == NULL && cur->right != NULL)
            {
                cur =  deleteRightChild(cur);
            }
            else if (cur->left != NULL && cur->right != NULL)
            {
                Node* minOfRight = findLeftest(cur->right);
                cur->data = minOfRight->data;
                cur->setRight( removeNode(cur->right,cur->data->getId()));
            }
        }

        else
        {
            if(UserId < cur->data->getId())//if(ifSmaller(requestedKey,cur->data)) //if (requestedKey < (cur->data->getCmp()))
                cur->setLeft(removeNode(cur->left, UserId));
            else
                cur->setRight(removeNode(cur->right, UserId));
        }

        cur->updateHeight();
        return fixBalance(cur);
    }

    Node* addNode(Node* cur,Node* newNode){
        if(cur == NULL) {
            cur = newNode;
            return cur;
        }

        if(cur->data->getId() == newNode->data->getId())
            throw alreadyExists();

        if(newNode->data->getId() < cur->data->getId())
            cur->setLeft(addNode(cur->left, newNode));
        else
            cur->setRight(addNode(cur->right, newNode));

        cur->updateHeight();
        return fixBalance(cur);
    }
    void deleteDatas(Node * cur){
        if(cur==NULL)
            return;




        deleteDatas(cur->right);
        deleteDatas(cur->left);
        delete cur->data;
        cur->data = NULL;
        return;
    }

public:
    UsersTree():AvlTreeNew<User *>(){}
     ~UsersTree(){
        deleteDatas(head);
        //delete head;
    }

    void remove(int UserKey) override{
        head = removeNode(head, UserKey);
        size--;
    }
    void remove(User* UserKey) override{
        size--;
    }

};

class Group:public UsersTree{
    int groupId;
    int vips;
    bool isVip;
    int * groupViews;
    int * groupViewsTmp;

public:

    ~Group(){
        delete[] groupViews;
        delete[] groupViewsTmp;


    }
    int getId(){
        return groupId;
    }
    Group(int groupId):groupId(groupId),vips(0),isVip(false){
        try{
            groupViews = new int [GENRES_NUM];
            groupViewsTmp = new int [GENRES_NUM];
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
    void remove(int userId) override{
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
    }
    void clearGroup(Node* cur){
        if(cur == NULL)
            return;
        clearGroup(cur->right);
        clearGroup(cur->left);
        removeUser(cur->data);
    }

};

class GroupsTree: public AvlTreeNew<Group*>{
    int getKey(Group *dat) override{
        return dat->getId();
    }

    void deleteDatas(Node * cur){
        if(cur == NULL)
            return;
        if(cur != NULL) {
            delete cur->data;
            cur->data = NULL;
        }

        deleteDatas(cur->right);
        deleteDatas(cur->left);
        return;
    }
    Node * find(Node *cur, int tmpKey) override
    {
        if(cur == NULL)
            throw NoNodeExist();
        if(cur->data->getId() == tmpKey)//if(tmpKey == (cur->data->getCmp()))
            return cur;
        if(cur->right == NULL && cur->left == NULL)
            throw NoNodeExist();
        if(tmpKey < cur->data->getId())        //if(!ifSmaller( cur->data,tmpKey))//if(tmpKey < (cur->data->getCmp()))
            return find(cur->left,tmpKey);
        else
            return find(cur->right,tmpKey);
    }


    virtual Node* removeNode(Node * cur, int groupId){
        if(cur == NULL)
            throw NoNodeExist();

        if(cur->data->getId() == groupId){
            if(cur->right == NULL && cur->left == NULL)
            {
                cur = NULL;
                return cur;
            }

            else if (cur->right == NULL && cur->left != NULL)
            {
                cur = deleteLeftChild(cur);
            }
            else if (cur->left == NULL && cur->right != NULL)
            {
                cur =  deleteRightChild(cur);
            }
            else if (cur->left != NULL && cur->right != NULL)
            {
                Node* minOfRight = findLeftest(cur->right);
                cur->data = minOfRight->data;
                cur->setRight( removeNode(cur->right,cur->data->getId()));
            }
        }

        else
        {
            if(groupId < cur->data->getId())//if(ifSmaller(requestedKey,cur->data)) //if (requestedKey < (cur->data->getCmp()))
                cur->setLeft(removeNode(cur->left, groupId));
            else
                cur->setRight(removeNode(cur->right, groupId));
        }

        cur->updateHeight();
        return fixBalance(cur);
    }

    Node* addNode(Node* cur,Node* newNode){
        if(cur == NULL) {
            cur = newNode;
            return cur;
        }

        if(cur->data->getId() == newNode->data->getId())
            throw alreadyExists();

        if(newNode->data->getId() < cur->data->getId())
            cur->setLeft(addNode(cur->left, newNode));
        else
            cur->setRight(addNode(cur->right, newNode));

        cur->updateHeight();
        return fixBalance(cur);
    }

public:
    GroupsTree():AvlTreeNew<Group *>(){}
    ~GroupsTree(){
        deleteDatas(head);
    }
    void remove(int UserKey) override{
        head = removeNode(head, UserKey);
        size--;
    }
    void remove(Group* group) override{
        head = removeNode(head, group->getId());
        size--;
    }






};

#endif //DSWET1NOSHARED_GROUP_H
