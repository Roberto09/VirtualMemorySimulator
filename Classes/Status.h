//
// Created by rober on 02/12/2019.
//

#ifndef VIRTUALMEMORYSIMULATOR_STATUS_H
#define VIRTUALMEMORYSIMULATOR_STATUS_H

#include <vector>
#include <string>

using namespace std;

const int s_succes = 0, s_failure = 1;
class Status {
private:
    int statusCode;
    vector<string> result;
public:
    Status();
    void outputResult();
    int getStatusCode();
    void setStatusCode(int statusCode);
    void addStringResult(string s);
};

#endif //VIRTUALMEMORYSIMULATOR_STATUS_H
