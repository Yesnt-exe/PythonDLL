import inspect

def get_arguments(func) -> list:
    ls = str(inspect.signature(func))
    ls = ls.replace("(", "")
    ls = ls.replace(")", "")
    ls = ls.replace(" ", "")
    ls = ls.split(",")
    return ls;
    

def get_functions() -> list:
    data = []
    gr = globals().copy()
    for i in gr.items():
        if str(i[1]).startswith("<function"):
            dt = str(i[1])
            dt = dt["<function ".__len__():dt.find("at")-1]
            if dt.startswith("__") or dt.endswith("__") or dt == "get_functions" or dt == "get_arguments":
                continue
            data.append(dt)
    return data

def get_cpp_data():
    funcs = []
    for function in get_functions():
        toappend = "std::string " + function + " ("
        try:
            args = get_arguments(globals()[function])
        except:
            continue
        for argument in args:
            oldargument = argument
            argument: str
            if argument.__contains__("->"):
                argument = argument[0 : argument.find("->")]
                if argument == "":
                    continue
            if args[0] != argument and args[0] != oldargument:
                toappend += " , std::string " + argument
            else:
                toappend += "std::string " + argument
        toappend += ")"
        toappend : str
        if toappend.__contains__("total_ordering"):
            continue
        funcs.append(toappend)
    return funcs



data = get_functions()
cdata = get_cpp_data()
iteration = 0
fungs = []
for i in cdata:
    i : str 
    while not i.__contains__(data[iteration]):
        iteration += 1
    fungs.append(data[iteration])
    iteration += 1
iteration = 0
write = open("out/headers/GeneratedCode.hpp", "w")
datatowrite = ""
for i in fungs:
    datatowrite += cdata[iteration]
    datatowrite += '{\nreturn ExecuteFunction_str('
    datatowrite += '"'
    datatowrite += i
    datatowrite += '"'
    args = get_arguments(globals()[i])
    aiter = True
    for a in args:
        if a.__contains__("->"):
                a = a[0 : a.find("->")]
                if a == "":
                    continue
        datatowrite += ','
        aiter = False
        datatowrite += a
    datatowrite += ');\n}\n'
    iteration += 1

batawrite = """#ifdef __cplusplus\n#include "pydll_cpp.h" \n"""
for i in range(0, datatowrite.__len__()):
    if datatowrite[i] == ',' and datatowrite[i-1] != '"' and datatowrite[i-1] != ' ':
        batawrite += '\\'
    else:
        batawrite += datatowrite[i] 

batawrite = batawrite.replace("\\", """ + "," + """)
batawrite = batawrite.replace('")', '", "")')
batawrite += "\n#endif"

write.write(batawrite)
write.close()