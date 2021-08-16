@echo off
echo Building...
pyinstaller --onefile --noconsole pybuild.py
cp dist/pybuild.exe pydll
del build
del dist 
del pybuild.spec
b2h.exe pydll
del pydll
g++ -shared -o out/libs/pydll.dll pydll.h
del pydll.h