//
// Created by rober on 26/11/2019.
//

#include <cmath>
#include <iostream>
#include "Controller.h"
using namespace std;

/*
 * Simple constructor for the controller
 */

Controller::Controller() {
    this->rm = RealMemory();
    this->sm = SecondaryMemory();
    this->ppt = ProcessPaginationTable();
    this->currentTime = 0.0;
    this->totalSwapOperations = 0;
    this->queue = FifoQueue();
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
    // we finally add it to the queue
    queue.insert(page);
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
 * Calculate the turnaround time which is the time calculated when a process is loaded until the process is terminated
 * and all of the pages (L) are freed. This can be calculated with a difference in timestamps.
 * This function will be used by the generateEndReport() function for showing the turnaround time in the output of the F input command.
 */
double Controller::calculateTurnaroundTime() {
    double dTurnAround = 0;
    // Flag: Insert calculation here.
    return dTurnAround;
}

/*
 * Calculate the turnaround AVERAGE time which is the time calculated when a process is loaded until the process is terminated
 * and all of the pages (L) are freed. This can be calculated with a difference in timestamps.
 * This function will be used by the generateEndReport() function for showing the AVERAGE turnaround time in the output of the F input command.
 */
double Controller::calculateTurnaroundAverageTime() {
    double dTurnAroundAvg = 0;
    // Flag: Insert calculation here.
    return dTurnAroundAvg;
}

/*
 * Calculate the number of page faults per process. A page fault occurs when a page frame needed is not in real memory.
 * This function will be used by the generateEndReport() function for showing the # of page faults per process.
 */
double Controller::calculateNumPageFaults(){
    double dPageFaults = 0;
    // Flag: Insert calculation here.
    return dPageFaults;
}

/*
 * Calculate The number of swap in swap out operations.
 * This function will be used by the generateEndReport() function for showing the # of page faults per process.
 */
double Controller::calculateNumOperations() {
    double dNumOperations = 0;
    // Flag: Insert calculation here.
    return dNumOperations;
}


/*
 * This method will be called by generateEndReport() in order to reset the
 * data structures previously initialized. This will allow the user to enter other inputs.
 */
void Controller::resetData()
{
    // Re-initialize private variables.
    this->rm = RealMemory();
    this->sm = SecondaryMemory();
    this->ppt = ProcessPaginationTable();
    this->queue = FifoQueue();
    this->currentTime = 0.0;
    this->totalSwapOperations = 0;

}

/*
 * This function will be called when the user inputs an F meaning that the program's iteration has
 * ended and the program must show a result of the running statistics.
 * @return output string that will show the report of the program statistics.
 */
string Controller::generateEndReport()
{
    string sOutput = ""; // Initialize the string that will be used for output.
    sOutput += "F\nFin. Reporte de Salida:";

    // Display the turnaround time.
    sOutput += "\nTurnaround Time: " + to_string(calculateTurnaroundTime());

    // Display the average turnaround time.
    sOutput += "\nAverage Turnaround Time: " + to_string(calculateTurnaroundAverageTime());

    // Display the number of page faults.
    sOutput += "\nNumber of Page Faults: " + to_string(calculateNumPageFaults());

    // Display the number of swap in swap out operations.
    sOutput += "\nNumber of Swap In Swap Out Operations: " + to_string(calculateNumOperations());

    // Reset the data structures so that new inputs are not affected by previous ones.
    resetData();
    return sOutput;

}

/*
 * Simple public process delegator which simply identifies the type of instruction given and triggers the corresponding
 * method.
 */
string Controller::processInstruction(Instruction &instruction) {

    switch(instruction.getType()) {
        case 'P': { // Initial creation of a process
            int bytes = instruction.getData()[0];
            int pId = instruction.getData()[1];

            // calculate total pages needed
            int totalPages = ceil((double) bytes / page_size);

            // add the process
            addProcess(pId, bytes, totalPages);
            // Flag: need to add return statement for the output.
            return "P";
        }
        // If the instruction is a comment print the comment.
        case 'C': // create process COMMENT
        {
            return ('C' + instruction.getComment());
        }
        // If the instruction is F, generate a report of statistics and reset the variables so that new inputs
        // can be handled without affecting previous proceses.
        case 'F': // create process FIN
        {
            // Generate the report of statistics and reset the variables.
            return generateEndReport();
        }
        // If the instruction is E end the program and exit the execution.
        case 'E': // create process EXIT
        {
            return ("E Muchas gracias por utilizar nuestro programa.");
        }break;
        case 'A':{ // search a page from a given process
            int virtualDir = instruction.getData()[0];
            int pId = instruction.getData()[1];
            bool onlyRead = instruction.getData()[2];
            searchProcessPage(virtualDir,pId , onlyRead);
        }break;
        case 'L': {//Frees a process in real memory and swapping
            int pId = instruction.getData()[0];
            Process pcs = ppt.getProcess(pId);
            for (int i = 0; i < pcs.getPages(); i++) {
                Page currentPage(pId, i);
                if (ppt.isInRealMemory(currentPage)) {
                    rm.erase(currentPage, ppt);
                } else {
                    sm.erase(currentPage, ppt);
                }
                queue.erase(currentPage);
                //Falta LRU
            }
            ppt.removeProcess(pId);
        }break;

    }
    return "";
}