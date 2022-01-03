## Where to write code?:
It's simple, just write your code as functions in file named "functions.py", after building these functions will be callable from your DLL

You can call functions by using GeneratedCode.hpp with c++, defined functions from functions.py will be exported there but some of the functions might not export when that happens you can still use them with ExecuteFunction()

## How to build?:

### Linux:
Requirements:
- Wine
- Python 3.x + pyinstaller
- g++ c++ compiler
Run sh build_linux.sh from terminal

The output will be saved in /out/libs/

### Windows:
Requirements:
- Python 3.x + pyinstaller
- MinGW

Open `cmd.exe` as administrator and `cd` it to the PythonDLL directory.

The output will be saved in /out/libs/
## Addtional information:
### Warning!
Linux version uses the `system()` function so it might be unsafe!

Remember that auto header generation is experimental and might not work properly!

Update: You can use [LoadPy](https://github.com/Yesnt-exe/LoadPy) instead of this project to use safer function.

### Functions that does not work
`printf()` <- Full support on Linux, on Windows you need to use `win_rstdout()` function to get *stdout*

`input()` <- Does not work on both operating systems.
