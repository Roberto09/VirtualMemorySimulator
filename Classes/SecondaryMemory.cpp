//
// Created by Pato Saldivar on 11/26/19.
//

#include "SecondaryMemory.h"
//Constructor
SecondaryMemory::SecondaryMemory() {}

//Inserts a page in secondary memory
void SecondaryMemory::insert(Page page, ProcessPaginationTable &paginationTable) {
    for(int i=0; i<secondary_memory_frames; i++){
        if(!m[i].first){
            m[i].first = true;
            m[i].second = page;
            paginationTable.addSecondaryPosition(page,i);
            break;
        }
    }

}
//Erases a page in secondary memory
void SecondaryMemory::erase(Page page, ProcessPaginationTable &paginationTable) {
    m[paginationTable.getSecondaryPosition(page)].first = false;
}