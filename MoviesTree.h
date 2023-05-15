//
// Created by yakir on 5/10/2023.
//

#include "Movie.h"
#include "AvlTreeNew.h"

#ifndef DSWET1NOSHARED_MOVIESTREE_H
#define DSWET1NOSHARED_MOVIESTREE_H




class MoviesTree:public AvlTreeNew<Movie*, int>{
    const int& getKey(Node* cur)const override{
        return cur->data->getId();
    }
    void deleteNode(Node * cur){
        cur->right = NULL;
        cur->left = NULL;
        //delete cur->data;
        delete cur;
    }
public:
    virtual~ MoviesTree(){
        deleteDatas(head);
    }

    void deleteDatas(Node * cur){
        if(cur == NULL)
            return;
        delete cur->data;
        deleteDatas(cur->right);
        deleteDatas(cur->left);
    }
};

#endif //DSWET1NOSHARED_MOVIESTREE_H
