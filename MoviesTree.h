//
// Created by yakir on 5/10/2023.
//

#include "Movie.h"
#include "AvlTreeNew.h"

#ifndef DSWET1NOSHARED_MOVIESTREE_H
#define DSWET1NOSHARED_MOVIESTREE_H

class MoviesTree:public AvlTreeNew<Movie*>{

    void deleteDatas(Node * cur){
        if(cur==NULL)
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

    virtual Node* removeNode(Node * cur, int requestedKey){
        if(cur == NULL)
            throw NoNodeExist();

        if(cur->data->getId() == requestedKey){
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
            if(requestedKey < cur->data->getId())//if(ifSmaller(requestedKey,cur->data)) //if (requestedKey < (cur->data->getCmp()))
                cur->setLeft(removeNode(cur->left, requestedKey));
            else
                cur->setRight(removeNode(cur->right, requestedKey));
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
    MoviesTree():AvlTreeNew<Movie *>(){}
    virtual ~MoviesTree(){
        deleteDatas(head);
        //delete head;
    }
    void remove(int movieKey) override{
        head = removeNode(head, movieKey);
        size--;
    }
    void remove(Movie* movieKey) override{
        //head = removeNode(head, movieKey);
        size--;
    }


};


#endif //DSWET1NOSHARED_MOVIESTREE_H
