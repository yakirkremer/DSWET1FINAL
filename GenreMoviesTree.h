//
// Created by yakir on 5/10/2023.
//

#include "MoviesTree.h"

#ifndef DSWET1NOSHARED_GENREMOVIESTREE_H
#define DSWET1NOSHARED_GENREMOVIESTREE_H


class GenreMoviesTree:public MoviesTreeAbs{



    virtual bool leftSmallOperator(Node * cur, Node * other)const override {
        return *(cur->data) < *(other->data);
    }
    virtual bool equalOperator(Node * cur, Node * other)const override{
        return *(cur->data) == *(other->data);
    }


    Movie* highestRated;
    Node* removeNode(Node * cur, Movie* movie){
        if(cur == NULL)
            throw NoNodeExist();

        if(*(cur->data) == *(movie)){//if(ifIs(requestedKey,cur->data)){
            if(cur->right == NULL && cur->left == NULL)
            {
                //delete cur;
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
                Movie* tmpData =cur->data;
                cur->data = minOfRight->data;
                minOfRight->data = tmpData;
                cur->setRight( removeNode(cur->right,movie));
            }
        }

        else
        {
            if((*movie) < *(cur->data))
                cur->setLeft(removeNode(cur->left, movie));
            else
                cur->setRight(removeNode(cur->right, movie));
        }

        cur->updateHeight();
        return fixBalance(cur);
    }

    void updateHighest(Node* cur){
        if(cur->right == NULL) {
            highestRated = cur->data;
            return;
        }
        updateHighest(cur->right);

    }

    void deleteNode(Node * cur){
        cur->right = NULL;
        cur->left = NULL;
        delete cur;
    }

public:

    GenreMoviesTree(): MoviesTreeAbs(),highestRated(NULL){}
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
        if(head == NULL){
            highestRated = NULL;
        }
        else
            updateHighest(head);
        size--;
    }


    void putDataInOrderAux(int* datas,Node* cur, int* i){
        if(cur == NULL)
            return;
        putDataInOrderAux(datas,cur->right,i);
        datas[*i] = cur->data->getId();
        (*i)++;
        putDataInOrderAux(datas,cur->left,i);


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
