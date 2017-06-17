#include <Windows.h>
#include <iostream>
#include <cstdio>

void welcome();

int main() {
    char Command_str[MAX_PATH];
    DWORD Command_len;
    HANDLE hConsoleInput;

    //获得输出流的句柄
    hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);

    //get the welcome message
    welcome();

    while(true) {
        //clear the command string
        memset(&Command_str, 0, MAX_PATH);
        //output the hint symbol
        printf("nLscmd>;");

        ReadFile(
                hConsoleInput,
                Command_str,
                MAX_PATH,
                &Command_len,
                NULL
        );

        printf("收到命令：[%s]", Command_str);
    }
}

void welcome() {
    printf("CMD Tool [test version]\n");
}