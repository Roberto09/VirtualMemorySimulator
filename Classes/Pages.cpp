//
// Created by Diego Alejandro Villarreal López on 26/11/19.
//

#include "Pages.h"

//Constructor
Pages ::Pages() {

}

int Pages::getIDProcess() {
    return idProcess;
}
int Pages::getPageNumber() {
    return pageNumber;
}
void Pages ::setIDProcess(int idProcess) {
    this -> idProcess = idProcess;
}
void Pages ::setPageNumber(int pageNumber) {
    this -> pageNumber = pageNumber;
}