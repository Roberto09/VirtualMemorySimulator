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
        //cout << dataS << etr;
        Instruction currInstruction(dataS);
    }

    inputFile.close();
}

int main(){
    parseData();
    cout<<"Si build jejeje xd"<<endl;
    return 0;
}