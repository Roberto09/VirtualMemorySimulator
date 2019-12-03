#include <iostream>
#include <fstream>
using namespace std;
#include "Classes/Instruction.h"
#include "Classes/Controller.h"


string nombreArch;
string algorithmToUse;

void askUserData(){
    // Welcome to user and ask for algorithm to use
    cout << "Bienvenido al simulador de memoria viritual!" << endl;
    cout << "Por el momento solo contamos con los algoritmos de remplazo: LRU y FIFO" << endl;
    cout << "Escribe el algoritmo de remplazo que deseas usar e.j. LRU" << endl;

    cin >> algorithmToUse;

    while(algorithmToUse != "LRU" && algorithmToUse != "FIFO"){
        cout << "Lo sentimos, ese no es un algoritmo valido. Por favor ingresa LRU o FIFO" << endl;
        cin >> algorithmToUse;
    }
    cout << "Se usara: " << algorithmToUse << endl;


    // Ask the user for the input file
    cout << "Agrega un archivo al folder de este programa con las instrucciones a simular y dinos su nombre: ";
    cin >> nombreArch;
}


void parseData(){
    // variables needed to parse data, which are queue
    Controller myController;

    // setup controller according to the selected algorithm
    if(algorithmToUse == "LRU"){
        LRUQueue lruQueue;
        myController = Controller(&lruQueue);
    }
    else if(algorithmToUse == "FIFO"){
        FifoQueue fifoQueue;
        myController = Controller(&fifoQueue);
    }

    // open given file
    ifstream inputFile;
    inputFile.open(nombreArch);

    //read data
    string dataS;
    while(getline(inputFile, dataS)){
        // parse the instruction
        Instruction currInstruction(dataS);

        // if there's not an error then we process the instruction
        cout << "INPUT: " << dataS << endl;
        Status statusResult = myController.processInstruction(currInstruction);

        // if there's a failure then we let the user know about it
        if(statusResult.getStatusCode() == s_failure) {
            cout << "Error fatal, se saltara a la siguiente instruccion:" << endl;
            statusResult.outputResult();
            cout << endl << endl << endl;
        }

        // if there's not a failure we output the result of the instruction
        else{
            statusResult.outputResult();
            cout << endl << endl << endl;
            if(currInstruction.getType() == 'E') break;
        }
    }

    string exit;
    cout << "Escriba lo que sea para salir" << endl;
    cin >> exit;

    // close given file
    inputFile.close();
}

int main(){
    // ask the user for basic data to execute the program
    askUserData();

    // parse the instructions given
    parseData();
    return 0;
}