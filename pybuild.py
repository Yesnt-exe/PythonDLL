from os import remove
from functions import *

func = ""
args = ""
try:
	with open("_info_", "r") as read:
		func = read.readline()
		args = read.readline()
		read.close()
	remove("_info_")
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