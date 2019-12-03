//
// Created by Diego Alejandro Villarreal López on 26/11/19.
//

#ifndef VIRTUALMEMORYSIMULATOR_FIFOQUEUE_H
#define VIRTUALMEMORYSIMULATOR_FIFOQUEUE_H
#include "Page.h"
#include <vector>
#include "ReplacementQueue.h"
using  namespace std;


//This class is for to specify the fifo replacement method. It applies poliformism from Replacement Queue
class FifoQueue: public ReplacementQueue {
public:
};


#endif //VIRTUALMEMORYSIMULATOR_FIFOQUEUE_H
