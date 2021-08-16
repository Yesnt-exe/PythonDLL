build_windows.bat was not yet tested, windows windows version was not yet testet/compiled and might not even compile!
Linux version was compiled and tested
On linux function input() does not work!


How to use?

Before building you must have installed pyinstaller with pip3/pip
On linux you need to have wine emulator installed

Just write your functions in functions.py

example:
def a():
	return 5
Run sh build_linux or build_windows.bat

Build library location: lib/
Header location: include/

Next in c++/c you just link library from lib/ and include header from include

Warning:

You must prepare binary before using ExecuteFunction by calling PrepareBinary() (you do it just once)

After calling all python functions you can call RemoveBinary(), this will undo PrepareBinary()
