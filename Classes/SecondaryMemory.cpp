//
// Created by Pato Saldivar on 11/26/19.
//

#include "SecondaryMemory.h"

SecondaryMemory::SecondaryMemory() {}
void SecondaryMemory::insert(Page page, ProcessPaginationTable &paginationTable) {
    for(int i=0; i<len; i++){
        if(!m[i].first){
            m[i].first = true;
            m[i].second = page;
            paginationTable.addSecondaryPosition(page,i);
            break;
        }
    }

}