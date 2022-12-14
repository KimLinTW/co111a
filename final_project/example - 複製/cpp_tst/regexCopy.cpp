#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <cstdlib>
#include <map>



using namespace std;

// vvvvvvvvvvvvvvvvvvv擷取自老師的 co/06/asm.cpp vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

map<string, string> dMap {
  {"", "000"}, {"M", "001"}, {"D", "010"}, {"MD", "011"},
  {"A","100"}, {"AM","101"}, {"AD","110"}, {"AMD","111"}
};

map<string, string> cMap {
  {"0",   "0101010"}, {"1",   "0111111"}, {"-1",  "0111010"},
  {"D",   "0001100"}, {"A",   "0110000"}, {"!D",  "0001101"},
  {"!A",  "0110001"}, {"-D",  "0001111"}, {"-A",  "0110011"},
  {"D+1", "0011111"}, {"A+1", "0110111"}, {"D-1", "0001110"},
  {"A-1", "0110010"}, {"D+A", "0000010"}, {"D-A", "0010011"},
  {"A-D", "0000111"}, {"D&A", "0000000"}, {"D|A", "0010101"},
  {"M",   "1110000"}, {"!M",  "1110001"}, {"-M",  "1110011"},
  {"M+1", "1110111"}, {"M-1", "1110010"}, {"D+M", "1000010"},
  {"D-M", "1010011"}, {"M-D", "1000111"}, {"D&M", "1000000"},
  {"D|M", "1010101"}
};

map<string, string> jMap {
  {"",   "000"}, {"JGT","001"}, {"JEQ","010"}, {"JGE","011"},
  {"JLT","100"}, {"JNE","101"}, {"JLE","110"}, {"JMP","111"}
};

int varTop = 16;

map<string, int> symMap {
  {"R0",0},{"R1",1},{"R2",2},{"R3",3},{"R4",4},{"R5",5},{"R6",6},{"R7",7},
  {"R8",8}, {"R9",9}, {"R10",10}, {"R11",11},{"R12",12}, {"R13",13}, {"R14",14}, {"R15",15},
  {"SCREEN",16384}, {"KBD",24576}, {"SP",0}, {"LCL",0}, {"ARG",2}, {"THIS",3}, {"THAT",4}
};
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void parse(string line, string& save, int* counter){
    regex reg("//.+");
    regex reg2(" ");
    
    line = regex_replace(line, reg, "");
    line = regex_replace(line, reg2, ""); 

    if (line != ""){
        if (*counter < 10)
            cout << "0" << *counter << ":" << line << endl;
        else
            cout << *counter << ":" << line << endl;

        if (line == "(LOOP)"){
            cout << "symbol:LOOP address=" << *counter << endl;
            (*counter)--;
        }

        if (line == "(STOP)"){
            cout << "symbol:STOP address=" << *counter << endl;
            (*counter)--;
        }

        (*counter)++;
    }
}

void assemble(string file, int* counter) {
    string line;
    string save("");

    string inFile(file+".asm");
    string hackFile(file+".hack");
    string binFile(file+".bin");
    string a(file+".");

    cout<< inFile << endl ;
    cout << hackFile << endl ;
    cout << binFile << endl;

    ifstream in;
    // ofstream out_hack;
    // ofstream out_bin;

    in.open(inFile);
    // out_hack.open(hackFile);
    // out_bin.open(binFile);



    // string tst("hack");
    // if (out_hack.fail()) cout << "fail";
    // else cout << "ok";
    // out_hack << tst;
    // out_hack.close();

    cout << "============= PASS1 ================" << endl;
    while (getline(in, line))
    {
        parse(line, save, counter);
    }
    cout << "============= PASS2 ================" << endl;

    int abc = 3;
    cout << abc << endl;

    cout<< inFile << endl ;
    cout << hackFile << endl ;
    cout << binFile << endl;
    cout << a << endl;
    cout << binFile << endl;

    ofstream out_hack;
    out_hack.open(hackFile);
    if (out_hack.fail()) cout << "fail";
    else cout << "write hackFile ok"  << endl;
    out_hack << "12345678\n\n888";
    out_hack.close();

    ifstream inHack;
    inHack.open(hackFile);
    if (out_hack.fail()) cout << "fail";
    else cout << "read hackFile ok"  << endl;
    string aaaa;
    inHack >> aaaa;
    cout << "hackFile:" << aaaa;
    inHack.close();

    in.close();

    // out_bin.close();
}

int main(void) {
    int counter = 0;
    string file("sum");
    assemble(file, &counter);

    
    // 1. 清除註解 用Regex
    // 2. 清除所有空白、空白行
    // 3.  a. 從00開始編號(在line[0]插入"{count}:")，每換行count++
    //     b. 當line == "(LOOP)\n" or line== "(STOP)\n"  -> "(" in line 時
    //        tmp = regex取出 () 裡面的東西，在line最後加上"symbol:{tmp} address={count}"
    //        並且 下一行count--



    return 0;
}

