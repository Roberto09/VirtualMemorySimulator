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

const int real_memory_frames = 128;
class RealMemory {
public:
    RealMemory();
    bool insert(Page page, ProcessPaginationTable &paginationTable);
    void erase(Page page, ProcessPaginationTable &paginationTable);
private:
    //List of pages inside of the real memory
    pair<bool,Page> m[real_memory_frames];

};


#endif //VIRTUALMEMORYSIMULATOR_REALMEMORY_H
