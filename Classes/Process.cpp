//
// Created by rober on 01/12/2019.
//

#include "Process.h"

Process::Process() {}

Process::Process(int bytes, int pages, double initTimestamp) {
    this->bytes = bytes;
    this->pages = pages;
    this->initTimestamp = initTimestamp;
    this->finishTimestamp = 0;
    this->pageFaults = 0;
    this->finished = false;
}

int Process::getPages() {
    return this->pages;
}

void Process::addPageFault(){
    this->pageFaults ++;
}

bool Process::isFinished() {
    return this->finished;
}

void Process::finishProcess(double currentTimestamp) {
    this->finished = true;
    this->finishTimestamp = currentTimestamp;
}

int Process::getPagesFault() {
    return this->pageFaults;
}

double Process::getTurnAround() {
    return this->finishTimestamp - this->initTimestamp;
}

int Process::getBytes() {
    return this->bytes;
}