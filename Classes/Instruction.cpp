//
// Created by rober on 26/11/2019.
//

#include "Instruction.h"

Instruction::Instruction() {}

Instruction::Instruction(string &parseString) {
    this->type = parseString[0];
    int iPos = 2;
    int niPos;
    while(iPos < parseString.length() && parseString[iPos] >= '0' && parseString[iPos] <= '9'){
        niPos = parseString.find(' ', iPos);
        niPos = (niPos == string::npos ? parseString.length() : niPos);
        this->data.push_back(stol(parseString.substr(iPos, niPos)));
        iPos = niPos+1;
    }

    if(iPos < parseString.length()) this->comment = parseString.substr(iPos);
}
