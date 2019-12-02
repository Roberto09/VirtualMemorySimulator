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
    Controller(ReplacementQueue *rq);
    string processInstruction(Instruction &instruction);
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
    string addProcess(int pId, int bytes, int totalPages);
    string searchProcessPage(int virtualDirection, int pId, bool onlyRead);
    string eraseProcess(int pId);
    string generateEndReport();

    /*
     * Auxiliary methods used by the main methods in order to fulfill their respective tasks.
     */
    Page swap(int pId);
    pair<int, pair<bool, Page>> addToRealMemory(Page &page);
    void createProcess(int pId, int bytes, int totalPages, double currentTime);
    void endProcess(int pId);
    Process& getProcess(int pId);


    void eliminateProcess();
    void endProcessGroup();
    void comment();
    void exitProgram();
    void resetData();
};


#endif //VIRTUALMEMORYSIMULATOR_CONTROLLER_H
