echo Building...

python PreProcess.py
python RunCode.py
pyinstaller --onefile --noconsole pybuild.py
cp .\dist\pybuild.exe ./pydll
del build -r
del dist -r
del pybuild.spec
./b2h.exe pydll
del pydll
g++ -shared -o out/libs/pydll.dll dll_build.cpp
del pydll.h