#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct triangulo t;
typedef struct punto p;
typedef struct arista arist;

//FALTA ASIGNAR EL NUMERO DEL VERTICE AL PUNTO MEDIO DE LA ARISTA MODIFICADA, SOBRE ESCRIBIR EL ARCHIVO Y AGREGAR ESA LINEA, PARA LEERLA POSTERIORMENTE

/*************************	METODOS CALCULAR *************************/

int *ordenar_vertices(int v1, int v2, int v3){
	int *v=malloc(sizeof(int)*3);
	int list[3]={v1,v2,v3};
	long c, d, t;

  	for (c=0;c < 2;c++)
  	{
    	for (d = 0 ; d < 3 - c - 1; d++)
    	{
      		if (list[d] > list[d+1])
      		{
        		t         = list[d];
        		list[d]   = list[d+1];
        		list[d+1] = t;
      		}
    	}
  	}
  	for(int i=0;i<3;i++){
  		v[i]=list[i];
  	}
	return v;
}

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

float *angulo(float a, float b, float c)  {
	float *ang=malloc(sizeof(int)*3);
    ang[0]=acos((c*c-a*a-b*b)/(-2*a*b))*180/3.14;
    ang[1]=acos((a*a-b*b-c*c)/(-2*b*c))*180/3.14;
    ang[2]=acos((b*b-a*a-c*c)/(-2*a*c))*180/3.14;

    return ang;
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
			}else{
				return aristas;
			}
		}
	}
}

float *vertices_no_mayores(t t1){
	float *vertices=malloc(4*sizeof(int));
	if(t1.vertices[0].nodos.coordenadas[0]==t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[0] && t1.vertices[0].nodos.coordenadas[1]==t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[1]){
		vertices[0]=t1.vertices[1].nodos.coordenadas[0];
		vertices[1]=t1.vertices[1].nodos.coordenadas[1];
		vertices[2]=t1.vertices[2].nodos.coordenadas[0];
		vertices[3]=t1.vertices[2].nodos.coordenadas[1];
		return vertices;
	}else{
		if(t1.vertices[1].nodos.coordenadas[0]==t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[0] && t1.vertices[1].nodos.coordenadas[1]==t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[1]){
			vertices[0]=t1.vertices[0].nodos.coordenadas[0];
			vertices[1]=t1.vertices[0].nodos.coordenadas[1];
			vertices[2]=t1.vertices[2].nodos.coordenadas[0];
			vertices[3]=t1.vertices[2].nodos.coordenadas[1];
			return vertices;
		}else{
			if(t1.vertices[2].nodos.coordenadas[0]==t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[0] && t1.vertices[2].nodos.coordenadas[1]==t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[1]){
				vertices[0]=t1.vertices[0].nodos.coordenadas[0];
				vertices[1]=t1.vertices[0].nodos.coordenadas[1];
				vertices[2]=t1.vertices[1].nodos.coordenadas[0];
				vertices[3]=t1.vertices[1].nodos.coordenadas[1];
				return vertices;
			}
		}
	}
}

/*************************	GENERADORES *************************/

void generar_angulos(t t1){
	t1.angulos[0].grados=angulo(distancia(t1.vertices[0].nodos,t1.vertices[1].nodos),distancia(t1.vertices[0].nodos,t1.vertices[2].nodos),distancia(t1.vertices[1].nodos,t1.vertices[2].nodos))[0];
	t1.angulos[1].grados=angulo(distancia(t1.vertices[0].nodos,t1.vertices[1].nodos),distancia(t1.vertices[0].nodos,t1.vertices[2].nodos),distancia(t1.vertices[1].nodos,t1.vertices[2].nodos))[1];
	t1.angulos[2].grados=angulo(distancia(t1.vertices[0].nodos,t1.vertices[1].nodos),distancia(t1.vertices[0].nodos,t1.vertices[2].nodos),distancia(t1.vertices[1].nodos,t1.vertices[2].nodos))[2];
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
	t1.aristas[1].vertices[0].nodos.coordenadas[0]=t1.vertices[1].nodos.coordenadas[0];
	t1.aristas[1].vertices[0].nodos.coordenadas[1]=t1.vertices[1].nodos.coordenadas[1];
	t1.aristas[1].vertices[1].nodos.coordenadas[0]=t1.vertices[2].nodos.coordenadas[0];
	t1.aristas[1].vertices[1].nodos.coordenadas[1]=t1.vertices[2].nodos.coordenadas[1];

	t1.aristas[2].numero=3;
	t1.aristas[2].vertices[0].nodos.coordenadas[0]=t1.vertices[0].nodos.coordenadas[0];
	t1.aristas[2].vertices[0].nodos.coordenadas[1]=t1.vertices[0].nodos.coordenadas[1];
	t1.aristas[2].vertices[1].nodos.coordenadas[0]=t1.vertices[2].nodos.coordenadas[0];
	t1.aristas[2].vertices[1].nodos.coordenadas[1]=t1.vertices[2].nodos.coordenadas[1];
}


void generar_triangulos_4T(t t1, t malla[]){
	//Agregamos un nuevo triangulo
	t t2,t3,t4,t5;
	p punto_medio_uno, punto_medio_dos;

	elementos_mayores(t1);

	//Generar elementos mayores
	punto_medio_uno.coordenadas[0]=punto_medio(t1.aristas[aristas_no_mayores(t1)[0]].vertices[0].nodos,t1.aristas[aristas_no_mayores(t1)[0]].vertices[1].nodos)[0];
	punto_medio_uno.coordenadas[1]=punto_medio(t1.aristas[aristas_no_mayores(t1)[0]].vertices[0].nodos,t1.aristas[aristas_no_mayores(t1)[0]].vertices[1].nodos)[1];

	punto_medio_dos.coordenadas[0]=punto_medio(t1.aristas[aristas_no_mayores(t1)[1]].vertices[0].nodos,t1.aristas[aristas_no_mayores(t1)[1]].vertices[1].nodos)[0];
	punto_medio_dos.coordenadas[1]=punto_medio(t1.aristas[aristas_no_mayores(t1)[1]].vertices[0].nodos,t1.aristas[aristas_no_mayores(t1)[1]].vertices[1].nodos)[1];


	//ENTRAN 3 PUNTOS AL ARCHIVO NODE: LOS 2 PUNTOS MEDIOS DE LAS ARISTAS NO MAYORES Y EL PUNTO MEDIO DE LA ARISTA MAYOR

	agregar_vertice_node(punto_medio_uno);
	agregar_vertice_node(punto_medio_dos);
	agregar_vertice_node(t1.elemento_mayor.punto_medio);

	t2.vertices[0].nodos.coordenadas[0]=vertices_no_mayores(t1)[0];
	t2.vertices[0].nodos.coordenadas[1]=vertices_no_mayores(t1)[1];
	t2.vertices[2].nodos.coordenadas[0]=t1.elemento_mayor.punto_medio.coordenadas[0];
	t2.vertices[2].nodos.coordenadas[0]=t1.elemento_mayor.punto_medio.coordenadas[1];

	/*
		PREGUNTO SI EL VERTICE PUNTO_MEDIO_UNO -SERIA EL PUNTO MEDIO DE UNA DE LAS ARISTAS NO MAYORES- PASA POR LA
		RECTA GENERADA POR EL VERTICE 1 DEL TRIANGULO T2 Y EL VERTICE DEL PUNTO MEDIO DE LA ARISTA MAYOR
	*/
	if(ecuacion_recta(t2.vertices[0].nodos, t1.elemento_mayor.vertice_opuesto.nodos, punto_medio_uno)==1){
		t2.vertices[1].nodos.coordenadas[0]=punto_medio_uno.coordenadas[0];
		t2.vertices[1].nodos.coordenadas[1]=punto_medio_uno.coordenadas[1];
	}else{
		t2.vertices[1].nodos.coordenadas[0]=punto_medio_dos.coordenadas[0];
		t2.vertices[1].nodos.coordenadas[1]=punto_medio_dos.coordenadas[1];
	}

	t5.vertices[0].nodos.coordenadas[0]=vertices_no_mayores(t1)[2];
	t5.vertices[0].nodos.coordenadas[1]=vertices_no_mayores(t1)[3];
	t5.vertices[2].nodos.coordenadas[0]=t1.elemento_mayor.punto_medio.coordenadas[0];
	t5.vertices[2].nodos.coordenadas[0]=t1.elemento_mayor.punto_medio.coordenadas[1];
	if(ecuacion_recta(t5.vertices[0].nodos, t1.elemento_mayor.vertice_opuesto.nodos, punto_medio_uno)==1){
		t5.vertices[1].nodos.coordenadas[0]=punto_medio_uno.coordenadas[0];
		t5.vertices[1].nodos.coordenadas[1]=punto_medio_uno.coordenadas[1];
	}else{
		t5.vertices[1].nodos.coordenadas[0]=punto_medio_dos.coordenadas[0];
		t5.vertices[1].nodos.coordenadas[1]=punto_medio_dos.coordenadas[1];
	}

	t3.vertices[0].nodos.coordenadas[0]=t1.elemento_mayor.punto_medio.coordenadas[0];
	t3.vertices[0].nodos.coordenadas[1]=t1.elemento_mayor.punto_medio.coordenadas[1];
	t3.vertices[1].nodos.coordenadas[0]=t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[0];
	t3.vertices[1].nodos.coordenadas[1]=t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[1];
	t3.vertices[2].nodos.coordenadas[0]=punto_medio_uno.coordenadas[0];
	t3.vertices[2].nodos.coordenadas[1]=punto_medio_uno.coordenadas[1];

	t4.vertices[0].nodos.coordenadas[0]=t1.elemento_mayor.punto_medio.coordenadas[0];
	t4.vertices[0].nodos.coordenadas[1]=t1.elemento_mayor.punto_medio.coordenadas[1];
	t4.vertices[1].nodos.coordenadas[0]=t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[0];
	t4.vertices[1].nodos.coordenadas[1]=t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[1];
	t4.vertices[2].nodos.coordenadas[0]=punto_medio_dos.coordenadas[0];
	t4.vertices[2].nodos.coordenadas[1]=punto_medio_dos.coordenadas[1];

	eliminar_triangulo_ele(t1.numero_triangulo, malla);
	agregar_triangulo_ele(t2);
	agregar_triangulo_ele(t3);
	agregar_triangulo_ele(t4);
	agregar_triangulo_ele(t5);

	//Se vuelve a generar la malla
	//DBERIA HABER UNA FUNCION, QUE SOLO ME CALCULE LOS DATOS DE LOS TRIANGULOS NUEVOS

	llenado_malla(malla);
}

void generar_triangulo_biseccion(t t1, t malla[]){
	t t2,t3;
	p punto_medio;

	elementos_mayores(t1);

	agregar_vertice_node(t1.elemento_mayor.punto_medio);

	t2.vertices[0].nodos.coordenadas[0]=t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[0];
	t2.vertices[0].nodos.coordenadas[1]=t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[1];

	t2.vertices[1].nodos.coordenadas[0]=t1.elemento_mayor.punto_medio.coordenadas[0];
	t2.vertices[1].nodos.coordenadas[1]=t1.elemento_mayor.punto_medio.coordenadas[1];

	t2.vertices[2].nodos.coordenadas[0]=vertices_no_mayores(t1)[0];
	t2.vertices[2].nodos.coordenadas[1]=vertices_no_mayores(t1)[1];

	t3.vertices[0].nodos.coordenadas[0]=t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[0];
	t3.vertices[0].nodos.coordenadas[1]=t1.elemento_mayor.vertice_opuesto.nodos.coordenadas[1];

	t3.vertices[1].nodos.coordenadas[0]=t1.elemento_mayor.punto_medio.coordenadas[0];
	t3.vertices[1].nodos.coordenadas[1]=t1.elemento_mayor.punto_medio.coordenadas[1];

	t3.vertices[2].nodos.coordenadas[0]=vertices_no_mayores(t1)[2];
	t3.vertices[2].nodos.coordenadas[1]=vertices_no_mayores(t1)[3];

	eliminar_triangulo_ele(t1.numero_triangulo, malla);
	agregar_triangulo_ele(t2);
	agregar_triangulo_ele(t3);

	llenado_malla(malla);


}

int triangulo_conforme(t t1){
	p pm_arista_uno,pm_arista_dos,pm_arista_tres;
	int size_node=tamano_node();
	int numero_vertice[size_node];
	float x_vertice[size_node],y_vertice[size_node];

	lectura_node(&numero_vertice,&x_vertice,&y_vertice);

	pm_arista_uno.coordenadas[0]=punto_medio(t1.aristas[0].vertices[0].nodos,t1.aristas[0].vertices[1].nodos)[0];
	pm_arista_uno.coordenadas[1]=punto_medio(t1.aristas[0].vertices[0].nodos,t1.aristas[0].vertices[1].nodos)[1];

	pm_arista_dos.coordenadas[0]=punto_medio(t1.aristas[1].vertices[0].nodos,t1.aristas[1].vertices[1].nodos)[0];
	pm_arista_dos.coordenadas[1]=punto_medio(t1.aristas[1].vertices[0].nodos,t1.aristas[1].vertices[1].nodos)[1];

	pm_arista_tres.coordenadas[0]=punto_medio(t1.aristas[2].vertices[0].nodos,t1.aristas[2].vertices[1].nodos)[0];
	pm_arista_tres.coordenadas[1]=punto_medio(t1.aristas[2].vertices[0].nodos,t1.aristas[2].vertices[1].nodos)[1];

	for(int i=0;i<size_node;i++){
		if((pm_arista_uno.coordenadas[0]==x_vertice[i] && pm_arista_uno.coordenadas[1]==y_vertice[i]) || (pm_arista_dos.coordenadas[0]==x_vertice[i] && pm_arista_dos.coordenadas[1]==y_vertice[i]) || (pm_arista_tres.coordenadas[0]==x_vertice[i] && pm_arista_tres.coordenadas[1]==y_vertice[i])){
			return 0;
		}
	}

	return 1;

}

void conformidad_iterativo(t malla[]){
	int size_ele=tamano_ele();
	for(int i=0;i<size_ele;i++){
		//Verificamos si el triangulo no es conforme
		if(triangulo_conforme(malla[i])==0){
			generar_triangulo_biseccion(malla[i], malla);
			//arranca de 0 la iteracion, ya que hay que verificar los triangulos por fichero
			i=-1;
		}
	}
}

void refinamiento(float angulo_limite, t malla[]){
	int size_ele=tamano_ele();
	int triangulos_refinar[size_ele];

	criterio_refinamiento(triangulos_refinar,angulo_limite,malla);

	for(int i=0;i<size_ele;i++){
		//RECORRO LA LISTA DE TRIANGULOS QUE TENGAN EL NUMERO DE UN TRIANGULO A REFINAR, SI ES ASI LO REFINO Y MODIFICO LA MALLA
		for(int j=0;j<size_ele;j++){
			if(triangulos_refinar[j] == malla[i].numero_triangulo){
				//MOMENTO EPICO
				generar_triangulos_4T(malla[i], malla);
				conformidad_iterativo(malla);
				i=-1;
			}
		}
	}
}

void criterio_refinamiento(int triangulos_refinar[], float angulo_limite, t malla[]){
	int size_ele=tamano_ele();

	for(int i=0;i<size_ele;i++){
		if((malla[i].angulos[0].grados < angulo_limite) || (malla[i].angulos[1].grados < angulo_limite) || (malla[i].angulos[2].grados < angulo_limite)){
			triangulos_refinar[i]=malla[i].numero_triangulo;
		}else{
			triangulos_refinar[i]=0;
		}
	}
}

//Incompleto, solo he generado una matriz y asignar los elementos
void llenado_malla(t malla[]){
	int size_node=tamano_node(), size_ele=tamano_ele();
	int numero_vertice[size_node];
	float x_vertice[size_node],y_vertice[size_node];

	int numero_triangulo[size_ele], vertice_uno[size_ele], vertice_dos[size_ele],vertice_tres[size_ele];


	lectura_node(&numero_vertice,&x_vertice,&y_vertice);
	lectura_ele(&numero_triangulo,&vertice_uno,&vertice_dos,&vertice_tres);

	for(int i=0;i<size_ele;i++){
		malla[i].vertices[0].numero=ordenar_vertices(vertice_uno[i],vertice_dos[i],vertice_tres[i])[0];
		malla[i].vertices[1].numero=ordenar_vertices(vertice_uno[i],vertice_dos[i],vertice_tres[i])[1];
		malla[i].vertices[2].numero=ordenar_vertices(vertice_uno[i],vertice_dos[i],vertice_tres[i])[2];

		malla[i].vertices[0].nodos.coordenadas[0]=x_vertice[malla[i].vertices[0].numero-1];
		malla[i].vertices[0].nodos.coordenadas[1]=y_vertice[malla[i].vertices[0].numero-1];

		malla[i].vertices[1].nodos.coordenadas[0]=x_vertice[malla[i].vertices[1].numero-1];
		malla[i].vertices[1].nodos.coordenadas[1]=y_vertice[malla[i].vertices[1].numero-1];

		malla[i].vertices[2].nodos.coordenadas[0]=x_vertice[malla[i].vertices[2].numero-1];
		malla[i].vertices[2].nodos.coordenadas[1]=y_vertice[malla[i].vertices[2].numero-1];

		generar_angulos(malla[i]);


		malla[i].numero_triangulo=numero_triangulo[i];

		generar_aristas(malla[i]);

		printf("Angulos: %d %f %f %f\n",malla[i].numero_triangulo,malla[i].angulos[0].grados,malla[i].angulos[1].grados,malla[i].angulos[2].grados);

		printf("%d %d %d %d\n",malla[i].numero_triangulo,malla[i].vertices[0].numero,malla[i].vertices[1].numero, malla[i].vertices[2].numero);

		//printf("%d %f %f %f\n\n", malla[i].numero_triangulo, malla[i].angulos[0].grados, malla[i].angulos[1].grados, malla[i].angulos[2].grados);
		//printf("%f %f %f\n\n\n\n", distancia(malla[i].vertices[0].nodos,malla[i].vertices[1].nodos),distancia(malla[i].vertices[0].nodos,malla[i].vertices[2].nodos),distancia(malla[i].vertices[1].nodos,malla[i].vertices[2].nodos));
	}

	/*for(int i=0;i<size_ele;i++){
		printf("%d %d %d %d\n",malla[i].numero_triangulo,malla[i].vertices[0].numero,malla[i].vertices[1].numero, malla[i].vertices[2].numero);
	}*/


}
