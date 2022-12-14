#include <iostream> 
#include <fstream>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <cstdlib>
#include <map>
#include <iomanip>
#include <bitset>

using namespace std;

int main(){ 
    streambuf *save2tst,*origin; 
    ofstream file; 
    file.open("test.txt"); 
    origin=cout.rdbuf(); 
    save2tst=file.rdbuf();

    cout.rdbuf(save2tst);//將cout輸出重定向到文件
    cout << uppercase << hex << 123456 << setw(10) << 123 << endl << "123";

    cout.rdbuf(origin);//恢復cout輸出重定向到終端
    cout << uppercase << hex << 123456 << setw(10) << 123 << endl << "123";
    file.close();
}