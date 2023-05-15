//
// Created by yakir on 5/10/2023.
//

#ifndef DSWET1NOSHARED_AVLTREENEW_H
#define DSWET1NOSHARED_AVLTREENEW_H

//
// Created by yakir on 5/8/2023.
//

#ifndef __1_AVLTREENEW_H
#define __1_AVLTREENEW_H

#include <iostream>
#include <iomanip>


class NoNodeExist:public std::exception{};
class alreadyExists:public std::exception{};
class EmptyTree:public std::exception{};

template <class type, class key>
class AvlTreeNew{
protected:
    struct Node{
        type data;
        Node* right;
        Node* left;
        int height;

        virtual ~Node(){
            delete right;
            delete left;
        }
        Node(type data):data(data), right(NULL), left(NULL), height(0) {}

        int max(int a, int b){
            if(a>b)
                return a;
            return b;
        }
        void updateHeight(){
            int rHeight = -1, lHeight = -1;
            if(right != NULL)
                rHeight = right->height;
            if(left != NULL)
                lHeight = left->height;
            height = max(rHeight, lHeight) +1;
        }
        void setLeft(Node* newNode){left = newNode;}
        void setRight(Node* newNode){right = newNode;}
    };
    Node * head;
    int size;

    virtual  const key& getKey(Node * cur)const = 0;
    int getBf(Node* cur){
        int RH = -1, LH = -1;

        if (cur->right != NULL)
            RH = cur->right->height;
        if (cur->left != NULL)
            LH = cur->left->height;
        return LH - RH;
    }
    void copy(Node* cur,Node* other){
        cur->right = other->right;
        cur->left  = other->left;
        cur->data = other->data;
        cur->height = other->height;
        other->left = NULL;
        other->right = NULL;
    }
    Node* findLeftest(Node * cur){
        if(cur->left == NULL)
            return cur;
        return findLeftest(cur->left);
    }
    Node* rotateLL(Node *cur){
        Node* A = cur;
        Node* B = cur->left;
        Node* C = cur->left->left;
        A->setLeft(B->right);
        B->setRight(A);
        A->updateHeight();
        B->updateHeight();
        return B;
    }
    Node* rotateRR(Node *cur){
        Node* A = cur;
        Node* B = cur->right;
        Node* C = cur->right->right;
        A->setRight(B->left);
        B->setLeft(A);
        A->updateHeight();
        B->updateHeight();
        return B;
    }
    Node* rotateLR(Node *cur) {
        cur->setLeft(rotateRR(cur->left))  ;
        return rotateLL(cur);
    }
    Node* rotateRL(Node *cur) {
        cur->setRight(rotateLL(cur->right));
        return rotateRR(cur);
    }
    Node* fixBalance(Node *cur) {
        if (getBf(cur) == 2) {
            if (getBf(cur->left) == -1)
                return rotateLR(cur);
            else
                return rotateLL(cur);
        } else if (getBf(cur) == -2) {
            if (getBf(cur->right) == 1)
                return rotateRL(cur);
            else
                return rotateRR(cur);
        }
        return cur;
    }
    Node *deleteLeftChild(Node* cur){
        Node* leftChild = cur->left;
        copy(cur, leftChild);
        leftChild->right = NULL;
        leftChild->left = NULL;
        delete leftChild;
        leftChild = NULL;
        return cur;
    }
    Node *deleteRightChild(Node* cur){
        Node* rightChild = cur->right;
        copy(cur, rightChild);
        rightChild->right = NULL;
        rightChild->left = NULL;
        delete rightChild;
        rightChild = NULL;
        return cur;
    }


public:
    AvlTreeNew():head(NULL),size(0){}
    virtual ~AvlTreeNew() {
        delete head;
    }
    Node * getHead(){
        return head;
    }
    const int getSize()const{
        return size;
    }
    Node * find(Node *cur, const key& tmpKey)
    {
        if(cur == NULL)
            throw NoNodeExist();
       // if(cur->data->getId() == tmpKey)
       const key& cur1 = getKey(cur);
       const key&cur2 = tmpKey;
       if(getKey(cur) == tmpKey)
            return cur;
        if(cur->right == NULL && cur->left == NULL)
            throw NoNodeExist();
        //if(leftSmallOperator(tmpKey, cur))
        if(tmpKey < getKey(cur))
            return find(cur->left,tmpKey);
        else
            return find(cur->right,tmpKey);
    }
    virtual void deleteNode(Node * cur)=0;

public:
    type getData(int keyToFInd){
        try
        {
            type res = find(head, keyToFInd)->data;
            return res; //find(head,keyToFInd)->data;
        }
        catch (...)
        {
            throw NoNodeExist();
        }
    }
    virtual Node* addNode(Node* cur,Node* newNode)
    {

        if(cur == NULL) {
            cur = newNode;
            return cur;
        }

        //if(equalOperator(cur, newNode))

        if(getKey(cur)== getKey(newNode))
            throw alreadyExists();

        //if(leftSmallOperator(newNode, cur))
        if(getKey(newNode) < getKey(cur))
            cur->setLeft(addNode(cur->left, newNode));
        else
            cur->setRight(addNode(cur->right, newNode));

        cur->updateHeight();
        return fixBalance(cur);
    }
    virtual Node* removeNode(Node * cur, const key& requestedKey){
        if(cur == NULL)
            throw NoNodeExist();

       // if(equalOperator( requestedKey, cur)){//if(ifIs(requestedKey,cur->data)){
       if(requestedKey == getKey(cur)){
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
                key tmpKey = getKey(cur);
                type tmpData =cur->data;
                cur->data = minOfRight->data;
                minOfRight->data = tmpData;
                cur->setRight( removeNode(cur->right,requestedKey));
            }
        }

        else
        {
            //if(leftSmallOperator( requestedKey,cur))//if(ifSmaller(requestedKey,cur->data)) //if (requestedKey < (cur->data->getCmp()))
            if(requestedKey < getKey(cur))
                cur->setLeft(removeNode(cur->left, requestedKey));
            else
                cur->setRight(removeNode(cur->right, requestedKey));
        }

        cur->updateHeight();
        return fixBalance(cur);
    }
    virtual void add(type newData) {
        try {
            Node* newNode = new Node(newData);
            head = addNode(head, newNode);
            size++;
        }
        catch (std::bad_alloc){
            throw std::bad_alloc();
        }

    }
    virtual void remove(const key& requestedKey) {
        head = removeNode(head, requestedKey);
        size--;
    }
};




#endif //__1_AVLTREENEW_H


#endif //DSWET1NOSHARED_AVLTREENEW_H
