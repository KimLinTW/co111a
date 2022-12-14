#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <cstdlib>
#include <map>
#include <iomanip>
#include <bitset>


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


bool isNumber(const string& str){
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

void parse1(string line, string& save, int* counter){
    regex reg("//.+");
    regex reg2(" ");
    regex reg3("\\((\\w+)\\)");
    smatch m;
    string sym;
    
    line = regex_replace(line, reg, "");
    line = regex_replace(line, reg2, ""); 
    
    if (regex_search( line, m, reg3)){
        sym = m[1];
        symMap[sym] = *counter; // 記住符號位址，給 pass2 編碼時使用
        // cout << "symMap[" << m2[1] << "] = " << *counter << endl;
    }
    // char* s = const_cast<char*>(line.c_str()); //"std::string" to "char *", regex_match不接受string 所以要先轉成 char *
    // bool isSym = regex_match (s, m, reg3);  // returns true, and m[0] contains "s"
    // if(isSym){
    //     string sym = m[0];
    //     cout << "end: " << (sizeof(sym)) << endl;
    //     cout << "end: " << (sizeof("(LOOP)")) << endl;
    //     cout << "symble: " << sym.substr(1,(sizeof(sym))) << endl; 
    // }
    // symble = regex_match(line);
    if (line != ""){

        cout << setfill('0') << setw(2) << *counter << ":" << line << endl;

        if (line == "(" + sym + ")")
            cout << "symbol:" << sym << " address=" << (*counter)-- << endl;

        (*counter)++;
    }
}


void parse2(string line, string& save, int* counter, streambuf *hack_buf, streambuf *bin_buf, streambuf *origin){
    regex reg("//.+");
    regex reg2(" ");
    regex reg3("\\((\\w+)\\)");
    regex reg4("\\@(\\w+)");
    smatch m;
    string sym;
    
    line = regex_replace(line, reg, "");
    line = regex_replace(line, reg2, ""); 
    
    if (regex_search( line, m, reg3)){
        sym = m[1];
        symMap[sym] = *counter; // 記住符號位址，給 pass2 編碼時使用
        // cout << "symMap[" << m[1] << "] = " << *counter << endl;
        cout << "(" << m[1] << ")" << endl;
    }

    if (line != ""){
        if (!line.find(sym)){
            cout << setfill('0') << setw(2) << hex << uppercase << *counter << ": " << line;
            cout << "  \t\t";
            if (!line.find("@")){
                // A cmd
                if (regex_search(line, m, reg4)){
                    bool isSym = !isNumber(m[1]);
                    if(isSym){
                        if (symMap.find(m[1]) == symMap.end()) symMap[m[1]] = varTop++;
                        // cout -> file
                        // https://huangwang.github.io/2019/12/12/CPlusPlus%E4%B8%ADCout%E8%BE%93%E5%87%BA%E5%88%B0%E6%96%87%E4%BB%B6/
                        cout.rdbuf(hack_buf);
                        cout << setw(16) << setfill('0') << bitset<8>(symMap[m[1]]) << endl;
                        cout.rdbuf(origin);
                        cout << std::nouppercase << ' ' << setw(4) << hex << symMap[m[1]];
                    }else{
                        cout.rdbuf(hack_buf);
                        cout << setw(16) << setfill('0') << bitset<8>(stoi(m[1])) << endl;
                        cout.rdbuf(origin);
                        cout << std::nouppercase << ' ' << setw(4) << hex << stoi(m[1]);
                    }
                }
            }else{
                // C cmd
                string d, js, comp, dcode, ccode, jcode;

                // string::size_type loc = line.find("=",0);
                if (line[1] == '='){
                    string::size_type loc = line.find("=",0);
                    
                    d = line.substr(0, loc);
                    comp = line.substr(loc + 1, (sizeof(line)));
                    dcode = dMap[d];
                    ccode = cMap[comp];

                    // 111 7(dcode) 3(ccode) 000
                    cout.rdbuf(hack_buf);
                    cout << std::dec << 111 << setw(7) << setfill('0') << ccode << setw(3) << setfill('0') << dcode << setw(3) << 0 << endl;
                    cout.rdbuf(origin);

                    cout << std::dec << 111 << setw(7) << setfill('0') << ccode << setw(3) << setfill('0') << dcode << setw(3) << 0;

                    string binary_str("111"+ccode+dcode+"000");
                    bitset<16> set(binary_str);  

                    cout << nouppercase << hex << " " << set.to_ulong();
                }else{
                    string::size_type loc = line.find(";",0);
                    
                    comp = line.substr(0, loc);
                    js = line.substr(loc + 1, (sizeof(line)));
                    ccode = cMap[comp];
                    jcode = jMap[js];

                    // 111 7(dcode) 000 3(jcode)
                    cout.rdbuf(hack_buf);
                    cout << std::dec << 111 << setw(7) << setfill('0') << ccode << setw(3) << setfill('0') << 0 << jcode << endl;
                    cout.rdbuf(origin);

                    string binary_str("111"+ccode+"000"+jcode);
                    bitset<16> set(binary_str);  
                    cout << nouppercase << hex << " " << set.to_ulong();
                }
            }
            cout << endl;
            (*counter)++;
        }
    }
}



void pass1(string inFile, string line, string save, int* counter){
    cout << "============= PASS1 ================" << endl;
    ifstream in;
    in.open(inFile);
    while (getline(in, line))
    {
        parse1(line, save, counter);
    }
}

void pass2(string inFile, string line, string save, int* counter, streambuf *hack_buf, streambuf *bin_buf, streambuf *origin){
    cout << "============= PASS2 ================" << endl;
    ifstream in;
    in.open(inFile);
    while (getline(in, line))
    {
        parse2(line, save, counter, hack_buf, bin_buf, origin);
    }
}

void assemble(string file, int* count2er) {
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
    in.open(inFile);

    ofstream to_hack;
    ofstream to_bin;
    streambuf *hack_buf, *bin_buf, *origin;
    to_hack.open(hackFile, ios::out | ios::trunc); //開啟檔案為輸出狀態，若檔案已存在則清除檔案內容重新寫入
    to_bin.open(binFile, ios::out | ios::trunc); //開啟檔案為輸出狀態，若檔案已存在則清除檔案內容重新寫入
    origin = cout.rdbuf();
    hack_buf = to_hack.rdbuf();
    bin_buf = to_bin.rdbuf();
    
 
    int counter = 0;
    pass1(inFile, line, save, &counter);
    counter = 0;
    pass2(inFile, line, save, &counter, hack_buf, bin_buf, origin);

    in.close();
    to_hack.close();
    to_bin.close();
    

    

    // int abc = 3;
    // cout << abc << endl;

    // cout<< inFile << endl ;
    // cout << hackFile << endl ;
    // cout << binFile << endl;
    // cout << a << endl;
    // cout << binFile << endl;

    // ofstream out_hack;
    // out_hack.open(hackFile);
    // if (out_hack.fail()) cout << "fail";
    // else cout << "write hackFile ok"  << endl;
    // out_hack << "12345678\n\n888";
    // out_hack.close();

    // ifstream inHack;
    // inHack.open(hackFile);
    // if (out_hack.fail()) cout << "fail";
    // else cout << "read hackFile ok"  << endl;
    // string aaaa;
    // inHack >> aaaa;
    // cout << "hackFile:" << aaaa;
    // inHack.close();

    // in.close();

    // out_bin.close();
}

int main(void) {
    int counter = 0;
    string file("sum");
    assemble(file, &counter);
    return 0;
}

