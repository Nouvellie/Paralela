#include <stdio.h>
#define length(x) (sizeof(x)/sizeof(x[0]))

typedef struct triangulo t;
typedef struct punto p;

void angulo(float a, float b, float c,float *A, float *B, float *C)  {
    *C=acos((c*c-a*a-b*b)/(-2*a*b))*180;
    *A=acos((a*a-b*b-c*c)/(-2*b*c))*180;
    *B=acos((b*b-a*a-c*c)/(-2*a*c))*180;
}

//Saco la distancia entre dos puntos
float distancia(float x0,float y0,float x1,float y1) {
    float dist;
    dist=sqrt( (x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
    return dist;
}

//Distancia mayor
float *distancia_mayor(t t1){
	//este vector retorna la distancia mayor y el punto opuesto a esta distancia
	float *vector=malloc(7*sizeof(int));
	//A=0, B=1, C=2
	float distancia_AB=distancia(t1.vertices[0].coordenadas[0], t1.vertices[0].coordenadas[1],t1.vertices[1].coordenadas[0], t1.vertices[1].coordenadas[1]);
	float distancia_AC=distancia(t1.vertices[0].coordenadas[0], t1.vertices[0].coordenadas[1],t1.vertices[2].coordenadas[0], t1.vertices[2].coordenadas[1]);
	float distancia_BC=distancia(t1.vertices[1].coordenadas[0], t1.vertices[1].coordenadas[1],t1.vertices[2].coordenadas[0], t1.vertices[2].coordenadas[1]);
	if(distancia_AB > distancia_AC){
		if(distancia_AB > distancia_BC){
			vector[0]=distancia_AB;
			vector[1]=t1.vertices[2].coordenadas[0];
			vector[2]=t1.vertices[2].coordenadas[1];
			vector[3]=t1.vertices[0].coordenadas[0];
			vector[4]=t1.vertices[0].coordenadas[1];
			vector[5]=t1.vertices[1].coordenadas[0];
			vector[6]=t1.vertices[1].coordenadas[1];
			return vector;
		}else{
			vector[0]=distancia_BC;
			vector[1]=t1.vertices[0].coordenadas[0];
			vector[2]=t1.vertices[0].coordenadas[1];
			vector[3]=t1.vertices[1].coordenadas[0];
			vector[4]=t1.vertices[1].coordenadas[1];
			vector[5]=t1.vertices[2].coordenadas[0];
			vector[6]=t1.vertices[2].coordenadas[1];
			return vector;
		}
	}else{
		if(distancia_AC > distancia_BC){
			vector[0]=distancia_AC;
			vector[1]=t1.vertices[1].coordenadas[0];
			vector[2]=t1.vertices[1].coordenadas[1];
			vector[3]=t1.vertices[0].coordenadas[0];
			vector[4]=t1.vertices[0].coordenadas[1];
			vector[5]=t1.vertices[2].coordenadas[0];
			vector[6]=t1.vertices[2].coordenadas[1];
			return vector;
		}else{
			vector[0]=distancia_BC;
			vector[1]=t1.vertices[0].coordenadas[0];
			vector[2]=t1.vertices[0].coordenadas[1];
			vector[3]=t1.vertices[1].coordenadas[0];
			vector[4]=t1.vertices[1].coordenadas[1];
			vector[5]=t1.vertices[2].coordenadas[0];
			vector[6]=t1.vertices[2].coordenadas[1];
			return vector;
		}
	}
}

float *punto_medio(float x0, float y0, float x1, float y1){
	float *coordenadas=malloc(2*sizeof(int));
	coordenadas[0]=(float)((x0+x1))/2;
	coordenadas[1]=(float)((y0+y1))/2;
	return coordenadas;
}


int *aristas_no_mayores(t t1){
	int *aristas=malloc(2*sizeof(int));
	if(t1.aristas[0].numero == t1.elemento_mayor.arista_mayor.numero){
		//Las dos aristas siguientes no son la de las mayores distancias
		aristas[0]=1;
		aristas[1]=2;
		return aristas;
	}else{
		if(t1.aristas[1].numero==t1.elemento_mayor.arista_mayor.numero){
			aristas[0]=0;
			aristas[1]=2;
			return aristas;
		}else{
			if(t1.aristas[2].numero==t1.elemento_mayor.arista_mayor.numero){
				aristas[0]=0;
				aristas[1]=1;
				return aristas;
			}
		}
	}
}

float *vertices_no_mayores(t t1){
	float *vertices=malloc(4*sizeof(int));
	if(t1.vertices[0].coordenadas[0]==t1.elemento_mayor.vertice_opuesto.coordenadas[0] && t1.vertices[0].coordenadas[1]==t1.elemento_mayor.vertice_opuesto.coordenadas[1]){
		vertices[0]=t1.vertices[1].coordenadas[0];
		vertices[1]=t1.vertices[1].coordenadas[1];
		vertices[2]=t1.vertices[2].coordenadas[0];
		vertices[3]=t1.vertices[2].coordenadas[1];
		return vertices;
	}else{
		if(t1.vertices[1].coordenadas[0]==t1.elemento_mayor.vertice_opuesto.coordenadas[0] && t1.vertices[1].coordenadas[1]==t1.elemento_mayor.vertice_opuesto.coordenadas[1]){
			vertices[0]=t1.vertices[0].coordenadas[0];
			vertices[1]=t1.vertices[0].coordenadas[1];
			vertices[2]=t1.vertices[2].coordenadas[0];
			vertices[3]=t1.vertices[2].coordenadas[1];
			return vertices;
		}else{
			if(t1.vertices[2].coordenadas[0]==t1.elemento_mayor.vertice_opuesto.coordenadas[0] && t1.vertices[2].coordenadas[1]==t1.elemento_mayor.vertice_opuesto.coordenadas[1]){
				vertices[0]=t1.vertices[0].coordenadas[0];
				vertices[1]=t1.vertices[0].coordenadas[1];
				vertices[2]=t1.vertices[1].coordenadas[0];
				vertices[3]=t1.vertices[1].coordenadas[1];
				return vertices;
			}
		}
	}
}

void generar_triangulos_4T(t t1, t malla[]){
	//Agregamos un nuevo triangulo
	t t2,t3,t4,t5;
	p punto_medio_uno, punto_medio_dos;
	
	//Sacamos el punto medio de la primera arista no mayor esto seria un nuevo vertice
	punto_medio_uno.coordenadas[0]=punto_medio(t1.aristas[aristas_no_mayores(t1)[0]].vertices[0].coordenadas[0],t1.aristas[aristas_no_mayores(t1)[0]].vertices[0].coordenadas[1],t1.aristas[aristas_no_mayores(t1)[0]].vertices[1].coordenadas[0],t1.aristas[aristas_no_mayores(t1)[0]].vertices[1].coordenadas[1])[0];
	punto_medio_uno.coordenadas[1]=punto_medio(t1.aristas[aristas_no_mayores(t1)[0]].vertices[0].coordenadas[0],t1.aristas[aristas_no_mayores(t1)[0]].vertices[0].coordenadas[1],t1.aristas[aristas_no_mayores(t1)[0]].vertices[1].coordenadas[0],t1.aristas[aristas_no_mayores(t1)[0]].vertices[1].coordenadas[1])[1];
	
	punto_medio_dos.coordenadas[0]=punto_medio(t1.aristas[aristas_no_mayores(t1)[1]].vertices[0].coordenadas[0],t1.aristas[aristas_no_mayores(t1)[1]].vertices[0].coordenadas[1],t1.aristas[aristas_no_mayores(t1)[1]].vertices[1].coordenadas[0],t1.aristas[aristas_no_mayores(t1)[1]].vertices[1].coordenadas[1])[0];
	punto_medio_dos.coordenadas[1]=punto_medio(t1.aristas[aristas_no_mayores(t1)[1]].vertices[0].coordenadas[0],t1.aristas[aristas_no_mayores(t1)[1]].vertices[0].coordenadas[1],t1.aristas[aristas_no_mayores(t1)[1]].vertices[1].coordenadas[0],t1.aristas[aristas_no_mayores(t1)[1]].vertices[1].coordenadas[1])[1];

	//Generando vertices primeramente
	t2.vertices[0].coordenadas[0]=vertices_no_mayores(t1)[0];
	t2.vertices[0].coordenadas[1]=vertices_no_mayores(t1)[1];
	t2.vertices[2].coordenadas[0]=t1.elemento_mayor.punto_medio.coordenadas[0];
	t2.vertices[2].coordenadas[0]=t1.elemento_mayor.punto_medio.coordenadas[1];
	if(ecuacion_recta(t2.vertices[0], t1.elemento_mayor.vertice_opuesto, punto_medio_uno)==1){
		t2.vertices[1].coordenadas[0]=punto_medio_uno.coordenadas[0];
		t2.vertices[1].coordenadas[1]=punto_medio_uno.coordenadas[1];
	}else{
		t2.vertices[1].coordenadas[0]=punto_medio_dos.coordenadas[0];
		t2.vertices[1].coordenadas[1]=punto_medio_dos.coordenadas[1];
	}

	t5.vertices[0].coordenadas[0]=vertices_no_mayores(t1)[2];
	t5.vertices[0].coordenadas[1]=vertices_no_mayores(t1)[3];
	t5.vertices[2].coordenadas[0]=t1.elemento_mayor.punto_medio.coordenadas[0];
	t5.vertices[2].coordenadas[0]=t1.elemento_mayor.punto_medio.coordenadas[1];
	if(ecuacion_recta(t5.vertices[0], t1.elemento_mayor.vertice_opuesto, punto_medio_uno)==1){
		t5.vertices[1].coordenadas[0]=punto_medio_uno.coordenadas[0];
		t5.vertices[1].coordenadas[1]=punto_medio_uno.coordenadas[1];
	}else{
		t5.vertices[1].coordenadas[0]=punto_medio_dos.coordenadas[0];
		t5.vertices[1].coordenadas[1]=punto_medio_dos.coordenadas[1];
	}

	t3.vertices[0].coordenadas[0]=t1.elemento_mayor.punto_medio.coordenadas[0];
	t3.vertices[0].coordenadas[1]=t1.elemento_mayor.punto_medio.coordenadas[1];
	t3.vertices[1].coordenadas[0]=t1.elemento_mayor.vertice_opuesto.coordenadas[0];
	t3.vertices[1].coordenadas[1]=t1.elemento_mayor.vertice_opuesto.coordenadas[1];
	t3.vertices[2].coordenadas[0]=punto_medio_uno.coordenadas[0];
	t3.vertices[2].coordenadas[1]=punto_medio_uno.coordenadas[1];

	t4.vertices[0].coordenadas[0]=t1.elemento_mayor.punto_medio.coordenadas[0];
	t4.vertices[0].coordenadas[1]=t1.elemento_mayor.punto_medio.coordenadas[1];
	t4.vertices[1].coordenadas[0]=t1.elemento_mayor.vertice_opuesto.coordenadas[0];
	t4.vertices[1].coordenadas[1]=t1.elemento_mayor.vertice_opuesto.coordenadas[1];
	t4.vertices[2].coordenadas[0]=punto_medio_dos.coordenadas[0];
	t4.vertices[2].coordenadas[1]=punto_medio_dos.coordenadas[1];



	//Generamos las angulos
	generar_angulos(t2);
	generar_angulos(t3);
	generar_angulos(t4);
	generar_angulos(t5);

	//Generamos las aristas
	generar_aristas(t2);
	generar_aristas(t3);
	generar_aristas(t4);
	generar_aristas(t5);
	//Generamos los numeros de triangulo y aristas
	//length es el tamaño de la malla, le agregamos los elementos nuevos y le restamos el triangulo que se bisecciono
	//Reajustamos el tamaño del vector dinamico
	espaciar_vector(malla, 3, t1.numero_triangulo);
	malla=realloc(malla,sizeof(int)*(length(malla)+3));
	for(int i=0; i< length(malla)+3;i++){
		malla[i].numero_triangulo=i+1;
		if(malla[i].numero_triangulo == i+1){
			//En esta posicion estaba anteriormente el triangulo que se bisecciono
			asignar_triangulo(malla[i],t2);
			//t3, t4 y t5 se encuentran los triangulos que vienen al que se bisecciono
			asignar_triangulo(malla[i+1],t3);
			asignar_triangulo(malla[i+2],t4);
			asignar_triangulo(malla[i+3],t5);
			malla[i].numero_triangulo=i+1;
			malla[i+1].numero_triangulo=i+2;
			malla[i+2].numero_triangulo=i+3;
			malla[i+3].numero_triangulo=i+4;
			i=i+4;
		}
	}
	
}

void llenar_triangulos_mayor(t t1){
	t1.elemento_mayor.distancia_mayor=distancia_mayor(t1)[0];
	t1.elemento_mayor.vertice_opuesto.coordenadas[0]=distancia_mayor(t1)[1];
	t1.elemento_mayor.vertice_opuesto.coordenadas[1]=distancia_mayor(t1)[2];

	//Declarar cual es la arista mayor t1.elemento_mayor.arista_mayor.numero=
	t1.elemento_mayor.arista_mayor.vertices[0].coordenadas[0]=distancia_mayor(t1)[3];
	t1.elemento_mayor.arista_mayor.vertices[0].coordenadas[1]=distancia_mayor(t1)[4];
	t1.elemento_mayor.arista_mayor.vertices[1].coordenadas[0]=distancia_mayor(t1)[5];
	t1.elemento_mayor.arista_mayor.vertices[1].coordenadas[1]=distancia_mayor(t1)[6];

	//Debemos agregar este punto a la malla
	t1.elemento_mayor.punto_medio.coordenadas[0]=punto_medio(t1.elemento_mayor.arista_mayor.vertices[0].coordenadas[0],t1.elemento_mayor.arista_mayor.vertices[0].coordenadas[1],t1.elemento_mayor.arista_mayor.vertices[1].coordenadas[0],t1.elemento_mayor.arista_mayor.vertices[1].coordenadas[1])[0];
	t1.elemento_mayor.punto_medio.coordenadas[1]=punto_medio(t1.elemento_mayor.arista_mayor.vertices[0].coordenadas[0],t1.elemento_mayor.arista_mayor.vertices[0].coordenadas[1],t1.elemento_mayor.arista_mayor.vertices[1].coordenadas[0],t1.elemento_mayor.arista_mayor.vertices[1].coordenadas[1])[1];
}

//Retorna si el punto pertenece z o no a la recta formada por x e y
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

void generar_angulos(t t1){
	float m1=(t1.vertices[0].coordenadas[1]-t1.vertices[1].coordenadas[1])/(t1.vertices[0].coordenadas[0]-t1.vertices[1].coordenadas[0]);
	float m2=(t1.vertices[0].coordenadas[1]-t1.vertices[2].coordenadas[1])/(t1.vertices[0].coordenadas[0]-t1.vertices[2].coordenadas[0]);
	float m3=(t1.vertices[1].coordenadas[1]-t1.vertices[2].coordenadas[1])/(t1.vertices[1].coordenadas[0]-t1.vertices[2].coordenadas[0]);
	
	//Verificamos que los angulos sean positivos debe haber un peque;o error de angulos
	if(atan((m2-m1)/(1+m2*m1))<0){
		t1.angulos[0]=-1*atan((m2-m1)/(1+m2*m1));
	}else{
		t1.angulos[0]=atan((m2-m1)/(1+m2*m1));
	}
	
	if(atan((m3-m1)/(1+m3*m1))<0){
		t1.angulos[1]=-1*atan((m3-m1)/(1+m3*m1));
	}else{
		t1.angulos[1]=atan((m3-m1)/(1+m3*m1));
	}	
	//El pequeño error de aproximacion lo resolvemos dandole esos pequeños diferenciales de angulo al ultimo angulo
	t1.angulos[2]=180-(t1.angulos[1]+t1.angulos[0]);
}

void generar_aristas(t t1){
	t1.aristas[0].numero=1;
	t1.aristas[0].vertices[0].coordenadas[0]=t1.vertices[0].coordenadas[0];
	t1.aristas[0].vertices[0].coordenadas[1]=t1.vertices[0].coordenadas[1];
	t1.aristas[0].vertices[1].coordenadas[0]=t1.vertices[1].coordenadas[0];
	t1.aristas[0].vertices[1].coordenadas[1]=t1.vertices[1].coordenadas[1];

	t1.aristas[1].numero=2;
	t1.aristas[1].vertices[0].coordenadas[0]=t1.vertices[0].coordenadas[0];
	t1.aristas[1].vertices[0].coordenadas[1]=t1.vertices[0].coordenadas[1];
	t1.aristas[1].vertices[1].coordenadas[0]=t1.vertices[2].coordenadas[0];
	t1.aristas[1].vertices[1].coordenadas[1]=t1.vertices[2].coordenadas[1];
	
	t1.aristas[2].numero=3;
	t1.aristas[2].vertices[0].coordenadas[0]=t1.vertices[1].coordenadas[0];
	t1.aristas[2].vertices[0].coordenadas[1]=t1.vertices[1].coordenadas[1];
	t1.aristas[2].vertices[1].coordenadas[0]=t1.vertices[2].coordenadas[0];
	t1.aristas[2].vertices[1].coordenadas[1]=t1.vertices[2].coordenadas[1];
}

//t1=t2 y t2=t1 por medio de un auxiliar
void asignar_triangulo(t t1, t t2){
	t1.vertices[0].coordenadas[0]=t2.vertices[0].coordenadas[0];
	t1.vertices[0].coordenadas[1]=t2.vertices[0].coordenadas[1];
	t1.vertices[1].coordenadas[0]=t2.vertices[1].coordenadas[0];
	t1.vertices[1].coordenadas[1]=t2.vertices[1].coordenadas[1];
	t1.vertices[2].coordenadas[0]=t2.vertices[2].coordenadas[0];
	t1.vertices[2].coordenadas[1]=t2.vertices[2].coordenadas[1];
	//Los 3 angulos
	t1.angulos[0]=t2.angulos[0];
	t1.angulos[1]=t2.angulos[1];
	t1.angulos[2]=t2.angulos[2];
	//Arista 1
	t1.aristas[0].vertices[0].coordenadas[0]=t2.aristas[0].vertices[0].coordenadas[0];
	t1.aristas[0].vertices[0].coordenadas[1]=t2.aristas[0].vertices[0].coordenadas[1];
	t1.aristas[0].vertices[1].coordenadas[0]=t2.aristas[0].vertices[1].coordenadas[0];
	t1.aristas[0].vertices[1].coordenadas[1]=t2.aristas[0].vertices[1].coordenadas[1];
	//Arista 2
	t1.aristas[1].vertices[0].coordenadas[0]=t2.aristas[1].vertices[0].coordenadas[0];
	t1.aristas[1].vertices[0].coordenadas[1]=t2.aristas[1].vertices[0].coordenadas[1];
	t1.aristas[1].vertices[1].coordenadas[0]=t2.aristas[1].vertices[1].coordenadas[0];
	t1.aristas[1].vertices[1].coordenadas[1]=t2.aristas[1].vertices[1].coordenadas[1];
	//Arista 3
	t1.aristas[2].vertices[0].coordenadas[0]=t2.aristas[1].vertices[0].coordenadas[0];
	t1.aristas[2].vertices[0].coordenadas[1]=t2.aristas[1].vertices[0].coordenadas[1];
	t1.aristas[2].vertices[1].coordenadas[0]=t2.aristas[1].vertices[1].coordenadas[0];
	t1.aristas[2].vertices[1].coordenadas[1]=t2.aristas[1].vertices[1].coordenadas[1];

	t1.numero_triangulo=t2.numero_triangulo;

	t1.aristas[0].numero=t2.aristas[0].numero;
	t1.aristas[1].numero=t2.aristas[1].numero;
	t1.aristas[2].numero=t2.aristas[2].numero;
}

void espaciar_vector(t malla[],int espacio, int num_triangulo){
	t *malla_dos=malloc(sizeof(int)*(length(malla)));
	t t_vacio;
	constructor_triangulo(t_vacio);
	//Llenamos la malla_dos con los datos de la malla original, ahora haremos lo mismo, pero dandole el espaciamiento
	for(int i=0; i< length(malla);i++){
		asignar_triangulo(malla_dos[i],malla[i]);
	}

	for(int i=0; i< length(malla)+espacio;i++){
		if(num_triangulo <= i+1 && i+1 <= num_triangulo+espacio){
			asignar_triangulo(malla[i],t_vacio);
		}else{
			if(num_triangulo+espacio < i+1 ){
				asignar_triangulo(malla[i],malla_dos[i-espacio]);
			}
		}
	}

}


void llenar_malla(t malla[]){
	
}
