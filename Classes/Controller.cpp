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
Controller::Controller(ReplacementQueue *rq) {
    this->rm = RealMemory();
    this->sm = SecondaryMemory();
    this->ppt = ProcessPaginationTable();
    this->currentTime = 0.0;
    this->totalSwapOperations = 0;
    this->rq = rq;
}

/*
 * Swap method that swaps a page from real memory to secondary memory (in order to generate space) according to the
 * replacement queue specified in the contruction.
 */
Page Controller::swap(int pId) {
    // remove page from real memory that doesn't belong to the current process
    Page swapPage = rq->front(pId);
    // add such page to secondary memory
    rm.erase(swapPage, ppt);
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
    rq->insert(page);
    // last but not least we return the result
    return result;
}

/*
 * Create Process method that creates a process in the process history for future reference for statistics.
 */
void Controller::createProcess(int pId, int bytes, int totalPages, double currentTime){
    this->proccessHistory[pId] = Process(bytes, totalPages, currentTime);
}

/*
 * Gets a process from the process history
 */
Process& Controller::getProcess(int pId) {
    return this->proccessHistory[pId];
}

/*
 * Ends a process in process history, used for future statistic references
 */
void Controller::endProcess(int pId) {
    this->proccessHistory[pId].finishProcess(this->currentTime);
}


/*
 * Search process page, searches for a virtual direction in real memory, if it's not found then a swap occurs.
 */
string Controller::searchProcessPage(int virtualDirection, int pId, bool onlyRead) {
    string output = "Obtener la direccion real correspondiente a la direccion virtual " + to_string(virtualDirection) +
                    " del proceso " + to_string(pId) + "\n";
    // create page
    int pageNumber = virtualDirection / page_size;
    Page page(pId, pageNumber);
    // check if page is in secondary memory
    if(this->ppt.isInSecondaryMemory(page)) { // if it isn't then we have to move it to real memory
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
                      to_string(ppt.getSecondaryPosition(swappedPage)) + "del area de swappping \n";
        }

        // we add to the output the real memory direction where the page ended up at
        output += "Se cargo la pagina: " + to_string(page.getPageNumber()) + " del proceso " +
                  to_string(page.getIDProcess()) + " a el marco " + to_string(ppt.getRealPosition(page)) +
                  " de memoria real \n";
    }
    rq->update(page);
    // we add to the output the real direction where our information is now at in real memory
    output += "Direccion virtual: " + to_string(virtualDirection) + ". Direccion Real: " +
              to_string(ppt.getRealPosition(page) * page_size + virtualDirection % page_size) + "\n";
    return output;
}

/*
 * Add process method that adds an entire process to real memory given the process id, the bytes it occupies and the
 * total number of needed pages. If the process can't be added directly to secondary memory then a swap is triggered
 * to secondary memory
 */
string Controller::addProcess(int pId, int bytes, int totalPages) {
    string output = "Asignar " + to_string(bytes) + " bytes al proceso " + to_string(pId) + "\n";
    vector<int> realMemoryFrames; // stores where in real memory the pages of the process ended up.
    vector<Page> swapedPages; // stores the pages that had to be swapped in order to add this process properly.
    // create simple process
    createProcess(pId, bytes, totalPages, this->currentTime);
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

    for(int frame : realMemoryFrames) output += to_string(frame) + ", ";

    output.pop_back(); output.pop_back(); // we remove the last comma added.
    output += "]\n";

    // add to output the information of all the swaps needed
    if(swapedPages.size() > 0){
        output += "Paginas swapeadas a area de swapping: \n";
        //página 5 del proceso 1 swappeada al marco 0 del área de swapping
        for(Page &p : swapedPages){
            output += "Pagina " + to_string(p.getPageNumber()) + " del proceso " + to_string(p.getIDProcess()) +
                      " en memoria real swappeada al marco " + to_string(ppt.getSecondaryPosition(p)) +
                      " del area de swapping \n";
        }
    }

    return output;
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
    this->currentTime = 0.0;
    this->totalSwapOperations = 0;
    this->rq->reset();

}

string Controller::eraseProcess(int pId) {
    string output = "Liberar los marcos de pagina ocupados por el proceso " + to_string(pId) + " \n";
    vector<int> realMemoryFrames, secondaryMemoryFrames;
    Process pcs = getProcess(pId);
    for (int i = 0; i < pcs.getPages(); i++) {
        Page currentPage(pId, i);
        if (ppt.isInRealMemory(currentPage)) {
            realMemoryFrames.push_back(ppt.getRealPosition(currentPage));
            rm.erase(currentPage, ppt);
        } else {
            secondaryMemoryFrames.push_back(ppt.getSecondaryPosition(currentPage));
            sm.erase(currentPage, ppt);
        }
        rq->erase(currentPage);
    }

    if(realMemoryFrames.size() > 0){
        output += "Se libreraron los marcos de pagina de memoria real: [";

        for(int frame : realMemoryFrames) output += to_string(frame) + ", ";

        output.pop_back(); output.pop_back(); // remove last colon from ouput

        output += "] \n";
    }

    if(secondaryMemoryFrames.size() > 0){
        output += "Se libreraron los marcos de pagina del area de swapping: [";

        for(int frame : secondaryMemoryFrames) output += to_string(frame) + ", ";

        output.pop_back(); output.pop_back(); // remove last colon from ouput

        output += "] \n";
    }

    this->ppt.removeProcess(pId);
    endProcess(pId);
    return output;
}

/*
 * This function will be called when the user inputs an F meaning that the program's iteration has
 * ended and the program must show a result of the running statistics.
 * @return output string that will show the report of the program statistics.
 */
string Controller::generateEndReport(){
    string output = "Reporte de Salida: \n"; // Initialize the string that will be used for output.
    output += "Turn around de procesos: \n";

    // Initialize average turn around value
    double averageTurnAround = 0;

    // Calculate average turn around while adding to the ouput the individual turn around of each process
    for(auto it = proccessHistory.begin(); it != proccessHistory.end(); it++) {
        Process &p = it->second;
        if (!p.isFinished()) p.finishProcess(this->currentTime);
        output += "El turn around del proceso " + to_string(it->first) + " es " + to_string(p.getTurnAround()) +
                  " segundos \n";
        averageTurnAround += p.getTurnAround();
    }
    averageTurnAround/=(double)proccessHistory.size();

    // Add to output the page faults per process
    for(auto it = proccessHistory.begin(); it != proccessHistory.end(); it++) {
        Process &p = it->second;
        if (!p.isFinished()) p.finishProcess(this->currentTime);
        output += "Los page faults del proceso " + to_string(it->first) + " son " + to_string(p.getPagesFault()) +
                  "\n";
    }

    // Display the average turnaround time.
    output += "\nAverage Turnaround Time: " + to_string(averageTurnAround) + "\n";

    // Display the number of swap in swap out operations.
    output += "\nNumber of Swap In Swap Out Operations: " + to_string(totalSwapOperations)  + "\n";

    // Reset the data structures so that new inputs are not affected by previous ones.
    resetData();
    return output;
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
            return addProcess(pId, bytes, totalPages);
        }

        case 'A':{ // Search a page from a given process
            int virtualDir = instruction.getData()[0];
            int pId = instruction.getData()[1];
            bool onlyRead = instruction.getData()[2];
            return searchProcessPage(virtualDir,pId , onlyRead);
        }

        case 'L': { //Frees a process in real memory and swapping
            int pId = instruction.getData()[0];
            return eraseProcess(pId);
        }

        case 'C':{ // Create process comment
            return instruction.getComment();
        }

        case 'F':{// End process
            // Generate the report of statistics and reset the variables.
            return generateEndReport();
        }

        case 'E':{ // Exit program
            return "Muchas gracias por utilizar nuestro programa.";
        }
    }
    return "";
}