//
// Created by Diego Alejandro Villarreal López on 26/11/19.
//

#include "Page.h"

//Constructor
Page ::Page() {}

Page ::Page(int idProcess, int pageNumber) {
    this->idProcess = idProcess;
    this->pageNumber = pageNumber;
}

int Page::getIDProcess() {
    return idProcess;
}
int Page::getPageNumber() {
    return pageNumber;
}
void Page ::setIDProcess(int idProcess) {
    this -> idProcess = idProcess;
}
void Page ::setPageNumber(int pageNumber) {
    this -> pageNumber = pageNumber;
}