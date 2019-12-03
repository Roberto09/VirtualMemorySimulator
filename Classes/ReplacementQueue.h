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
     Page front(int);
     void erase(Page page);
     void insert(Page page);
    virtual void update(Page page);
     void reset();

protected:
    //Queue of pages
    vector <Page> queuePages;

};



#endif //VIRTUALMEMORYSIMULATOR_REPLACEMENTQUEUE_H
