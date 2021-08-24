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
HANDLE _pstdout;
HANDLE _pstdoutr;
#endif

using namespace std;

#ifndef __unix__
extern "C" char* win_rstdout(int* _len){
    FILE* readout = fopen("_stdout", "r");
    fseek(readout, 0, SEEK_END);
    size_t len = ftell(readout);
    rewind(readout);
    char* data = (char*)malloc(len + 1);
    data[fread(data, 1, len, readout)] = '\0';
    fclose(readout);
    *_len = (int)len;
    remove("_stdout");
    return data;
}
#endif


#ifdef __unix__
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
    //create pipe
    SECURITY_ATTRIBUTES pattr;
    ZeroMemory(&pattr, sizeof(pattr)); //clear mem
    pattr.bInheritHandle = FALSE;
    pattr.nLength = sizeof(pattr);
    pattr.lpSecurityDescriptor = NULL;
    CreatePipe(&_pstdoutr, &_pstdout, &pattr, 0); // create pipe
    STARTUPINFOA info = {sizeof(info)};
    PROCESS_INFORMATION pinfo;
    info.hStdError = _pstdout; // stderr to stdout
    info.hStdOutput = _pstdout; // stdout to stdout
    info.hStdInput = NULL;
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
    
    BOOL isrunning = true;
    while(isrunning){
        DWORD ret = WaitForSingleObject(hndl, 0);
        isrunning = ret == WAIT_TIMEOUT;
        if(isrunning){
            //ReadStdout(stdout, 32); //not working
        }
        this_thread::sleep_for(std::chrono::milliseconds(30));
    }
    CloseHandle(_pstdoutr);
    CloseHandle(_pstdout);
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
        this_thread::sleep_for(std::chrono::milliseconds(30));
    }
    CloseHandle(_pstdoutr);
    CloseHandle(_pstdout);
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
