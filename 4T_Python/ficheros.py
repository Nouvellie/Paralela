import numpy as np
import math as mt

#Calculamos distancia ingresando 2 vertices casteados en enteros y la lista lnodos
def cal_dist(v1,v2,lnodos):
	dist=mt.sqrt(((float(lnodos[v1][1])-float(lnodos[v2][1]))*(float(lnodos[v1][1])-float(lnodos[v2][1])))+((float(lnodos[v1][2])-float(lnodos[v2][2]))*(float(lnodos[v1][2])-float(lnodos[v2][2]))))
	return dist
#Calculamos los angulos con arcoseno ingresando 3 distancias
def angulos(a,b, c):
	lista= [None] * 3
	lista[0]=(mt.acos((c*c-a*a-b*b)/(-2*a*b)))*180/3.1415
	lista[1]=(mt.acos((a*a-b*b-c*c)/(-2*b*c)))*180/3.1415
	lista[2]=(mt.acos((b*b-a*a-c*c)/(-2*a*c)))*180/3.1415
	return lista

#Genera los 3 angulos a todos los triangulos de toda la malla y se los agrega a la lista lelementos
def cal_ang(lnodos,lelementos):
	lista=[None] *3
	for i in range(1,int(lelementos[0][0])+1):
			lista=angulos(cal_dist(int(lelementos[i][1]),int(lelementos[i][2]),lnodos),cal_dist(int(lelementos[i][1]),int(lelementos[i][3]),lnodos),cal_dist(int(lelementos[i][2]),int(lelementos[i][3]),lnodos))
			lelementos[i].append(lista[0])
			lelementos[i].append(lista[1])
			lelementos[i].append(lista[2])

def cal_ang_solo(lnodos, lelementos,i):
	lista=[]
	lista=angulos(cal_dist(int(lelementos[lelementos[i][0]][1]),int(lelementos[lelementos[i][0]][2]),lnodos),cal_dist(int(lelementos[lelementos[i][0]][1]),int(lelementos[lelementos[i][0]][3]),lnodos),cal_dist(int(lelementos[lelementos[i][0]][2]),int(lelementos[lelementos[i][0]][3]),lnodos))
	lelementos[lelementos[i][0]].append(lista[0])
	lelementos[lelementos[i][0]].append(lista[1])
	lelementos[lelementos[i][0]].append(lista[2])

#Criterio de refinamiento, si algun angulo del un triangulo es menor al angulo critico se le asigna un 1 de refinar en contraparte 0 de no refinar
def crit_ref(lelementos, crit_ang):
	cant_ref=0
	for i in range(1,int(lelementos[0][0])+1):
		if lelementos[i][4] < crit_ang or lelementos[i][5] < crit_ang or lelementos[i][6] < crit_ang:
			cant_ref=cant_ref+1
			lelementos[i].append(1)
		else:
			lelementos[i].append(0)
	return cant_ref				

#En esta funcion determinamos las distancias mayores y asignaermos los vertices a esa distancia mayor
def arista_larga(lelementos):
	for i in range(1,int(lelementos[0][0])+1):
		lista=[None] * 3
		if (cal_dist(int(lelementos[i][1]),int(lelementos[i][2]),lnodos) > cal_dist(int(lelementos[i][1]),int(lelementos[i][3]),lnodos)) and (cal_dist(int(lelementos[i][1]),int(lelementos[i][2]),lnodos) > cal_dist(int(lelementos[i][2]),int(lelementos[i][3]),lnodos)):
			lista[0]=cal_dist(int(lelementos[i][1]),int(lelementos[i][2]),lnodos)
			lista[1]=lelementos[i][1]
			lista[2]=lelementos[i][2]
			lelementos[i].append(lista)
		elif (cal_dist(int(lelementos[i][1]),int(lelementos[i][3]),lnodos) > cal_dist(int(lelementos[i][1]),int(lelementos[i][2]),lnodos)) and (cal_dist(int(lelementos[i][1]),int(lelementos[i][3]),lnodos) > cal_dist(int(lelementos[i][2]),int(lelementos[i][3]),lnodos)):
			lista[0]=cal_dist(int(lelementos[i][1]),int(lelementos[i][3]),lnodos)
			lista[1]=lelementos[i][1]
			lista[2]=lelementos[i][3]
			lelementos[i].append(lista)
		elif (cal_dist(int(lelementos[i][2]),int(lelementos[i][3]),lnodos) > cal_dist(int(lelementos[i][1]),int(lelementos[i][2]),lnodos)) and (cal_dist(int(lelementos[i][2]),int(lelementos[i][3]),lnodos) > cal_dist(int(lelementos[i][1]),int(lelementos[i][3]),lnodos)):
			lista[0]=cal_dist(int(lelementos[i][2]),int(lelementos[i][3]),lnodos)
			lista[1]=lelementos[i][2]
			lista[2]=lelementos[i][3]
			lelementos[i].append(lista)


def arista_larga_solo(lelementos, i):
		lista=[None] * 3
		if (cal_dist(int(lelementos[i][1]),int(lelementos[i][2]),lnodos) > cal_dist(int(lelementos[i][1]),int(lelementos[i][3]),lnodos)) and (cal_dist(int(lelementos[i][1]),int(lelementos[i][2]),lnodos) > cal_dist(int(lelementos[i][2]),int(lelementos[i][3]),lnodos)):
			lista[0]=cal_dist(int(lelementos[i][1]),int(lelementos[i][2]),lnodos)
			lista[1]=lelementos[i][1]
			lista[2]=lelementos[i][2]
			lelementos[i].append(lista)
		elif (cal_dist(int(lelementos[i][1]),int(lelementos[i][3]),lnodos) > cal_dist(int(lelementos[i][1]),int(lelementos[i][2]),lnodos)) and (cal_dist(int(lelementos[i][1]),int(lelementos[i][3]),lnodos) > cal_dist(int(lelementos[i][2]),int(lelementos[i][3]),lnodos)):
			lista[0]=cal_dist(int(lelementos[i][1]),int(lelementos[i][3]),lnodos)
			lista[1]=lelementos[i][1]
			lista[2]=lelementos[i][3]
			lelementos[i].append(lista)
		elif (cal_dist(int(lelementos[i][2]),int(lelementos[i][3]),lnodos) > cal_dist(int(lelementos[i][1]),int(lelementos[i][2]),lnodos)) and (cal_dist(int(lelementos[i][2]),int(lelementos[i][3]),lnodos) > cal_dist(int(lelementos[i][1]),int(lelementos[i][3]),lnodos)):
			lista[0]=cal_dist(int(lelementos[i][2]),int(lelementos[i][3]),lnodos)
			lista[1]=lelementos[i][2]
			lista[2]=lelementos[i][3]
			lelementos[i].append(lista)
#Calcula el punto medio			
def pto_mdo(v1, v2, lnodos):
	lista=[None] * 3
	lista[0]=(float(lnodos[v1][1])+float(lnodos[v2][1]))/2
	lista[1]=(float(lnodos[v1][2])+float(lnodos[v2][2]))/2

	a=int(lnodos[0][0])+1
	lnodos[0][0]=a
	lnodos.append([a])
	lnodos[a].append(lista[0])
	lnodos[a].append(lista[1])
	lista[2]=a
	return lista

#Se le sacara punto medio a todos los triangulos, pero se analizara despues si es necesario sacar punto medio a la arista mayor de todos los T
def asig_pto_mdo(lelementos):
	lista=[None] * 3
	for i in range(1,int(lelementos[0][0])+1):
		lista=pto_mdo(int(lelementos[i][8][1]),int(lelementos[i][8][2]),lnodos)
		lelementos[i].append(lista)

def pto_mdoa_ele(lelements,indice,lnodes):
	i=0
	while (lelementos[indice][9][0] == lnodos[i][1] and lelementos[indice][9][1] == lnodos[i][2]) or (i==lnode[0][0]):
		return int(lnodos[i][0])

def crear_indice(lelementos):
	
	a=int(lelementos[0][0])+1
	lelementos[0][0]=a
	print lelementos[0][0]
	lelementos.append([a])
def crear_triangulo(v1, v2, v3,lelementos):
	#Esta lista genera los tres vertices y el numero del triangulo si es refinable 1 y 0
	lista=[None] * 3
	#Genera 3 angulos
	#genera la distancia mas larga y los vertices asociados
	lista3=[None] * 3
	#Genera el punto medio de la arista mayor
	lista4=[None] * 2

	lista[0]=v1
	lista[1]=v2
	lista[2]=v3
	#se agregaran los 3 vertices en las casillas de la fila nueva -lista[0]-
	lelementos[lelementos[0][0]].append(lista[0])
	lelementos[lelementos[0][0]].append(lista[1])
	lelementos[lelementos[0][0]].append(lista[2])
	cal_ang_solo(lnodos,lelementos,int(lelementos[0][0]))
	"""#Se agregaran los 3 angulos
	lelementos[lelementos[0][0]].append(lista2[0])
	lelementos[lelementos[0][0]].append(lista2[1])
	lelementos[lelementos[0][0]].append(lista2[2])"""
	#No entra al criterio de refinamiento, pero si al de conformidad
	lelementos[lelementos[0][0]].append(0)
	lista3=arista_larga_solo(lelementos,int(lelementos[0][0]))
	#se llena la casilla 8 con la distancia mayor y los dos vertices que contienen la arista mayor
	#Se genera 
	lista4=pto_mdo(lelementos[int(lelementos[0][0])][8][1],lelementos[int(lelementos[0][0])][8][2], lnodos)
	lelementos[lelementos[0][0]].append(lista4)

	pto_opuesto_solo(lelementos, lelementos[0][0])


#REVISAR PUNTO MEDIO
def cuatro_t(lelementos):
	i=0
	while lelementos[i][7] != 1:
		i=i+1	
	crear_triangulo(lelementos[i][9],lelementos[i][8][1],pto_mdo(lelementos[i][8][1],lelementos[i][10]),lelementos)
	crear_triangulo(lelementos[i][9],lelementos[i][8][2],pto_mdo(lelementos[i][8][2],lelementos[i][10]),lelementos)
	crear_triangulo(pto_mdo(lelementos[i][8][1],lelementos[i][10]),lelementos[i][8][2],pto_mdo(lelementos[i][8][2],lelementos[i][10]),lelementos)
	crear_triangulo(pto_mdo(lelementos[i][8][1],lelementos[i][10]),lelementos[i][8][2],pto_mdo(lelementos[i][8][2],lelementos[i][9]),lelementos)


def pto_opuesto_solo(lelementos, indice):
	if (lelementos[indice][1] != lelementos[indice][8][1]) and (lelementos[indice][1] != lelementos[indice][8][2]):
		lelementos[indice].append(lelementos[indice][1])
	elif (lelementos[indice][2] != lelementos[indice][8][1]) and (lelementos[indice][2] != lelementos[indice][8][2]):
		lelementos[indice].append(lelementos[indice][2])
	elif (lelementos[indice][3] != lelementos[indice][8][1]) and (lelementos[indice][3] != lelementos[indice][8][2]):
		lelementos[indice].append(lelementos[indice][3])
#Calculamos punto opuesto a la arista mayor

def pto_opuesto(lelementos):
	for i in range(1,int(lelementos[0][0])+1):
		if (lelementos[i][1] != lelementos[i][8][1]) and (lelementos[i][1] != lelementos[i][8][2]):
			lelementos[i].append(lelementos[i][1])
		elif (lelementos[i][2] != lelementos[i][8][1]) and (lelementos[i][2] != lelementos[i][8][2]):
			lelementos[i].append(lelementos[i][2])
		elif (lelementos[i][3] != lelementos[i][8][1]) and (lelementos[i][3] != lelementos[i][8][2]):
			lelementos[i].append(lelementos[i][3])

def leer_node():
	#Lee el fichero .node y lo asigna a la lista lnodos
	lineas = open("mesh.node").readlines()
	lnodos = [[m.strip() for m in n] for n in [linea.split(" ") for linea in lineas]]
	return lnodos	

def leer_ele():	
	#Lee el fichero .ele y lo asigna a la lista lelementos
	lineas = open("mesh.ele").readlines()
	lelementos = [[m.strip() for m in n] for n in [linea.split(" ") for linea in lineas]]
	return lelementos

def anadir_linea_ele(lelementos):
	fp=open('mesh.ele','a')
	fp.write('\n1')
	fp.close()

lnodos=leer_node()
lelementos=leer_ele()
#lelementos[1].append(5)

#ele(lelementos)

"""print cal_dist(1,2,lnodos)
lista=[]
lista=angulos(0.999668445,1.4186599311,1.0469407815)
print lista
"""

cal_ang(lnodos,lelementos)
#print lelementos

cant_r=crit_ref(lelementos,30)
print cant_r


arista_larga(lelementos)

asig_pto_mdo(lelementos)


pto_opuesto(lelementos)

a=pto_mdo(1,2,lnodos)


print lnodos

##print lelementos
for elem in lelementos:
	print elem
