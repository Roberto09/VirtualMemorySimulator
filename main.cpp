#include <iostream>
#include <fstream>
using namespace std;
#include "Classes/Instruction.h"
#include "Classes/Controller.h"


const string nombreArch = "input.txt";


void parseData(){
    Controller myControllerFifo(true);
    //Controller myControllerLru(false);
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
            //cout << myControllerLru.processInstruction(currInstruction)<< " LRU" << endl;
            cout << myControllerFifo.processInstruction(currInstruction)<< " Fifo" << endl;
        }
    }

    inputFile.close();
}

int main(){
    parseData();
    cout<<"Si build jejeje xd"<<endl;
    return 0;
}