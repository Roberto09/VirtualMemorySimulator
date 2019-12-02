#include <iostream>
#include <fstream>
using namespace std;
#include "Classes/Instruction.h"
#include "Classes/Controller.h"


const string nombreArch = "input.txt";


void parseData(){
    FifoQueue fifoQueue;
    Controller myControllerFifo(&fifoQueue);
    LRUQueue lruQueue;
    //Controller myControllerLru(&lruQueue);
    ifstream inputFile;
    inputFile.open(nombreArch);

    bool errorOcurred = false;

    //read data
    string dataS;
    while(getline(inputFile, dataS)){
        Instruction currInstruction(dataS);
        if(errorOcurred){
            if(currInstruction.getType() == 'F') errorOcurred = false, myControllerFifo.resetData();
            else continue;
        }

        cout << "INPUT: " << dataS << endl;
        Status statusResult = myControllerFifo.processInstruction(currInstruction);
        if(statusResult.getStatusCode() == s_failure) {
            cout << "Error fatal:" << endl;
            statusResult.outputResult();
            cout << "El programa esperara hasta la siguiente F para continuar con la siguiente ejecucion";
            cout << endl << endl << endl;
            errorOcurred = true;
        }

        else{
            statusResult.outputResult();
            cout << endl << endl << endl;
            if(currInstruction.getType() == 'E') break;
        }
    }

    inputFile.close();
}

int main(){
    parseData();
    return 0;
}