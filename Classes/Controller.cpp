//
// Created by rober on 26/11/2019.
//

#include "Controller.h"

Controller::Controller() {
    this->rm = RealMemory();
    this->sm = SecondaryMemory();
    this->ppt = ProcessPaginationTable();
    this->currentTime = 0.0;
    this->totalSwapOperations = 0;
}

string Controller::processInstruction(Instruction &instruction) {

}