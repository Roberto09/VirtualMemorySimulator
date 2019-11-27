//
// Created by Diego Alejandro Villarreal López on 26/11/19.
//

#include "FifoQueue.h"

//Constructores

FifoQueue::FifoQueue() {
    this ->queuePages = vector <Page>();
}

Page FifoQueue::front(int number) {
    Page answer;
    int i;
    for(i = 0; i < queuePages.size(); i++){
       if (queuePages.at(i).getIDProcess() != number){
           answer = queuePages[i];
           break;
       }
    }
    // Assuming that every process could fit in real memory this works
    queuePages.erase(queuePages.begin()+i);
    return answer;
}

void FifoQueue:: erase(Page page){
    int i;
    for (i = queuePages.size()-1; i>= 0; i--) {
        if (queuePages.at(i).getIDProcess() == page.getIDProcess()){
            queuePages.erase(queuePages.begin()+i);
        }
    }
}
void FifoQueue:: insert(Page page){
    queuePages.push_back(page);
}