//
// Created by yakir on 5/10/2023.
//

#include "DbObj.h"

DbObj::DbObj(int id, bool vip) : Id(id),isVip(vip) {
    if(Id <= 0)
        throw NotValidId();
}

int DbObj::getId() const {
    return Id;
}

bool DbObj::Vip() const {
    return isVip;
}
