
## Where to write code?:

	Its simple, just write your code as functions in file named "functions.py",
	after building these functions will be callable from your DLL

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
		run build_windows.bat from cmd
		DLL will be saved in /out/libs/
## Addtional information:
	Warning!
	Linux version uses system() function so it might be unsafe!

	Functions that does not work:
		printf() <- Does not work on Windows version
		input() <- Does not work on both versions
![](https://www.python.org/static/community_logos/python-powered-w-100x40.png)