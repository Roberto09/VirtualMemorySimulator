//
// Created by Pato Saldivar on 12/1/19.
//

#include "LRUQueue.h"

void LRUQueue::update(Page page) {
    for(int i=0; i<queuePages.size(); i++){
        if(queuePages[i].getIDProcess()==page.getIDProcess()){
            queuePages.erase(queuePages.begin()+i);
            queuePages.push_back(page);
            break;
        }
    }
}