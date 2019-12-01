//
// Created by rober on 01/12/2019.
//

#include "Process.h"

Process::Process() {}

Process::Process(double initTimestamp) {
    this->initTimestamp = initTimestamp;
}

unordered_map<int, pair<bool, int>>& Process::getPaginationTable() {
    return this->paginationTable;
}

double Process::getInitTimeStamp() {
    return this->initTimestamp;
}