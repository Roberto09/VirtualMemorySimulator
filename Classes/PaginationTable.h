//
// Created by rober on 26/11/2019.
//

#ifndef VIRTUALMEMORYSIMULATOR_PAGINATIONTABLE_H
#define VIRTUALMEMORYSIMULATOR_PAGINATIONTABLE_H
#include <unordered_map>
#include "Page.h"

using namespace std;

class PaginationTable {
private:
    unordered_map<int, unordered_map<int, pair<bool, int>>> table;
public:
    PaginationTable();
    int getRealPosition(Page &page);
    void addRealPosition(Page &page, int position);
    int getSecondaryPosition(Page &page);
    void addSecondaryPosition(Page &page, int position);
    bool isInRealMemory(Page &page);
    void removeProcess(int pId);
};


#endif //VIRTUALMEMORYSIMULATOR_PAGINATIONTABLE_H
