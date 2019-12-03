//
// Created by rober on 26/11/2019.
//

#include "ProcessPaginationTable.h"

//Constructor
ProcessPaginationTable::ProcessPaginationTable() {
    table = unordered_map<int, unordered_map<int, pair<bool, int>>>();
}
//Adds a page to real position
void ProcessPaginationTable::addRealPosition(Page &page, int position) {
    table[page.getIDProcess()][page.getPageNumber()] = {true, position};
}
//Gets the real position of a page
int ProcessPaginationTable::getRealPosition(Page &page) {
    return table[page.getIDProcess()][page.getPageNumber()].second;
}
//Adds a page to real position
void ProcessPaginationTable::addSecondaryPosition(Page &page, int position) {
    table[page.getIDProcess()][page.getPageNumber()] = {false, position};
}
//Adds a page to swapping position
int ProcessPaginationTable::getSecondaryPosition(Page &page) {
    return table[page.getIDProcess()][page.getPageNumber()].second;
}
// Removes a process
void ProcessPaginationTable::removeProcess(int pId) {
    table.erase(pId);
}
// Checks if a process is in real memory
bool ProcessPaginationTable::isInRealMemory(Page &page) {
    return table[page.getIDProcess()][page.getPageNumber()].first;
}
// Checks if a process is in secondary memory
bool ProcessPaginationTable::isInSecondaryMemory(Page &page) {
    return !table[page.getIDProcess()][page.getPageNumber()].first;
}