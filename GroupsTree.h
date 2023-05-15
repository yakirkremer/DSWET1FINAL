//
// Created by yakir on 5/15/2023.
//

#ifndef DSWET1NOSHARED_GROUPSTREE_H
#define DSWET1NOSHARED_GROUPSTREE_H

#include "Group.h"

class GroupsTree: public AvlTreeNew<Group*,int>{
    const int& getKey(Node* cur)const override{

        return cur->data->getId();
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
        //delete cur->data;
        cur->right = NULL;
        cur->left = NULL;
        delete cur;
    }

public:
    GroupsTree():AvlTreeNew<Group *,int>(){}
    ~GroupsTree(){
        deleteDatas(head);
    }
    void remove(const int& groupId ) override{
        head = removeNode(head, groupId);
        size--;
    }







};

#endif //DSWET1NOSHARED_GROUPSTREE_H
