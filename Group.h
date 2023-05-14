//
// Created by yakir on 5/10/2023.
//

#ifndef DSWET1NOSHARED_GROUP_H
#define DSWET1NOSHARED_GROUP_H

#include "User.h"





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
    int getKey(Node* cur)const override{
        return cur->data->getId();
    }

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
        user->setGroupId(0,NULL);
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
        removeUser(cur->data);
    }

};

class GroupsTree: public AvlTreeNew<Group*>{
    int getKey(Node* cur)const override{
        return cur->data->getId();
    }


    virtual bool leftSmallOperator(Node * cur, Node * other)const override {
        return cur->data->getId() < other->data->getId();
    }
    virtual bool equalOperator(Node * cur, Node * other)const override{
        return cur->data->getId()  == other->data->getId();
    }
    virtual bool leftSmallOperator(int tmpKey, Node * other)const override{
        return tmpKey < other->data->getId();
    }
    virtual bool equalOperator(int tmpKey, Node * other) const override{
        return tmpKey == other->data->getId();
    }


    void deleteDatas(Node * cur){
        if(cur == NULL)
            return;
        delete cur->data;
        deleteDatas(cur->right);
        deleteDatas(cur->left);
    }



    virtual Node* removeNode(Node * cur, int groupId){
        if(cur == NULL)
            throw NoNodeExist();

        if(cur->data->getId() == groupId){
            if(cur->right == NULL && cur->left == NULL)
            {
                deleteNode(cur);
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
                Group* tmpData =cur->data;
                cur->data = minOfRight->data;
                minOfRight->data = tmpData;
                cur->setRight( removeNode(cur->right,groupId));
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

    void deleteNode(Node * cur){
        delete cur->data;
        cur->right = NULL;
        cur->left = NULL;
        delete cur;
    }

public:
    GroupsTree():AvlTreeNew<Group *>(){}
    ~GroupsTree(){
        deleteDatas(head);
    }
    void remove(int groupId ) override{
        head = removeNode(head, groupId);
        size--;
    }







};

#endif //DSWET1NOSHARED_GROUP_H
