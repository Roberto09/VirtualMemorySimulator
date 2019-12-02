//
// Created by rober on 26/11/2019.
//

#include <cmath>
#include "Controller.h"

/*
 * Simple constructor for the controller
 */

Controller::Controller() {
    this->rm = RealMemory();
    this->sm = SecondaryMemory();
    this->ppt = ProcessPaginationTable();
    this->currentTime = 0.0;
    this->totalSwapOperations = 0;
}

/*
 * Swap method that swaps a page from real memory to secondary memory
 */
void Controller::swap(int pId) {
    // remove page from real memory that doesn't belong to the current process
    Page swapPage = queue.front(pId);
    // add such page to secondary memory
    sm.insert(swapPage, ppt);
}

/*
 * Add to real memory method that tries to add a page to real memory and if it's not possible then it makes a swap
 * and then adds it.
 */
void Controller::addToRealMemory(Page &page) {
    bool realMemoryInsertionResult = this->rm.insert(page, this->ppt);
    if(!realMemoryInsertionResult){// there's not enough space in real memory
        // we should swap a page to secondary memory
        swap(page.getIDProcess());
        // we insert page again now that there's enough space
        this->rm.insert(page, this->ppt);
    }
}

void Controller::searchProcessPage(int virtualDirection, int pId, bool onlyRead) {
    // create page
    int pageNumber = virtualDirection / page_size;
    Page page(pId, pageNumber);
    // check if page is in secondary memory
    if(this->ppt.isInSecondaryMemory(page)){
        addToRealMemory(page);
    }
}

/*
 * Add process method that adds an entire process to real memory given the process id, the bytes it occupies and the
 * total number of needed pages. If the process can't be added directly to secondary memory then a swap is triggered
 * to secondary memory
 */
void Controller::addProcess(int pId, int bytes, int totalPages) {
    // create simple process
    this->ppt.createProcess(pId, bytes, totalPages, this->currentTime);
    // begin transactions, start adding it to real memory
    for(int i = 0; i < totalPages; i++){
        // create page
        Page currPage(pId, i);
        // add page to real memory
        addToRealMemory(currPage);
    }
}

/*
 * Simple public process delegator which simply identifies the type of instruction given and triggers the corresponding
 * method.
 */
string Controller::processInstruction(Instruction &instruction) {

    switch(instruction.getType()){
        case 'P': { // initial creation of a process
            int bytes = instruction.getData()[0];
            int pId = instruction.getData()[1];

            // calculate total pages needed
            int totalPages = ceil((double) bytes / page_size);

            // add the process
            addProcess(pId, bytes, totalPages);
        }break;
        case 'A':{ // search a page from a given process
            int virtualDir = instruction.getData()[0];
            int pId = instruction.getData()[1];
            bool onlyRead = instruction.getData()[2];
            searchProcessPage(virtualDir,pId , onlyRead);
        }break;
    }
    return "";
}