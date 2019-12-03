//
// Created by rober on 26/11/2019.
//

#ifndef VIRTUALMEMORYSIMULATOR_CONTROLLER_H
#define VIRTUALMEMORYSIMULATOR_CONTROLLER_H

#include "Instruction.h"
#include "RealMemory.h"
#include "SecondaryMemory.h"
#include "ReplacementQueue.h"
#include "FifoQueue.h"
#include "LRUQueue.h"
#include "Status.h"

using namespace std;

const double d_load_page_memory_initially = 1.0, d_swap = 1.0, d_access_page_in_real_memory = 0.1,
d_free_page_real_memory = 0.1, d_free_page_secondary_memory = 0.1;
const int page_size = 16;

class Controller {
public:
    Controller(ReplacementQueue *rq);
    Status processInstruction(Instruction &instruction);
    void resetData();
private:
    /*
     * Main variables, used to coordinate the transactions regarding the processes.
     */
    RealMemory rm;
    SecondaryMemory sm;
    ProcessPaginationTable ppt;
    ReplacementQueue *rq;

    /*
     * Statistic variables, used mainly to compute final statistics: turn around for each process, average turn around,
     * total page faults and total swap-in, swap-out operations.
     */
    unordered_map<int, Process> proccessHistory;
    double currentTime;
    int totalSwapOperations;

    /*
     * Main methods used by the controller, this are the onces being called directly with the data of the instruction.
     */
    Status addProcess(int pId, int bytes, int totalPages);
    Status searchProcessPage(int virtualDirection, int pId, bool onlyRead);
    Status eraseProcess(int pId);
    Status generateEndReport();

    /*
     * Auxiliary methods used by the main methods in order to fulfill their respective tasks.
     */
    Page swap(int pId);
    pair<int, pair<bool, Page>> addToRealMemory(Page &page);
    void createProcess(int pId, int bytes, int totalPages, double currentTime);
    void endProcess(int pId);
    Process& getProcess(int pId);
    bool processExists(int pId);
};


#endif //VIRTUALMEMORYSIMULATOR_CONTROLLER_H
