//
// Created by Pato Saldivar on 11/26/19.
//

#include "RealMemory.h"
using namespace std;
//Constructor
RealMemory::RealMemory() {};
//Inserts a page to real memory
bool RealMemory::insert(Page page, ProcessPaginationTable &paginationTable) {
    for(int i=0; i<real_memory_frames; i++){
        if(!m[i].first){
            m[i].first= true;
            m[i].second = page;
            paginationTable.addRealPosition(page,i);
            return true;
        }
    }
    return false;
}
// Erase a page from real memory
void RealMemory::erase(Page page, ProcessPaginationTable &paginationTable) {
    m[paginationTable.getRealPosition(page)].first = false;
}


