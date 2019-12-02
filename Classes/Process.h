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
    /*
     * General process information variables
     */
    int bytes;
    int pages;

    /*
     * Statistic process variables
     */
    double initTimestamp;
    double finishTimestamp;
    int pageFaults;
    bool finished;
public:
    Process();
    Process(int bytes, int pages, double initTimestamp);
    int getPages();
    void addPageFault();
    bool isFinished();
    void finishProcess(double currentTimestamp);
    int getPagesFault();
    double getTurnAround();
};


#endif //VIRTUALMEMORYSIMULATOR_PROCESS_H
