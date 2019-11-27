//
// Created by Pato Saldivar on 11/26/19.
//

#include "RealMemory.h"
#include "Page.cpp"
#include "PaginationTable.cpp"
using namespace std;
//Constructor
RealMemory::RealMemory() {};

bool RealMemory::insert(Page page, PaginationTable &paginationTable) {
    for(int i=0; i<len; i++){
        if(!m[i].first){
            m[i].first= true;
            m[i].second = page;
            paginationTable.addRealPosition(page,i);
            return true;
        }
    }
    return false;
}

void RealMemory::erase(Page page, PaginationTable &paginationTable) {
    m[paginationTable.getRealPosition(page)].first = false;
}

