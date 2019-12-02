//
// Created by rober on 02/12/2019.
//

#include <iostream>
#include "Status.h"


int Status::getStatusCode() {
    return this->statusCode;
}

void Status::outputResult() {
    for (string &s : result)
        cout << s << endl;
}

Status::Status() {
    this->statusCode = s_succes;
    this->result = vector<string>();
}

void Status::setStatusCode(int statusCode) {
    this->statusCode = statusCode;
}

void Status::addStringResult(string s) {
    this->result.push_back(s);
}
