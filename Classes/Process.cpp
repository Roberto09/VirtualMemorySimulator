//
// Created by rober on 01/12/2019.
//

#include "Process.h"

Process::Process() {}
//Constructor
Process::Process(int bytes, int pages, double initTimestamp) {
    this->bytes = bytes;
    this->pages = pages;
    this->initTimestamp = initTimestamp;
    this->finishTimestamp = 0;
    this->pageFaults = 0;
    this->finished = false;
}

//Gets the number of pages
int Process::getPages() {
    return this->pages;
}
//Adds a page fault
void Process::addPageFault(){
    this->pageFaults ++;
}
// Checks if a process is finished
bool Process::isFinished() {
    return this->finished;
}
//Finishes a process
void Process::finishProcess(double currentTimestamp) {
    this->finished = true;
    this->finishTimestamp = currentTimestamp;
}

//Gets the number of page faults
int Process::getPagesFault() {
    return this->pageFaults;
}
//Gets the turn around
double Process::getTurnAround() {
    return this->finishTimestamp - this->initTimestamp;
}
//Gets the bytes
int Process::getBytes() {
    return this->bytes;
}