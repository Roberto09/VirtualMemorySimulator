//
// Created by rober on 02/12/2019.
//

#include <iostream>
#include "Status.h"

// Gets the status of the code
int Status::getStatusCode() {
    return this->statusCode;
}
// Prints the result
void Status::outputResult() {
    for (string &s : result)
        cout << s << endl;
}
//Constructor
Status::Status() {
    this->statusCode = s_succes;
    this->result = vector<string>();
}
// Sets the status of the code
void Status::setStatusCode(int statusCode) {
    this->statusCode = statusCode;
}

//Adds a string result
void Status::addStringResult(string s) {
    this->result.push_back(s);
}
