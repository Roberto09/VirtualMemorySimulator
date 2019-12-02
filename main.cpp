#include <iostream>
#include <fstream>
#include "Classes/Instruction.h"

using namespace std;

const string nombreArch = "input.txt";


void parseData(){
    ifstream inputFile;
    inputFile.open(nombreArch);

    //read data
    string dataS;
    while(getline(inputFile, dataS)){
//        cout << dataS << endl;
        Instruction currInstruction(dataS);
        if (currInstruction.getType() == 'E')
        {
            return;
        }
        else
        {
            // Flag Call the controller processinstruction functino.
        }
    }

    inputFile.close();
}

int main(){
    parseData();
    return 0;
}