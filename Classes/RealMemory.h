//
// Created by Pato Saldivar on 11/26/19.
//

#ifndef VIRTUALMEMORYSIMULATOR_REALMEMORY_H
#define VIRTUALMEMORYSIMULATOR_REALMEMORY_H

#include "Page.h"
#include "ProcessPaginationTable.h"
#include <vector>
#include <utility>


using namespace std;

const int len = 128;
class RealMemory {
public:
    RealMemory();
    bool insert(Page page, ProcessPaginationTable &paginationTable);
    void erase(Page page, ProcessPaginationTable &paginationTable);
private:
    pair<bool,Page> m[len];
};


#endif //VIRTUALMEMORYSIMULATOR_REALMEMORY_H
