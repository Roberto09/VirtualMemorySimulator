//
// Created by rober on 26/11/2019.
//

#ifndef VIRTUALMEMORYSIMULATOR_PROCESSPAGINATIONTABLE_H
#define VIRTUALMEMORYSIMULATOR_PROCESSPAGINATIONTABLE_H
#include <unordered_map>
#include "Page.h"
#include "Process.h"

using namespace std;

class ProcessPaginationTable {
private:
    // map that maps the process id to the process itself which contains it's own pagination table
    unordered_map<int, Process> table;
public:
    ProcessPaginationTable();
    int getRealPosition(Page &page);
    void addRealPosition(Page &page, int position);
    int getSecondaryPosition(Page &page);
    void addSecondaryPosition(Page &page, int position);
    bool isInRealMemory(Page &page);
    bool isInSecondaryMemory(Page &page);
    void createProcess(int pId, int bytes, int pages, double timestamp);
    void removeProcess(int pId);
    Process& getProcess(int pId);
};


#endif //VIRTUALMEMORYSIMULATOR_PROCESSPAGINATIONTABLE_H
