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
    Controller myControllerLru(&lruQueue);
    ifstream inputFile;
    inputFile.open(nombreArch);

    //read data
    string dataS;
    while(getline(inputFile, dataS)){
        Instruction currInstruction(dataS);
        if (currInstruction.getType() == 'E'){
            cout << "E Muchas gracias por utilizar nuestro programa." << endl;
            break;
        }
        else{
            // Call the controller's processInstruction function in order to process every instruction and perform necessary actions..
            cout << "INPUT: " << dataS << endl;
            // Cout << myControllerFifo.processInstruction(currInstruction)<< " Fifo" << endl << endl << endl;
            cout << myControllerLru.processInstruction(currInstruction)<< " LRU" << endl << endl << endl;
        }
    }

    inputFile.close();
}

int main(){
    parseData();
    return 0;
}