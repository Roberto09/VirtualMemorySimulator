//
// Created by rober on 26/11/2019.
//

#ifndef VIRTUALMEMORYSIMULATOR_INSTRUCTION_H
#define VIRTUALMEMORYSIMULATOR_INSTRUCTION_H

#include <vector>
#include <string>

using namespace std;
//This class is for having better control of instructions
class Instruction {
private:
    char type; // the type of instruction to do
    vector<int> data; // the data recived
    string comment; // Any special comment recieved
public:
    Instruction();
    Instruction(string &parseString);
    char getType();
    vector<int>& getData();
    string& getComment();
};

#endif //VIRTUALMEMORYSIMULATOR_INSTRUCTION_H
