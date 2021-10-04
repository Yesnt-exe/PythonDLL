
## Where to write code?:

	Its simple, just write your code as functions in file named "functions.py",
	after building these functions will be callable from your DLL
	You can call functions by using GeneratedCode.hpp with c++, defined functions from functions.py will be exported there but some of the functions might not export when that happens you can still use them with ExecuteFunction()

## How to build?:

	Linux:
		Requirements:
			-wine
			-python 3.x + pyinstaller
			-g++ c++ compiler
		run sh build_linux.sh from terminal
		DLL will be saved in /out/libs/

	Windows:
		Requirements:
			-python 3.x + pyinstaller
			-g++ c++ compiler
			-powershell

		open POWERSHELL as administrator in PythonDLL directory
		type Set-ExecutionPolicy RemoteSigned and then,
		run build_windows.ps1
		DLL will be saved in /out/libs/
## Addtional information:
	Warning!
	Linux version uses system() function so it might be unsafe!
	Remember that auto header generation is experimental and might not work properly!

	Functions that does not work:
		printf() <- Full support on linux, on windows you need to use win_rstdout() function to get stdout
		input() <- Does not work on both versions
![](https://www.python.org/static/community_logos/python-powered-w-100x40.png)