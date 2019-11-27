//
// Created by rober on 26/11/2019.
//

#include "PaginationTable.h"

int PaginationTable::addRealPosition(Page &page, int position) {
    table[page.getIDProcess()][page.getPageNumber()] = {true, position};
}

int PaginationTable::getRealPosition(Page &page) {
    return table[page.getIDProcess()][page.getPageNumber()].second;
}

void PaginationTable::removeProcess(int pId) {
    table.erase(pId);
}

PaginationTable::PaginationTable() {
    table = unordered_map<int, unordered_map<int, pair<bool, int>>>();
}