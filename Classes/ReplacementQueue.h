//
// Created by Pato Saldivar on 12/1/19.
//

#ifndef VIRTUALMEMORYSIMULATOR_REPLACEMENTQUEUE_H
#define VIRTUALMEMORYSIMULATOR_REPLACEMENTQUEUE_H
#include "Page.h"
#include <vector>
using  namespace std;

class ReplacementQueue {
public:
    ReplacementQueue();
    virtual Page front(int);
    virtual void erase(Page page);
    virtual void insert(Page page);
    virtual void update(Page page);
    virtual void reset();

protected:
    vector <Page> queuePages;
};



#endif //VIRTUALMEMORYSIMULATOR_REPLACEMENTQUEUE_H
