#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#define GPIO_PATH "/sys/class/gpio/gpio"

// mutators
string choosePin(string pin){  // 60 & 46 called
    ostringstream s;
    s << GPIO_PATH << pin << "/";
    return s.str();
}

int write(string path, string filename, string value){
    ofstream fs;        // output
    fs.open((path + filename).c_str());
    if (!fs.is_open()){
        perror("GPIO: write failed to open file");
        return -1;
    }
    fs << value;
    fs.close();
    return 0;
}

string read(string path, string filename){
    ifstream fs;        // input
    fs.open((path + filename).c_str());
    if (!fs.is_open()){
        perror("GPIO: read failed to open file");
     }
    string input;
    getline(fs,input);
    fs.close();
    return input;
}

void setDirection(string path, string dir){
    if (dir == "in"){
        write(path,"direction","in");
    }
    else if (dir == "out"){
        write(path,"direction","out");
    }
}

// Accessors
int getValue(string path){
    string input = read(path,"value");
    if (input == "0") return 0;
    else return 1;
}

int main(int argc, char* argv[]){
    if (argc != 4){
        cout << "1st arg is output pin " << endl;
        cout << "2nd arg is state -> hi, low " << endl;
        cout << "3rd arg is input pin " << endl;
    }

    string outGPIO(argv[1]);
    string outPATH = choosePin(outGPIO);

    string stateGPIO(argv[2]);

    string inGPIO(argv[3]);
    string inPATH = choosePin(inGPIO);

    setDirection(outGPIO, "out");
    setDirection(inGPIO, "in");
    
    if (stateGPIO == "hi"){
        write(outGPIO,"value","1");   
    }
    else if (stateGPIO == "low"){
        write(outGPIO,"value","0");
    }
    else {
        return -1;
    }

    cout << "GPIO input" << inGPIO << " value is " << getValue(inPATH) << endl;
    cout << "GPIO output" << outGPIO << " value is " << getValue(outPATH) << endl;
    

    return 0;
}
