echo Building...
python PreProcess.py
python RunCode.py
pyinstaller pybuild.py --onefile --noconsole
cp dist/pybuild ./pydll
rm build -r
rm dist -r
rm pybuild.spec
wine b2h.exe pydll
rm pydll
g++ -shared -fPIC -o pydll.so dll_build.cpp
rm pydll.h 
mv pydll.so out/libs/
rm __pycache__/ -r
