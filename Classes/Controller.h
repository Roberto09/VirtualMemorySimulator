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

    double addProcess();
    double searchProcessPage();
    double eliminateProcess();
    double endProcessGroup();
    double comment();
    double exitProgram();
};


#endif //VIRTUALMEMORYSIMULATOR_CONTROLLER_H
