#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define length(x) (sizeof(x)-sizeof(x[0]))

typedef struct triangulo t;
typedef struct punto p;

int ecuacion_recta(p x, p y, p z){
	//y-y0=m(x-x0)
	//m=(y1-y0)/(x1-x0)
	float pendiente=(y.coordenadas[1]-x.coordenadas[1])/(y.coordenadas[0]-x.coordenadas[0]);
	if(z.coordenadas[1]-x.coordenadas[1]==pendiente*(z.coordenadas[0]-x.coordenadas[0])){
		return 1;
	}else{
		return 0;
	}
}

void angulo(float a, float b, float c,float *A, float *B, float *C)  {
    *C=acos((c*c-a*a-b*b)/(-2*a*b))*180;
    *A=acos((a*a-b*b-c*c)/(-2*b*c))*180;
    *B=acos((b*b-a*a-c*c)/(-2*a*c))*180;
}

//Saco la distancia entre dos puntos
float distancia( p x, p y) {
    float dist;
    dist=sqrt( (y.coordenadas[0]-x.coordenadas[0])*(y.coordenadas[0]-x.coordenadas[0])+(y.coordenadas[1]-x.coordenadas[1])*(y.coordenadas[1]-x.coordenadas[1]));
    return dist;
}

float *punto_medio( p x, p y){
	float *coordenadas=malloc(2*sizeof(int));
	coordenadas[0]=(float)((x.coordenadas[0]+y.coordenadas[0]))/2;
	coordenadas[1]=(float)((x.coordenadas[1]+y.coordenadas[1]))/2;
	return coordenadas;
}

void generar_angulos(t t1){
	float m1=(t1.vertices[0].nodos.coordenadas[1]-t1.vertices[1].nodos.coordenadas[1])/(t1.vertices[0].nodos.coordenadas[0]-t1.vertices[1].nodos.coordenadas[0]);
	float m2=(t1.vertices[0].nodos.coordenadas[1]-t1.vertices[2].nodos.coordenadas[1])/(t1.vertices[0].nodos.coordenadas[0]-t1.vertices[2].nodos.coordenadas[0]);
	float m3=(t1.vertices[1].nodos.coordenadas[1]-t1.vertices[2].nodos.coordenadas[1])/(t1.vertices[1].nodos.coordenadas[0]-t1.vertices[2].nodos.coordenadas[0]);
	
	//Verificamos que los angulos sean positivos debe haber un peque;o error de angulos
	if(atan((m2-m1)/(1+m2*m1))<0){
		t1.angulos[0].grados=-1*atan((m2-m1)/(1+m2*m1));
		t1.angulos[0].vertice_angulo.nodos.coordenadas[0]=t1.vertices[2].nodos.coordenadas[0];
		t1.angulos[0].vertice_angulo.nodos.coordenadas[1]=t1.vertices[2].nodos.coordenadas[1];
		t1.angulos[0].vertice_angulo.numero=t1.vertices[2].numero;
	}else{
		t1.angulos[0].grados=atan((m2-m1)/(1+m2*m1));
		t1.angulos[0].vertice_angulo.nodos.coordenadas[0]=t1.vertices[2].nodos.coordenadas[0];
		t1.angulos[0].vertice_angulo.nodos.coordenadas[1]=t1.vertices[2].nodos.coordenadas[1];
		t1.angulos[0].vertice_angulo.numero=t1.vertices[2].numero;
	}
	
	if(atan((m3-m1)/(1+m3*m1))<0){
		t1.angulos[1].grados=-1*atan((m3-m1)/(1+m3*m1));
		t1.angulos[1].vertice_angulo.nodos.coordenadas[0]=t1.vertices[1].nodos.coordenadas[0];
		t1.angulos[1].vertice_angulo.nodos.coordenadas[1]=t1.vertices[1].nodos.coordenadas[1];
		t1.angulos[1].vertice_angulo.numero=t1.vertices[1].numero;
	}else{
		t1.angulos[1].grados=atan((m3-m1)/(1+m3*m1));
		t1.angulos[1].vertice_angulo.nodos.coordenadas[0]=t1.vertices[1].nodos.coordenadas[0];
		t1.angulos[1].vertice_angulo.nodos.coordenadas[1]=t1.vertices[1].nodos.coordenadas[1];
		t1.angulos[1].vertice_angulo.numero=t1.vertices[1].numero;
	}	
	//El pequeño error de aproximacion lo resolvemos dandole esos pequeños diferenciales de angulo al ultimo angulo
	t1.angulos[2].grados=180-(t1.angulos[1].grados+t1.angulos[0].grados);
	
	t1.angulos[2].vertice_angulo.nodos.coordenadas[0]=t1.vertices[0].nodos.coordenadas[0];
	t1.angulos[2].vertice_angulo.nodos.coordenadas[1]=t1.vertices[0].nodos.coordenadas[1];
	t1.angulos[2].vertice_angulo.numero=t1.vertices[0].numero;
}

//ELEMENTOS: DISTANCIA MAYOR, VERTICE OPUESTO ARISTA MAYOR, VERTICES QUE PASAN POR LA ARISTA MAYOR, PUNTO MEDIO
void elementos_mayores(t t1){
	//este vector retorna la distancia mayor y el punto opuesto a esta distancia
	//A=0, B=1, C=2
	float distancia_AB=distancia(t1.vertices[0].nodos,t1.vertices[1].nodos);
	float distancia_AC=distancia(t1.vertices[0].nodos,t1.vertices[2].nodos);
	float distancia_BC=distancia(t1.vertices[1].nodos,t1.vertices[2].nodos);
	if(distancia_AB > distancia_AC){
		if(distancia_AB > distancia_BC){
			t1.elemento_mayor.distancia_mayor=distancia_AB;
			//Los primeros son los puntos opuestos
			t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[0]=t1.vertices[2].nodos.coordenadas[0];
			t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[1]=t1.vertices[2].nodos.coordenadas[1];
			t1.elemento_mayor.vertice_opuesto.numero=t1.vertices[2].numero;

			//Estos son los dos vertices que pasan por la arista mayor
			t1.elemento_mayor.arista_mayor.vertices[0].nodos.coordenadas[0]=t1.vertices[0].nodos.coordenadas[0];
			t1.elemento_mayor.arista_mayor.vertices[0].nodos.coordenadas[1]=t1.vertices[0].nodos.coordenadas[1];
			t1.elemento_mayor.vertice_opuesto.numero=t1.vertices[0].numero;

			t1.elemento_mayor.arista_mayor.vertices[1].nodos.coordenadas[0]=t1.vertices[1].nodos.coordenadas[0];
			t1.elemento_mayor.arista_mayor.vertices[1].nodos.coordenadas[1]=t1.vertices[1].nodos.coordenadas[1];
			t1.elemento_mayor.vertice_opuesto.numero=t1.vertices[1].numero;

			t1.elemento_mayor.punto_medio.coordenadas[0]=punto_medio(t1.vertices[0].nodos,t1.vertices[1].nodos)[0];
			t1.elemento_mayor.punto_medio.coordenadas[1]=punto_medio(t1.vertices[0].nodos,t1.vertices[1].nodos)[1];

		}else{
			t1.elemento_mayor.distancia_mayor=distancia_BC;
			t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[0]=t1.vertices[0].nodos.coordenadas[0];
			t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[1]=t1.vertices[0].nodos.coordenadas[1];
			t1.elemento_mayor.vertice_opuesto.numero=t1.vertices[0].numero;

			t1.elemento_mayor.arista_mayor.vertices[0].nodos.coordenadas[0]=t1.vertices[1].nodos.coordenadas[0];
			t1.elemento_mayor.arista_mayor.vertices[0].nodos.coordenadas[1]=t1.vertices[1].nodos.coordenadas[1];
			t1.elemento_mayor.vertice_opuesto.numero=t1.vertices[1].numero;

			t1.elemento_mayor.arista_mayor.vertices[1].nodos.coordenadas[0]=t1.vertices[2].nodos.coordenadas[0];
			t1.elemento_mayor.arista_mayor.vertices[1].nodos.coordenadas[1]=t1.vertices[2].nodos.coordenadas[1];
			t1.elemento_mayor.vertice_opuesto.numero=t1.vertices[2].numero;

			t1.elemento_mayor.punto_medio.coordenadas[0]=punto_medio(t1.vertices[1].nodos,t1.vertices[2].nodos)[0];
			t1.elemento_mayor.punto_medio.coordenadas[1]=punto_medio(t1.vertices[1].nodos,t1.vertices[2].nodos)[1];
		}
	}else{
		if(distancia_AC > distancia_BC){
			t1.elemento_mayor.distancia_mayor=distancia_AC;
			t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[0]=t1.vertices[1].nodos.coordenadas[0];
			t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[1]=t1.vertices[1].nodos.coordenadas[1];
			t1.elemento_mayor.vertice_opuesto.numero=t1.vertices[1].numero;

			t1.elemento_mayor.arista_mayor.vertices[0].nodos.coordenadas[0]=t1.vertices[0].nodos.coordenadas[0];
			t1.elemento_mayor.arista_mayor.vertices[0].nodos.coordenadas[1]=t1.vertices[0].nodos.coordenadas[1];
			t1.elemento_mayor.vertice_opuesto.numero=t1.vertices[0].numero;

			t1.elemento_mayor.arista_mayor.vertices[1].nodos.coordenadas[0]=t1.vertices[2].nodos.coordenadas[0];
			t1.elemento_mayor.arista_mayor.vertices[1].nodos.coordenadas[1]=t1.vertices[2].nodos.coordenadas[1];
			t1.elemento_mayor.vertice_opuesto.numero=t1.vertices[2].numero;

			t1.elemento_mayor.punto_medio.coordenadas[0]=punto_medio(t1.vertices[0].nodos,t1.vertices[2].nodos)[0];
			t1.elemento_mayor.punto_medio.coordenadas[1]=punto_medio(t1.vertices[0].nodos,t1.vertices[2].nodos)[1];
		}else{
			t1.elemento_mayor.distancia_mayor=distancia_BC;
			t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[0]=t1.vertices[0].nodos.coordenadas[0];
			t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[1]=t1.vertices[0].nodos.coordenadas[1];
			t1.elemento_mayor.vertice_opuesto.numero=t1.vertices[0].numero;

			t1.elemento_mayor.arista_mayor.vertices[0].nodos.coordenadas[0]=t1.vertices[1].nodos.coordenadas[0];
			t1.elemento_mayor.arista_mayor.vertices[0].nodos.coordenadas[1]=t1.vertices[1].nodos.coordenadas[1];
			t1.elemento_mayor.vertice_opuesto.numero=t1.vertices[1].numero;

			t1.elemento_mayor.arista_mayor.vertices[1].nodos.coordenadas[0]=t1.vertices[2].nodos.coordenadas[0];
			t1.elemento_mayor.arista_mayor.vertices[1].nodos.coordenadas[1]=t1.vertices[2].nodos.coordenadas[1];
			t1.elemento_mayor.vertice_opuesto.numero=t1.vertices[2].numero;

			t1.elemento_mayor.punto_medio.coordenadas[0]=punto_medio(t1.vertices[1].nodos,t1.vertices[2].nodos)[0];
			t1.elemento_mayor.punto_medio.coordenadas[1]=punto_medio(t1.vertices[1].nodos,t1.vertices[2].nodos)[1];
		}
	}
}

void generar_aristas(t t1){
	t1.aristas[0].numero=1;
	t1.aristas[0].vertices[0].nodos.coordenadas[0]=t1.vertices[0].nodos.coordenadas[0];
	t1.aristas[0].vertices[0].nodos.coordenadas[1]=t1.vertices[0].nodos.coordenadas[1];
	t1.aristas[0].vertices[1].nodos.coordenadas[0]=t1.vertices[1].nodos.coordenadas[0];
	t1.aristas[0].vertices[1].nodos.coordenadas[1]=t1.vertices[1].nodos.coordenadas[1];

	t1.aristas[1].numero=2;
	t1.aristas[1].vertices[0].nodos.coordenadas[0]=t1.vertices[0].nodos.coordenadas[0];
	t1.aristas[1].vertices[0].nodos.coordenadas[1]=t1.vertices[0].nodos.coordenadas[1];
	t1.aristas[1].vertices[1].nodos.coordenadas[0]=t1.vertices[2].nodos.coordenadas[0];
	t1.aristas[1].vertices[1].nodos.coordenadas[1]=t1.vertices[2].nodos.coordenadas[1];
	
	t1.aristas[2].numero=3;
	t1.aristas[2].vertices[0].nodos.coordenadas[0]=t1.vertices[1].nodos.coordenadas[0];
	t1.aristas[2].vertices[0].nodos.coordenadas[1]=t1.vertices[1].nodos.coordenadas[1];
	t1.aristas[2].vertices[1].nodos.coordenadas[0]=t1.vertices[2].nodos.coordenadas[0];
	t1.aristas[2].vertices[1].nodos.coordenadas[1]=t1.vertices[2].nodos.coordenadas[1];
}

//t1=t2 y t2=t1 por medio de un auxiliar
void asignar_triangulo(t t1, t t2){
	t1.vertices[0].nodos.coordenadas[0]=t2.vertices[0].nodos.coordenadas[0];
	t1.vertices[0].nodos.coordenadas[1]=t2.vertices[0].nodos.coordenadas[1];
	t1.vertices[1].nodos.coordenadas[0]=t2.vertices[1].nodos.coordenadas[0];
	t1.vertices[1].nodos.coordenadas[1]=t2.vertices[1].nodos.coordenadas[1];
	t1.vertices[2].nodos.coordenadas[0]=t2.vertices[2].nodos.coordenadas[0];
	t1.vertices[2].nodos.coordenadas[1]=t2.vertices[2].nodos.coordenadas[1];
	//Los 3 angulos
	t1.angulos[0]=t2.angulos[0];
	t1.angulos[1]=t2.angulos[1];
	t1.angulos[2]=t2.angulos[2];
	//Arista 1
	t1.aristas[0].vertices[0].nodos.coordenadas[0]=t2.aristas[0].vertices[0].nodos.coordenadas[0];
	t1.aristas[0].vertices[0].nodos.coordenadas[1]=t2.aristas[0].vertices[0].nodos.coordenadas[1];
	t1.aristas[0].vertices[1].nodos.coordenadas[0]=t2.aristas[0].vertices[1].nodos.coordenadas[0];
	t1.aristas[0].vertices[1].nodos.coordenadas[1]=t2.aristas[0].vertices[1].nodos.coordenadas[1];
	//Arista 2
	t1.aristas[1].vertices[0].nodos.coordenadas[0]=t2.aristas[1].vertices[0].nodos.coordenadas[0];
	t1.aristas[1].vertices[0].nodos.coordenadas[1]=t2.aristas[1].vertices[0].nodos.coordenadas[1];
	t1.aristas[1].vertices[1].nodos.coordenadas[0]=t2.aristas[1].vertices[1].nodos.coordenadas[0];
	t1.aristas[1].vertices[1].nodos.coordenadas[1]=t2.aristas[1].vertices[1].nodos.coordenadas[1];
	//Arista 3
	t1.aristas[2].vertices[0].nodos.coordenadas[0]=t2.aristas[1].vertices[0].nodos.coordenadas[0];
	t1.aristas[2].vertices[0].nodos.coordenadas[1]=t2.aristas[1].vertices[0].nodos.coordenadas[1];
	t1.aristas[2].vertices[1].nodos.coordenadas[0]=t2.aristas[1].vertices[1].nodos.coordenadas[0];
	t1.aristas[2].vertices[1].nodos.coordenadas[1]=t2.aristas[1].vertices[1].nodos.coordenadas[1];

	t1.numero_triangulo=t2.numero_triangulo;

	t1.aristas[0].numero=t2.aristas[0].numero;
	t1.aristas[1].numero=t2.aristas[1].numero;
	t1.aristas[2].numero=t2.aristas[2].numero;
}

void llenado_malla(t malla[], char fichero[]){
 	FILE *archivo;;
 	char Elements[100][100];
 	char Nodes[100][100];
 	int Elements_enteros[150];
 	int j=0;
 	double num;
 	//char caracteres[100];
 	char string[50][50];
 	int contador=-1;
 	archivo = fopen(fichero,"r");
 	
 	if (archivo == NULL)
 		exit(1);
 	

 	//Recorremos el archivo
 	while (feof(archivo) == 0){
 		contador++;
 		fgets(string[contador],50,archivo);
 	}

        fclose(archivo);

    //Llenamos el vector caracteres, tiene contenido el fichero msh    
    for(int i=0;i<filas_fichero("malla_triangulacion.msh");i++){
    	if(equals(string[i],"$Elements")){
    		printf("Informacion de los ELEMENTOS vertices que le corresponden a cada triangulo\n");
    		i++;
    		while(equals(string[i],"$EndElements")==0){
    			//La siguiente linea de $Elements
    			while(j<50){
    				Elements[i][j]=string[i][j];
    				j++;
    			}
    			j=0;
    			i++;	
    		}
    		//printf("%s",string[i]);
    	}else{
    		if(equals(string[i],"$Nodes")){
    			printf("Informacion de los NODES, corresponde a los vertices enumerados\n");
    			i++;
    			while(equals(string[i],"$EndNodes")==0){
    			//La siguiente linea de $Elements
	    			while(j<50){
	    				Nodes[i][j]=string[i][j];
	    				j++;
	    			}
	    			j=0;
	    			i++;	
	    		}

    		}
    	}
    }

    for(int i=0;i<100;i++){
   			printf("%s",Nodes[i]);
   	}
   	for(int i=0;i<100;i++){
   			printf("%s",Elements[i]);
   	}

   	string_entero(Elements_enteros,Elements);

   	for(int i=0;i<150;i++){
   		printf("%d\n",Elements_enteros[i]);
   	}
   
}
