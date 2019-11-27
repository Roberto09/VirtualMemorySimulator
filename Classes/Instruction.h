//
// Created by rober on 26/11/2019.
//

#ifndef VIRTUALMEMORYSIMULATOR_INSTRUCTION_H
#define VIRTUALMEMORYSIMULATOR_INSTRUCTION_H

#include <vector>
#include <string>

using namespace std;

class Instruction {
private:
    char type;
    vector<int> data;
    string comment;
public:
    Instruction();
    Instruction(string &parseString);
};

#endif //VIRTUALMEMORYSIMULATOR_INSTRUCTION_H
