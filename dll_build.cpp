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
#endif

using namespace std;


void StartApp(const char* appname){
    #ifdef __unix__
    string data = string(appname);
    system(string(string("chmod 777 ") + data).c_str());
    system(string(data + "& > /dev/null").c_str());
    return;
    #else
    //windows stuff
    ShellExecuteA(0,"open",appname,NULL,NULL,SW_HIDE);
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
    #else
    StartApp("pydll.exe");
    #endif
    while(access("_resp_", F_OK)){
        this_thread::sleep_for(chrono::milliseconds(30));
    }
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
    #else
    StartApp("pydll.exe");
    #endif
    while(access("_resp_", F_OK)){
        this_thread::sleep_for(chrono::milliseconds(30));
    }
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
