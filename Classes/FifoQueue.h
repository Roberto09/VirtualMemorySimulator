//
// Created by Diego Alejandro Villarreal López on 26/11/19.
//

#ifndef VIRTUALMEMORYSIMULATOR_FIFOQUEUE_H
#define VIRTUALMEMORYSIMULATOR_FIFOQUEUE_H
#include "Page.h"
#include <vector>
using  namespace std;


class FifoQueue {
public:
    FifoQueue();
    Page front(int);
    void erase(Page page);
    void insert(Page page);

private:
    vector <Page> queuePages;
};


#endif //VIRTUALMEMORYSIMULATOR_FIFOQUEUE_H
