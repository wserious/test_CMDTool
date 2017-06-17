#include <windows.h>
#include <iostream>
#include <cstdio>

void welcome();
void command_switch(char *cmd_str) ;
BOOL CreateChildProcess(char *cmd_str);

int main() {
    char Command_str[MAX_PATH];
    DWORD Command_len;
    HANDLE hConsoleInput;

    //get the input steam handle
    hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);

    //get the welcome message
    welcome();

    while(true) {
        //clear the command string
        memset(&Command_str, 0, MAX_PATH);
        //output the hint symbol
        printf("my cmd>:");
        //read the input stream
        ReadFile(
                hConsoleInput,    //file handle
                Command_str,      //buffered char[]
                MAX_PATH,        //size of buffered char[]
                &Command_len,     //real size of read
                NULL
        );

        command_switch(Command_str);
    }
}

void command_switch(char *cmd_str) {
    char cmd_tmp[MAX_PATH] = {0};
    char *pstr = cmd_str, *ptmp = cmd_tmp;

    //unitl the \n ,convert the char from cmd_str to cmd_tmp
    while(*pstr != '\r' && *pstr != '\n') {
        *ptmp++ = *pstr++;
    }

    //
    if(strcmp(cmd_tmp, "hi") == 0) {
        printf("hello user\n");
    } else if (strcmp(cmd_tmp, "exit") == 0) {
        exit(0);
    }  else {
        printf("Error: command not found\n");
    }
}

void welcome() {
    printf("CMD Tool [test version]\n");
}

BOOL CreateChildProcess(char *cmd_str) {
    STARTUPINFO start_info;
    PROCESS_INFORMATION process_info;
    BOOL flag;

    //clear the start struct information
    //todo; to be continued
}