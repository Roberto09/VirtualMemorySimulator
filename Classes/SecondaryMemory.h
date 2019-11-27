//
// Created by Pato Saldivar on 11/26/19.
//

#ifndef VIRTUALMEMORYSIMULATOR_SECONDARYMEMORY_H
#define VIRTUALMEMORYSIMULATOR_SECONDARYMEMORY_H
#include "Page.h"
#include <vector>
#include <utility>
#include "PaginationTable.h"
using namespace std;

const int len = 256;
class SecondaryMemory {
    public:
        SecondaryMemory();
        void insert(Page page, PaginationTable &paginationTable);

    private:
        pair<bool,Page> m[len];
};



#endif //VIRTUALMEMORYSIMULATOR_SECONDARYMEMORY_H
