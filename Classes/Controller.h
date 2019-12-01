//
// Created by rober on 26/11/2019.
//

#ifndef VIRTUALMEMORYSIMULATOR_CONTROLLER_H
#define VIRTUALMEMORYSIMULATOR_CONTROLLER_H

#include "Instruction.h"
#include "RealMemory.h"
#include "SecondaryMemory.h"
#include "FifoQueue.h"

using namespace std;

const double d_load_page_memory = 1.0, d_swap_in = 1.0, d_swap_out = 1.0;
const int page_size = 16;

class Controller {
public:
    Controller();
    string processInstruction(Instruction &instruction);
private:
    // Real memory, secondary memory, pagination table and queue
    RealMemory rm;
    SecondaryMemory sm;
    ProcessPaginationTable ppt;
    FifoQueue queue;

    // Statistic variables, used mainly to compute final statistics: turn around for each process, average turn around,
    // total page faults and total swap-in, swap-out operations.
    double currentTime;
    int totalSwapOperations;

    void addProcess(int pId, int bytes, int totalPages);
    void swap(int pId);
    void searchProcessPage();
    void eliminateProcess();
    void endProcessGroup();
    void comment();
    void exitProgram();
};


#endif //VIRTUALMEMORYSIMULATOR_CONTROLLER_H
