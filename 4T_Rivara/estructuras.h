#include <stdio.h>

struct punto{
	float coordenadas[2];
};

struct arista{
	int numero;
	struct punto vertices[2];
};

struct arista_mayor_triangulo{
	float distancia_mayor;
	struct arista arista_mayor;
	struct punto punto_medio;
	struct punto vertice_opuesto;
};

struct elementos_adyacentes{
	struct arista arista_adyacente[3];
	int triangulos_adyacentes[3];
};

struct triangulo{
	struct punto vertices[3];
	float angulos[3];
	int numero_triangulo;
	struct arista aristas[3];
	struct arista_mayor_triangulo elemento_mayor;
	struct elementos_adyacentes elemento_adyacente;
};
typedef struct triangulo t;

void constructor_triangulo(t t0){
	t0.vertices[0].coordenadas[0]=0;
	t0.vertices[0].coordenadas[1]=0;
	t0.vertices[1].coordenadas[0]=0;
	t0.vertices[1].coordenadas[1]=0;
	t0.vertices[2].coordenadas[0]=0;
	t0.vertices[2].coordenadas[1]=0;
	//Los 3 angulos
	t0.angulos[0]=0;
	t0.angulos[1]=0;
	t0.angulos[2]=0;
	//Arista 1
	t0.aristas[0].vertices[0].coordenadas[0]=0;
	t0.aristas[0].vertices[0].coordenadas[1]=0;
	t0.aristas[0].vertices[1].coordenadas[0]=0;
	t0.aristas[0].vertices[1].coordenadas[1]=0;
	//Arista 2
	t0.aristas[1].vertices[0].coordenadas[0]=0;
	t0.aristas[1].vertices[0].coordenadas[1]=0;
	t0.aristas[1].vertices[1].coordenadas[0]=0;
	t0.aristas[1].vertices[1].coordenadas[1]=0;
	//Arista 3
	t0.aristas[2].vertices[0].coordenadas[0]=0;
	t0.aristas[2].vertices[0].coordenadas[1]=0;
	t0.aristas[2].vertices[1].coordenadas[0]=0;
	t0.aristas[2].vertices[1].coordenadas[1]=0;

	t0.numero_triangulo=0;

	t0.aristas[0].numero=1;
	t0.aristas[1].numero=2;
	t0.aristas[2].numero=3;
}
