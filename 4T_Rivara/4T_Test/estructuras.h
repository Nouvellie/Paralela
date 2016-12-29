#include <stdio.h>

struct triangulos_afectados{
	int *t_afectados;
	int size;
};

struct punto{
	float coordenadas[2];
};

struct nodo{
	struct punto nodos;
	int numero;
};
struct angulo{
	struct nodo vertice_angulo;
	float grados;
};	
struct arista{
	int numero;
	struct nodo vertices[2];
};

struct arista_mayor_triangulo{
	float distancia_mayor;
	struct arista arista_mayor;
	struct punto punto_medio;
	struct nodo vertice_opuesto;
};

struct triangulo{
	struct nodo vertices[3];
	struct angulo angulos[3];
	int numero_triangulo;
	struct arista aristas[3];
	struct arista_mayor_triangulo elemento_mayor;
};
