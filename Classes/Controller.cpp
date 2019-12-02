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
Page Controller::swap(int pId) {
    // remove page from real memory that doesn't belong to the current process
    Page swapPage = queue.front(pId);
    // add such page to secondary memory
    sm.insert(swapPage, ppt);
    return swapPage;
}

/*
 * Add to real memory method that tries to add a page to real memory and if it's not possible then it makes a swap
 * and then adds it. While this happens a result is set up which is a pair<int, pair<bool, Page>>.
 * Regarding the result, result.first is the frame in real memory where the page ended up, result.second.first
 * will be true in case a page fault occurred hence result.second.second is the page that was swapped to secondary
 * memory.
 */
pair<int, pair<bool, Page>> Controller::addToRealMemory(Page &page) {
    pair<int, pair<bool, Page>> result = {-1, {false, Page()}};
    bool realMemoryInsertionResult = this->rm.insert(page, this->ppt);
    if(!realMemoryInsertionResult){// there's not enough space in real memory
        // we should swap a page to secondary memory
        Page swapedPage = swap(page.getIDProcess());
        // we insert page again now that there's enough space
        this->rm.insert(page, this->ppt);
        // since a swap occurred we have to add this to the result
        result.second = {true, swapedPage};
    }
    // setup the real memory frame where the page ended up
    result.first = ppt.getRealPosition(page);
    // we finally add it to the queue
    queue.insert(page);
    // last but not least we return the result
    return result;
}

/*
 * Search process page, searches for a virtual direction in real memory, if it's not found then its swaped.
 */
string Controller::searchProcessPage(int virtualDirection, int pId, bool onlyRead) {
    string output = "Obtener la direccion real correspondiente a la direccion virtual " + to_string(virtualDirection) +
            "del proceso " + to_string(pId) + "/n";
    // create page
    int pageNumber = virtualDirection / page_size;
    Page page(pId, pageNumber);
    // check if page is in secondary memory
    if(this->ppt.isInSecondaryMemory(page)) { // if it isn't then we have to it to real memory
        // we add to the output where it's currently in secondary memory
        output += "Se localizo la pagina: " + to_string(page.getPageNumber()) + " del proceso " +
                  to_string(page.getIDProcess()) + " que estaba en el marco " +
                  to_string(ppt.getSecondaryPosition(page)) + " del area de swapping";
        // we remove it form secondary memory
        sm.erase(page, ppt);

        // now we add it to real memory
        pair<int, pair<bool, Page>> result = addToRealMemory(page);

        // if we had to swap something from real memory to secondary memory we add it to the output
        if (result.second.first) {
            Page swappedPage = result.second.second;
            output += "Pagina " + to_string(swappedPage.getPageNumber()) + " swappeada al marco " +
                      to_string(ppt.getSecondaryPosition(swappedPage)) + "del area de swappping /n";
        }

        // we add to the output the real memory direction where the page ended up at
        output += "Se cargo la pagina: " + to_string(page.getPageNumber()) + " del proceso " +
                  to_string(page.getIDProcess()) + " a el marco " + to_string(ppt.getRealPosition(page)) +
                  " de memoria real /n";
    }
    // we add to the output the real direction where our information is now at in real memory
    output += "Direccion virtual: " + to_string(virtualDirection) + ". Direccion Real" +
              to_string(ppt.getRealPosition(page) * page_size + virtualDirection % page_size) + "/n";
    return output;
}

/*
 * Add process method that adds an entire process to real memory given the process id, the bytes it occupies and the
 * total number of needed pages. If the process can't be added directly to secondary memory then a swap is triggered
 * to secondary memory
 */
string Controller::addProcess(int pId, int bytes, int totalPages) {
    string output = "Asignar " + to_string(bytes) + " al proceso " + to_string(pId) + "/n";
    vector<int> realMemoryFrames; // stores where in real memory the pages of the process ended up.
    vector<Page> swapedPages; // stores the pages that had to be swapped in order to add this process properly.
    // create simple process
    this->ppt.createProcess(pId, bytes, totalPages, this->currentTime);
    // begin transactions, start adding it to real memory
    for(int i = 0; i < totalPages; i++){
        // create page
        Page currPage(pId, i);
        // add page to real memory and save the frame where it was added to output it later
        pair<int, pair<bool, Page>> result = addToRealMemory(currPage);
        realMemoryFrames.push_back(result.first);

        if(result.second.first) // if there was a fault then we should add the page swaped for further output
            swapedPages.push_back(result.second.second);
    }

    // add to output all real memory frames
    output += "Se asignaron los marcos de memoria real: [";

    for(int marco : realMemoryFrames) output += to_string(marco) + ", ";

    output.pop_back(); output.pop_back(); // we remove the last comma added.
    output += "]/n";

    // add to output the information of all the swaps needed
    if(swapedPages.size() > 0){
        output += "Paginas swapeadas a area de swapping: /n";
        //página 5 del proceso 1 swappeada al marco 0 del área de swapping
        for(Page &p : swapedPages){
            output += "Pagina " + to_string(p.getPageNumber()) + " del proceso " + to_string(p.getIDProcess()) +
                    " swappeada al marco: " + to_string(ppt.getSecondaryPosition(p)) + "/n";
        }
    }

    return output;
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
string Controller::generateEndReport(){
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

        } break;

        case 'C':{ // create process COMMENT
            return ('C' + instruction.getComment());
        } break;
        // If the instruction is F, generate a report of statistics and reset the variables so that new inputs
        // can be handled without affecting previous proceses.
        case 'F':{// create process FIN

            // Generate the report of statistics and reset the variables.
            return generateEndReport();
        }break;

        case 'E':{ // create process EXI
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