//
// Created by Pato Saldivar on 11/26/19.
//

#ifndef VIRTUALMEMORYSIMULATOR_REALMEMORY_H
#define VIRTUALMEMORYSIMULATOR_REALMEMORY_H

#include "Page.h"
#include <vector>
#include <utility>

using namespace std;

const int len = 128;
class RealMemory {
public:
    RealMemory();
    bool Insert(int idPage, int page);
    void Erase(int page);


private:
    pair<bool,Page> m[len];
};


#endif //VIRTUALMEMORYSIMULATOR_REALMEMORY_H
