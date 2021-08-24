import os, sys
if os.name == "nt":
	fl = open("_stdout", "w")
	sys.stderr = fl
	sys.stdout = fl

from functions import *

func = ""
args = ""
try:
	with open("_info_", "r") as read:
		func = read.readline()
		args = read.readline()
		read.close()
	os.remove("_info_")
	returndata = ""
	try:
		exec("returndata = str(" + func + "(" + args + "))")
	except Exception as e:
		returndata = "Exception" + "\n" + str(e)
	with open("_resp_", "w") as write:
		write.write(returndata)
		write.close()
except:
	with open("_resp_", "w") as write:
		write.write("Critical aplication error!")
		write.close()