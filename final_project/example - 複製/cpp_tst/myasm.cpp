#include <stdio.h>
#include <string.h>
#include <iostream>
#include <map>
#include <typeinfo>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

string parse(string line) {
    // 清除多餘空白換行註解

/*
data()與c_str()不同之處在於，c_str函數返回的數組以NULL('\0')結束，data函數但是返回的數組不以空字符終止。
無論是data函數還是c_str函數只能轉換成const char*，如果去掉const編譯不能通過。
解法: 使用copy()
https://blog.csdn.net/piglite/article/details/122985410
*/

    // 用string.c_str() 將string轉成char*
    // 用(char*)把 const char* 轉成 char*
    
    char *codePtr = (char*)line.data(), *codeEnd = (char*)line.data();

    // strchr() 會從 str 字串左側開始搜尋 character 字元，有找到會回傳指向 character 字元的指標，沒找到會回傳 NULL
    while (strchr("\t ", codePtr != NULL)) codePtr++;
    while (*codeEnd != '\0' && strchr("/\n\r", *codeEnd) == NULL) codeEnd++;
    *codeEnd = '\0';
    return codePtr;

}

void pass1(string inFile){
    
    string line;
    ifstream input_file(inFile);

    while (getline(input_file, line))
    {
        // line = parse(line);
        cout << line << endl;
    }

    input_file.close();
}


void assemble(string file) {
    /*
    char inFile[100], hackFile[100], binFile[100];
    sprintf(inFile, "%s.asm", file);
    sprintf(hackFile, "%s.hack", file);
    sprintf(binFile, "%s.bin", file);
    */
    // symDump(&symMap);
    pass1("sum.asm");
    // symDump(&symMap);
    //pass2(inFile, hackFile, binFile);
}

int main(void) {
    //assemble("sum");
    string a = "sum.asm";
    assemble(a);
}