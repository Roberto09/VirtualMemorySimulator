//
// Created by Pato Saldivar on 12/1/19.
//

#include "ReplacementQueue.h"


ReplacementQueue::ReplacementQueue() {
    this ->queuePages = vector <Page>();
}
// Returns the first page from the queue and erases from it
Page ReplacementQueue::front(int pId) {
    Page answer;
    int i;
    for(i = 0; i < queuePages.size(); i++){
        //if (queuePages.at(i).getIDProcess() != pId){
            answer = queuePages[i];
            break;
        //}
    }
    // Assuming that every process could fit in real memory this works
    queuePages.erase(queuePages.begin()+i);
    return answer;
}

//Erases a specific page
void ReplacementQueue:: erase(Page page){
    int i;
    for (i = queuePages.size()-1; i>= 0; i--) {
        if (queuePages.at(i).getIDProcess() == page.getIDProcess()){
            queuePages.erase(queuePages.begin()+i);
        }
    }
}
//Inserts a page to the queue
void ReplacementQueue:: insert(Page page){
    queuePages.push_back(page);
}
//Updates the queue
void ReplacementQueue::update(Page page) {}

//Resets the Queue
void ReplacementQueue:: reset(){
    this ->queuePages = vector <Page>();
}