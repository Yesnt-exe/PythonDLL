#include <string>

extern "C"{

//Calls a function named (functionname) with args (args) and returns function return value converted to string as const char*
//for example 
//(functionname) = add
//(args) = 2,5
//function called = add(2,5)
//return value is (const char*)"7"

//WARNING This function might return garbage instead of return value, ExecuteFunction_str does not have this problem!
extern const char* ExecuteFunction(const char* functionname, const char* args);

//Calls a function named (functionname) with args (args) and returns function return value converted to string as const char*
//for example 
//(functionname) = add
//(args) = 2,5
//function called = add(2,5)
//return value is (const char*)"7"
extern std::string ExecuteFunction_str(const char* functionname, const char* args);

#ifndef __unix__
//only on windows, read stdout
extern char* win_rstdout(int* lenght);
#endif

//This removes pydll.exe/pydll
extern void RemoveBinary();

//This creates pydll.exe/pydll
extern void PrepareBinary();
}