import math

archivo = open("in.txt", "w")
lineas = ["100\n"]
for i in range(1, 101):
    linea = ""
    for j in range(1, 101):
        linea = linea + " 1"
    linea = linea + "\n"
    lineas.append(linea)

archivo.writelines(lineas)
archivo.close()
