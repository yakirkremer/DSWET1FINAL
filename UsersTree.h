//
// Created by yakir on 5/15/2023.
//
#include "User.h"
#ifndef DSWET1NOSHARED_USERSTREE_H
#define DSWET1NOSHARED_USERSTREE_H

class UsersTreeAbs:public AvlTreeNew<User*,int> {
protected:
    const int& getKey(Node* cur)const override{
        if(cur == NULL)
            return NULL;
        return cur->data->getId();
    }
public:
    UsersTreeAbs():AvlTreeNew<User *,int>(){}


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
        cur->right = NULL;
        cur->left = NULL;
        //delete cur->data;
        delete cur;
    }

public:
    ~UsersTree(){
        deleteDatas(head);
    }

};

#endif //DSWET1NOSHARED_USERSTREE_H
