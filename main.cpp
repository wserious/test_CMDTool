#include <windows.h>
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
    //overwrite the newline
    *pstr = '\0';

    //
    if(strcmp(cmd_tmp, "hi") == 0) {
        printf("hello user\n");
    } else if (strcmp(cmd_tmp, "exit") == 0) {
        exit(0);
    }  else {
        CreateChildProcess(cmd_str);
    }
}

void welcome() {
    printf("CMD Tool [test version]\n");
}

BOOL CreateChildProcess(char *cmd_str) {
    STARTUPINFO start_info;
    PROCESS_INFORMATION process_info;
    BOOL flag;

    //clear the start struct information( equals to memset_0)
    ZeroMemory( &start_info, sizeof(start_info));
    //set the size of struct, cb is the size
    start_info.cb = sizeof(start_info);
    //clear the process struct
    ZeroMemory( &process_info, sizeof(process_info));

    flag = CreateProcess(
            NULL,
            cmd_str,
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &start_info,
            &process_info
    );

    if(!flag) {
        //create failed
        printf("Error : command not found (%d).\n", GetLastError());
        return 0;
    }

    //wait for sub process end
    WaitForSingleObject(process_info.hProcess, INFINITE);
    //close the process handle
    CloseHandle(process_info.hProcess);
    CloseHandle(process_info.hThread);

    return 1;
}