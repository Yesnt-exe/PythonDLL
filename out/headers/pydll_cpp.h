#include <string>

typedef unsigned long size_t;

extern "C"{
//args example const char* args = "5,5,'string', False," if no args leave it empty like that const char* args = ""
//on linux systems this function may be unsafe because of using system() command, on windows it uses shellexecute
extern const char* ExecuteFunction(const char* functionname, const char* args);

extern std::string ExecuteFunction_str(const char* functionname, const char* args);

extern void RemoveBinary();

extern void PrepareBinary();
}