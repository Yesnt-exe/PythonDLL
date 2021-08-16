echo This app require wine windows emulator!
echo Please ensure you have installed pyinstaller or ran prepare_linux/window before running this script!
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
