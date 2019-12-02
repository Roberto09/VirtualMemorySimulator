//
// Created by Pato Saldivar on 11/26/19.
//

#ifndef VIRTUALMEMORYSIMULATOR_SECONDARYMEMORY_H
#define VIRTUALMEMORYSIMULATOR_SECONDARYMEMORY_H
#include "Page.h"
#include <vector>
#include <utility>
#include "ProcessPaginationTable.h"
using namespace std;

const int total_frames = 256;
class SecondaryMemory {
    public:
        SecondaryMemory();
        void insert(Page page, ProcessPaginationTable &paginationTable);
        void erase(Page page, ProcessPaginationTable &paginationTable);

    private:
        pair<bool,Page> m[total_frames];
};



#endif //VIRTUALMEMORYSIMULATOR_SECONDARYMEMORY_H
