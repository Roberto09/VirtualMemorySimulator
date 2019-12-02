//
// Created by rober on 01/12/2019.
//

#ifndef VIRTUALMEMORYSIMULATOR_PROCESS_H
#define VIRTUALMEMORYSIMULATOR_PROCESS_H

#include <utility>
#include <unordered_map>

using namespace std;

class Process {
private:
    unordered_map<int, pair<bool, int>> paginationTable;
    double initTimestamp;
    int bytes;
    int pages;
public:
    Process();
    Process(int bytes, int pages, double initTimestamp);
    unordered_map<int, pair<bool, int>>& getPaginationTable();
    double getInitTimeStamp();
    int getPages();
};


#endif //VIRTUALMEMORYSIMULATOR_PROCESS_H
