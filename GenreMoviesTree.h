//
// Created by yakir on 5/10/2023.
//

#include "AvlTreeNew.h"

#ifndef DSWET1NOSHARED_GENREMOVIESTREE_H
#define DSWET1NOSHARED_GENREMOVIESTREE_H


class GenreMoviesTree:public AvlTreeNew<Movie*, MovieKey>{
    Movie* highestRated;
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

     const MovieKey& getKey(Node* cur)const override{
         return cur->data->getCmp();
    }
    void putDataInOrderAux(int* datas,Node* cur, int* i){
        if(cur == NULL)
            return;
        putDataInOrderAux(datas,cur->right,i);
        datas[*i] = cur->data->getId();
        (*i)++;
        putDataInOrderAux(datas,cur->left,i);


    }

public:

    GenreMoviesTree(): AvlTreeNew<Movie *, MovieKey>(),highestRated(NULL){}
    Movie* getHighest(){
        return highestRated;
    }

    void add(Movie* newData) {
         Node* newNode = new Node(newData);
         if(highestRated == NULL)
            highestRated = newData;

        head = addNode(head, newNode);
        size++;
         if(highestRated->getCmp() < newData->getCmp() )
             highestRated = newData;
    }
    void remove(Movie* movie) {
        //head = removeNode(head, movie);
        head = removeNode(head, movie->getCmp());
        if(head == NULL){
            highestRated = NULL;
        }
        else
            updateHighest(head);
        size--;
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
