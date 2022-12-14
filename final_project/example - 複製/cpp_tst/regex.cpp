#include <iostream>
#include <fstream>
#include <regex>



using namespace std;

string parse(string line){
    regex reg("//.+");
    regex reg2(" ");
    
    line = regex_replace(line, reg, "");
    line = regex_replace(line, reg2, ""); 

    // if (line == "") return NULL;
    return line;
}

int main(void) {
    string file("sum.asm");
    string line;
    //int count1 = 0;
    
    //parse("@i 132 // sum += i");
    //parse("123");
    // int count2 = 5;
    // cout << "abc" << endl;

    ifstream input_file(file);
    while (getline(input_file, line))
    {
        // cout << line << endl;
        string out = parse(line);
        // cout << out << endl;
        if(out != "")
        //     // cout.width(2) << count1;
            cout<< out << endl;
    }
    input_file.close();


    // 1. 清除註解 用Regex
    // 2. 清除所有空白、空白行
    // 3.  a. 從00開始編號(在line[0]插入"{count}:")，每換行count++
    //     b. 當line == "(LOOP)\n" or line== "(STOP)\n"  -> "(" in line 時
    //        tmp = regex取出 () 裡面的東西，在line最後加上"symbol:{tmp} address={count}"
    //        並且 下一行count--


    return 0;
}

