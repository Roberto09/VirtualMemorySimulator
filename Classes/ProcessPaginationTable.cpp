//
// Created by rober on 26/11/2019.
//

#include "ProcessPaginationTable.h"

ProcessPaginationTable::ProcessPaginationTable() {
    table = unordered_map<int, Process>();
}

void ProcessPaginationTable::createProcess(int pId, int bytes, int pages, double timeStamp) {
    table[pId] = Process(bytes, pages, timeStamp);
}

void ProcessPaginationTable::addRealPosition(Page &page, int position) {
    table[page.getIDProcess()].getPaginationTable()[page.getPageNumber()] = {true, position};
}

int ProcessPaginationTable::getRealPosition(Page &page) {
    return table[page.getIDProcess()].getPaginationTable()[page.getPageNumber()].second;
}

void ProcessPaginationTable::addSecondaryPosition(Page &page, int position) {
    table[page.getIDProcess()].getPaginationTable()[page.getPageNumber()] = {false, position};
}

int ProcessPaginationTable::getSecondaryPosition(Page &page) {
    return table[page.getIDProcess()].getPaginationTable()[page.getPageNumber()].second;
}

void ProcessPaginationTable::removeProcess(int pId) {
    table.erase(pId);
}

bool ProcessPaginationTable::isInRealMemory(Page &page) {
    return table[page.getIDProcess()].getPaginationTable()[page.getPageNumber()].first;
}

bool ProcessPaginationTable::isInSecondaryMemory(Page &page) {
    return !table[page.getIDProcess()].getPaginationTable()[page.getPageNumber()].first;
}

Process& ProcessPaginationTable::getProcess(int pId) {
    return table[pId];
}