//
// Created by yakir on 5/10/2023.
//

#include "Movie.h"
#include "AvlTreeNew.h"

#ifndef DSWET1NOSHARED_MOVIESTREE_H
#define DSWET1NOSHARED_MOVIESTREE_H



class MoviesTreeAbs:public AvlTreeNew<Movie*>{

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

    void deleteNode(Node * cur){
        cur->right = NULL;
        cur->left = NULL;
        delete cur;
    }
};

class MoviesTree:public MoviesTreeAbs{

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
