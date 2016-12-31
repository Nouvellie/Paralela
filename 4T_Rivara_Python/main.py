import random 
import pylab 
 
 
 
class Punto(object): 
    def __init__(self, x, y): 
        self.x=float(x) 
        self.y=float(y) 
 
    def __str__(self): 
        return '(' + str(round(self.x,2)) + ', '+str(round(self.y,2))+ ')' 
     
         
    def __sub__(self,other): 
        return Punto(self.x-other.x,self.y-other.y) 
 
    def deter(self,other): 
        return self.x * other.y - self.y * other.x 
 
    def isColinealTo(self, other): 
        if abs(self.deter(other))<0.0000001: 
            return True 
        else: 
            return False 
 
    def is_in_Seg(self, segmento): 
        v=segmento.destino-self 
        w=self - segmento.origen 
        return v.isColinealTo(w) and v.x * w.x >=0 
         
    def is_in_Tri(self, este_triangulo): 
        # una manera rara de determinar si un punto esta en el triangulo usando areas 
        a=este_triangulo.area() 
         
        for k in range(3): 
            aux=Triangulo(self, este_triangulo.puntos[k%3],este_triangulo.puntos[(k+1)%3]) 
             
            a -= aux.area() 
             
        if a<-0.00001: # para evitar que por poquito nos de mal tenemos que  
             
            return False 
        else: 
            return True 
 
 
 
class Segmento(object): 
    def __init__(self,origen, destino): 
        self.origen=origen 
        self.destino=destino 
 
    def __str__(self): 
        return self.origen.__str__() +'->'+ self.destino.__str__() 
 
    def getDirection(self): 
        return self.destino - self.origen  
 
    def is_cut_by(self,other): 
        v=self.getDirection() 
        w=other.getDirection() 
                 
        if v.isColinealTo(w): 
             
            return False 
        else: 
            #resuelvo con Cramer el punto interseccion(en forma parametrica) 
                        
            s= v.deter(self.origen-other.origen)/v.deter(w) 
            t= w.deter(self.origen-other.origen)/v.deter(w) 
             
            if s>0.0000001 and s<0.9999999 and t>0.0000001 and t<0.9999999: 
                return True 
            else: 
                return False 
    
 
 
 
class Triangulo(object): 
    def __init__(self,A,B,C): 
        self.puntos=[A,B,C] 
        self.lados=[Segmento(A,B),Segmento(B,C),Segmento(C,A)] 
         
    def __str__(self): 
        return self.puntos[0].__str__()+ self.puntos[1].__str__()+ self.puntos[2].__str__() 
 
 
              
    def area(self): 
        suma=0 
        for k in range(3): 
            suma += self.puntos[k%3].x * self.puntos[(k+1)%3].y 
            suma -= self.puntos[k%3].y * self.puntos[(k+1)%3].x 
        return abs(suma/2.0) 
 
 
 
# dado un conjunto de puntos, la funcion triangular devuelve un diccionario con los puntos, los lados y los triangulos 
# de una triangulacion de dichos puntos. 
 
def triangular(puntos,best=False): 
    if best==False: 
        # elijo los primeros tres puntos de la triangulacion 
        # formo el primer triangulo y los primeros tres lados 
         
        triangulos=[Triangulo(puntos[0],puntos[1],puntos[2])] 
        lados=triangulos[0].lados 
 
        for k in range(3,len(puntos)): 
            # tomo un punto P 
                        
            interior=False 
            # me fijo si P esta en el interior de un triangulo 
             
            for tri in triangulos: 
                if puntos[k].is_in_Tri(tri): 
                    interior=True 
 
                    #tiro el triangulo padre 
                    triangulos.remove(tri) 
 
                    # y agrego los lados y los triangulos 
                    for j in range(3): 
                        nuevo=Triangulo(puntos[k],tri.puntos[j%3],tri.puntos[(j+1)%3]) 
                        triangulos.append(nuevo) 
                        lados.append(Segmento(puntos[k],tri.puntos[j])) 
                         
                         
                    break 
 
            # si P no esta en ninguno de los triangulos  
 
             
            if interior==False: 
                 
                nuevoslados=[] 
                 
                for j in range(k): 
                     
                    posible_lado=Segmento(puntos[j],puntos[k])         
                     
                    #testeo si el posible_lado corta a los lados que ya tengo 
                    for lado in lados: 
                        corta=False 
                        if posible_lado.is_cut_by(lado): 
                            corta=True  
                            break 
                                            
                    if corta==False: 
                        nuevoslados.append(posible_lado) 
                         
                 
                for l in nuevoslados: 
                    lados.append(l) 
                    print l 
                     
 
                # Ahora me fijo que triangulos debo agregar los triangulos 
                for lado1 in nuevoslados: 
                    for lado2 in nuevoslados: 
                        p1=lado1.origen 
                        p2=lado2.origen 
                        for viejos in lados: 
                            if (p1==viejos.origen and p2==viejos.destino):  
                                nuevo_tri=Triangulo(puntos[k],p1,p2) 
                                triangulos.append(nuevo_tri) 
 
        return {'puntos': puntos, 'triangulos':triangulos, 'lados': lados}         
    else: 
       pass # la idea seria shufflear los puntos y quedarme con la triangulacion 
             # que encuentre la mejor segun algun criterio, por ejemplo la que       menos triangulos tenga. Lo dejo para otro dia. 
 
 
 
# un ejemplo: 
 
pts=[] 
for k in range(10): 
    pts.append(Punto(random.random(),random.random())) 
prueba=triangular(pts) 
 
 
puntosX=[] 
puntosY=[] 
for p in  prueba['puntos']: 
    print p 
    puntosX.append(p.x) 
    puntosY.append(p.y) 
 
for l in prueba['lados']: 
    pylab.plot([l.origen.x,l.destino.x],[l.origen.y,l.destino.y],'-') 
 
 
pylab.plot(puntosX,puntosY,'g^',[-0.1,1.1,1.1,-0.1,-0.1],[-0.1,-0.1,1.1,1.1,-0.1],'b') 
pylab.show() 