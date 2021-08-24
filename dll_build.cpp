#include "pydll.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <thread>

#ifdef __unix__
#include <unistd.h>
#else
#include <Windows.h>
#include <iostream>
#endif

using namespace std;

#ifdef __unix
void StartApp(const char* appname)
#else
HANDLE StartApp(const char* appname)
#endif
{
    #ifdef __unix__
    string data = string(appname);
    system(string(string("chmod 777 ") + data).c_str());
    system(string(data + "& > /dev/null").c_str());
    return;
    #else
    //windows stuff
    STARTUPINFO info = {sizeof(info)};
    PROCESS_INFORMATION pinfo;
    info.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    info.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    info.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    CreateProcessA(appname, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &info, &pinfo);
    return pinfo.hProcess;
    #endif
}




extern "C" void PrepareBinary(){
    FILE* fptr = fopen("pydll.exe", "wb");
    fwrite((const void*)pydll, 1, sizeof(pydll)/sizeof(pydll[0]), fptr);
    fclose(fptr);
}
extern "C" void RemoveBinary(){
    remove("pydll.exe");
    remove("_resp_");
}

extern "C" const char* ExecuteFunction(const char* functionname,const char* args){
    FILE* fptr = fopen("_info_", "w");
    fwrite(functionname, 1,strlen(functionname), fptr);
    fputc('\n', fptr);
    fwrite(args, 1, strlen(args), fptr);
    fclose(fptr);
    #ifdef __unix__
    remove("_resp_");
    StartApp("./pydll.exe");
    while(access("_resp_", F_OK)){
        this_thread::sleep_for(chrono::milliseconds(30));
    }
    #else
    HANDLE hndl = StartApp("pydll.exe");
    //windows
    BOOL isrunning = true;
    while(isrunning){
        DWORD ret = WaitForSingleObject(hndl, 0);
        isrunning = ret == WAIT_TIMEOUT;
    }
    CloseHandle(hndl);
    #endif
    ifstream rd("_resp_", ifstream::in);
    string data;
    string line;
    while(getline(rd, line)){
        data += line;
        data += "\n";

    }
    rd.close();
    return data.c_str();
}
extern "C" string ExecuteFunction_str(const char* functionname,const char* args){
    FILE* fptr = fopen("_info_", "w");
    fwrite(functionname, 1,strlen(functionname), fptr);
    fputc('\n', fptr);
    fwrite(args, 1, strlen(args), fptr);
    fclose(fptr);
    #ifdef __unix__
    remove("_resp_");
    StartApp("./pydll.exe");
    while(access("_resp_", F_OK)){
        this_thread::sleep_for(chrono::milliseconds(30));
    }
    #else
    HANDLE hndl = StartApp("pydll.exe");
    //windows
    BOOL isrunning = true;
    while(isrunning){
        DWORD ret = WaitForSingleObject(hndl, 0);
        isrunning = ret == WAIT_TIMEOUT;
    }
    CloseHandle(hndl);
    #endif
    ifstream rd("_resp_", ifstream::in);
    string data;
    string line;
    while(getline(rd, line)){
        data += line;
        data += "\n";
    }
    rd.close();
    return data;
}
