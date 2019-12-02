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
    /*
     * map that maps the process id (int) to it's respective pagination table where every page is represented by it's
     * id and a pair<bool, int> where the boolean represents whether it's in real memory or not and the int represents
     * in which frame in real or secondary memory such page is living.
    */
    unordered_map<int, unordered_map<int, pair<bool, int>>> table;
public:
    ProcessPaginationTable();
    int getRealPosition(Page &page);
    void addRealPosition(Page &page, int position);
    int getSecondaryPosition(Page &page);
    void addSecondaryPosition(Page &page, int position);
    bool isInRealMemory(Page &page);
    bool isInSecondaryMemory(Page &page);
    void removeProcess(int pId);
};


#endif //VIRTUALMEMORYSIMULATOR_PROCESSPAGINATIONTABLE_H
