
read = open("functions.py", "r")
lines = read.readlines()
read.close()
read = open("GenerateCode.py", "r")
codedata = read.readlines()
read.close()
write = open("RunCode.py", "w")
for i in lines:
    write.write(i)
write.write("\n\n\n")
for i in codedata:
    write.write(i)
write.close()