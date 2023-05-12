//
// Created by yakir on 5/10/2023.
//

#include "Movie.h"
#include "AvlTreeNew.h"

#ifndef DSWET1NOSHARED_GENREMOVIESTREE_H
#define DSWET1NOSHARED_GENREMOVIESTREE_H


class GenreMoviesTree:public AvlTreeNew<Movie*>{

/*
    bool smallOperatorMovie(Movie* cur, Movie* target){
        return *cur < *target;
    }

    bool leftSmallOperator(Node* cur, Node* target)const override{//if(cur < target.
        return cur->data->getId() < target->data->getId();
    }

    bool leftSmallOperator(Movie* cur, Movie* target)const override{//if(cur < target.
        return cur->getId() < target->getId();
    }

    bool leftSmallOperator( int targetKey,Movie* cur)const override{//if(cur < target.
        return cur->getId() < targetKey;
    }

    bool equalOperator(Node* cur, Node* target)const override{
        return cur->data->getId() == target->data->getId();
    }

    bool equalOperator(Movie* cur, Movie* target){
        return cur->getId() == target->getId();
    }
    */
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
    Movie* highestRated;
    Node* removeNode(Node * cur, Movie* movie){
        if(cur == NULL)
            throw NoNodeExist();

        if(*(cur->data) == *(movie)){//if(ifIs(requestedKey,cur->data)){
            if(cur->right == NULL && cur->left == NULL)
            {
                //delete cur;
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
                cur->setRight( removeNode(cur->right,cur->data));
            }
        }

        else
        {
            if((*movie) < *(cur->data))//if(ifSmaller(requestedKey,cur->data)) //if (requestedKey < (cur->data->getCmp()))
                cur->setLeft(removeNode(cur->left, movie));
            else
                cur->setRight(removeNode(cur->right, movie));
        }

        cur->updateHeight();
        return fixBalance(cur);
    }

    Node* addNode(Node* cur,Node* newNode){

        if(cur == NULL) {
            cur = newNode;
            return cur;
        }

        if(*(cur->data) == *(newNode->data))
            throw alreadyExists();

        if(*(newNode->data) < *(cur->data))
            cur->setLeft(addNode(cur->left, newNode));
        else
            cur->setRight(addNode(cur->right, newNode));

        cur->updateHeight();
        return fixBalance(cur);
    }
    void updateHighest(Node* cur){
        if(cur == NULL) {
            highestRated = NULL;
            return;
        }
        if(cur->right == NULL) {
            highestRated = cur->data;
            return;
        }
        updateHighest(cur->right);
    }


public:

    GenreMoviesTree():AvlTreeNew<Movie *>(),highestRated(NULL){}
    Movie* getHighest(){
        return highestRated;
    }

    void add(Movie* newData) {
         Node* newNode = new Node(newData);
         if(highestRated == NULL)
            highestRated = newData;

        head = addNode(head, newNode);
        size++;
         if(*highestRated < *newData )
             highestRated = newData;
    }
    void remove(Movie* movie) {
        head = removeNode(head, movie);
        updateHighest(head);
        size--;
    }
    void remove(int movie) {
       size--;
    }

    void putDataInOrderAux(int* datas,Node* cur, int* i){
        if(cur == NULL)
            return;
        putDataInOrderAux(datas,cur->left,i);
        datas[*i] = cur->data->getId();
        (*i)++;
        putDataInOrderAux(datas,cur->right,i);


    }
    void putDataInOrder(int * datas){
        if(head == NULL || size == 0)
            throw EmptyTree();
        int * i =new int(0);
        putDataInOrderAux(datas,head,i);
        delete i;
    }
};

#endif //DSWET1NOSHARED_GENREMOVIESTREE_H
