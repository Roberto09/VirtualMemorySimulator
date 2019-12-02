//
// Created by Pato Saldivar on 12/1/19.
//

#ifndef VIRTUALMEMORYSIMULATOR_LRUQUEUE_H
#define VIRTUALMEMORYSIMULATOR_LRUQUEUE_H
#include "ReplacementQueue.h"
using namespace std;
class LRUQueue: public ReplacementQueue {
public:
    void update(Page page);
};


#endif //VIRTUALMEMORYSIMULATOR_LRUQUEUE_H
