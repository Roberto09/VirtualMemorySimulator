//
// Created by rober on 26/11/2019.
//

#include "ProcessPaginationTable.h"

ProcessPaginationTable::ProcessPaginationTable() {
    table = unordered_map<int, unordered_map<int, pair<bool, int>>>();
}

void ProcessPaginationTable::addRealPosition(Page &page, int position) {
    table[page.getIDProcess()][page.getPageNumber()] = {true, position};
}

int ProcessPaginationTable::getRealPosition(Page &page) {
    return table[page.getIDProcess()][page.getPageNumber()].second;
}

void ProcessPaginationTable::addSecondaryPosition(Page &page, int position) {
    table[page.getIDProcess()][page.getPageNumber()] = {false, position};
}

int ProcessPaginationTable::getSecondaryPosition(Page &page) {
    return table[page.getIDProcess()][page.getPageNumber()].second;
}

void ProcessPaginationTable::removeProcess(int pId) {
    table.erase(pId);
}

bool ProcessPaginationTable::isInRealMemory(Page &page) {
    return table[page.getIDProcess()][page.getPageNumber()].first;
}

bool ProcessPaginationTable::isInSecondaryMemory(Page &page) {
    return !table[page.getIDProcess()][page.getPageNumber()].first;
}