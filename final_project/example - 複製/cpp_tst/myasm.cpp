#include <stdio.h>
#include <string.h>
#include <iostream>
#include <map>
#include <typeinfo>
#include <string>
#include <fstream>
#include <vector>
#include <regex>

using namespace std;

string parse(string line) {
    // 1. 清除註解 用Regex
    // 2. 清除所有空白、空白行
    // 3.  a. 從00開始編號(在line[0]插入"{count}:")，每換行count++
    //     b. 當line == "(LOOP)\n" or line== "(STOP)\n"  -> "(" in line 時
    //        tmp = regex取出 () 裡面的東西，在line最後加上"symbol:{tmp} address={count}"
    //        並且 下一行count--


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
// https://cloud.tencent.com/developer/article/1398721

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


/*
PS C:\Users\user\Desktop\計算機結構\co\06> ./asm sum
============= PASS1 ================
00:@10
01:D=A
02:@0
03:M=D
04:@i 
05:M=1 
06:@sum
07:M=0 
08:(LOOP)
symbol:LOOP address=8
08:@i 
09:D=M
10:@R0
11:D=D-M
12:@STOP
13:D;JGT
14:@i 
15:D=M
16:@sum
17:M=D+M
18:@i 
19:M=M+1 
20:@LOOP 
21:0;JMP
22:(STOP)
symbol:STOP address=22
22:@sum
23:D=M
24:@R1
25:M=D 
============= PASS2 ================
00: @10                  0000000000001010 000a
01: D=A                  1110110000010000 ec10
02: @0                   0000000000000000 0000
03: M=D                  1110001100001000 e308
04: @i                   0000000000010000 0010
05: M=1                  1110111111001000 efc8
06: @sum                 0000000000010001 0011
07: M=0                  1110101010001000 ea88
(LOOP)
08: @i                   0000000000010000 0010
09: D=M                  1111110000010000 fc10
0A: @R0                  0000000000000000 0000
0B: D=D-M                1111010011010000 f4d0
0C: @STOP                0000000000010110 0016
0D: D;JGT                1110001100000001 e301
0E: @i                   0000000000010000 0010
0F: D=M                  1111110000010000 fc10
10: @sum                 0000000000010001 0011
11: M=D+M                1111000010001000 f088
12: @i                   0000000000010000 0010
13: M=M+1                1111110111001000 fdc8
14: @LOOP                0000000000001000 0008
15: 0;JMP                1110101010000111 ea87
(STOP)
16: @sum                 0000000000010001 0011
17: D=M                  1111110000010000 fc10
18: @R1                  0000000000000001 0001
19: M=D                  1110001100001000 e308
*/


}





