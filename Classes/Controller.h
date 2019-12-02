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

using namespace std;

const double d_load_page_memory = 1.0, d_swap_in = 1.0, d_swap_out = 1.0;
const int page_size = 16;

class Controller {
public:
    Controller(ReplacementQueue *rq); //If b is true it is fifo, else it is LRU
    string processInstruction(Instruction &instruction);
private:
    // Real memory, secondary memory, pagination table and queue
    RealMemory rm;
    SecondaryMemory sm;
    ProcessPaginationTable ppt;
    ReplacementQueue *rq;


    // Statistic variables, used mainly to compute final statistics: turn around for each process, average turn around,
    // total page faults and total swap-in, swap-out operations.
    double currentTime;
    int totalSwapOperations;

    string addProcess(int pId, int bytes, int totalPages);
    Page swap(int pId);
    pair<int, pair<bool, Page>> addToRealMemory(Page &page);
    string searchProcessPage(int virtualDirection, int pId, bool onlyRead);
    void eliminateProcess();
    void endProcessGroup();
    void comment();
    void exitProgram();
    string eraseProcess(int pId);

    string generateEndReport();
    void resetData();

    double calculateTurnaroundTime();

    double calculateTurnaroundAverageTime();

    double calculateNumPageFaults();

    double calculateNumOperations();
};


#endif //VIRTUALMEMORYSIMULATOR_CONTROLLER_H
