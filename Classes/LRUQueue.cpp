//
// Created by Pato Saldivar on 12/1/19.
//

#include <iostream>
#include "LRUQueue.h"

void LRUQueue::update(Page page) {
    int toErase;
    for(int i=0; i<queuePages.size(); i++){
        if(queuePages[i].getIDProcess() == page.getIDProcess() && queuePages[i].getPageNumber() == page.getPageNumber()){
            toErase = i;
            break;
        }
    }
    queuePages.erase(queuePages.begin()+toErase);
    queuePages.push_back(page);
}