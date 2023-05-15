//
// Created by yakir on 5/10/2023.
//

#ifndef DSWET1NOSHARED_DBOBJ_H
#define DSWET1NOSHARED_DBOBJ_H

#include "AvlTreeNew.h"
#include "wet1util.h"

class NotVip:public std::exception{};
class NotValidId:public std::exception{};
class NotValidInput:public std::exception{};

class DbObj {
int Id;
bool isVip;


public:
    DbObj(int,bool);
    const int& getId()const;
    bool Vip()const;
};





#endif //DSWET1NOSHARED_DBOBJ_H
