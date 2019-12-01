//
// Created by rober on 26/11/2019.
//

#include <cmath>
#include "Controller.h"

Controller::Controller() {
    this->rm = RealMemory();
    this->sm = SecondaryMemory();
    this->ppt = ProcessPaginationTable();
    this->currentTime = 0.0;
    this->totalSwapOperations = 0;
}

void Controller::addProcess(int pId, int bytes, int totalPages) {
    // create simple process
    this->ppt.createProcess(pId, bytes, totalPages, this->currentTime);
    // begin transactions, start adding it to real memory
    for(int i = 0; i < totalPages; i++){
        // create page
        Page currPage(pId, i);
        bool realMemoryInsertionResult = this->rm.insert(currPage, this->ppt);
        if(!realMemoryInsertionResult){// there's not enough space in real memory
            // we should swap a page to secondary memory
            Page swapPage = queue.front(pId);
            sm.insert(swapPage, ppt);
            // we insert page again now that there's enough space
            this->rm.insert(currPage, this->ppt);
        }
    }
}

string Controller::processInstruction(Instruction &instruction) {
    switch(instruction.getType()){
        case 'P': // Initial creation of a process
            int bytes = instruction.getData()[0];
            int pId = instruction.getData()[1];

            // calculate total pages needed
            int totalPages = ceil((double)bytes/page_size);

            // add the process
            addProcess(pId, bytes, totalPages);
            break;
        case 'b':
            break;
        case 'c':
            break;
        case 'd':
            break;
        case 'e':
            break;
    }
}