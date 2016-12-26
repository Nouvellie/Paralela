#include <stdio.h>

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

struct elementos_adyacentes{
	struct arista arista_adyacente[3];
	int triangulos_adyacentes[3];
};

struct triangulo{
	struct nodo vertices[3];
	struct angulo angulos[3];
	int numero_triangulo;
	struct arista aristas[3];
	struct arista_mayor_triangulo elemento_mayor;
	struct elementos_adyacentes elemento_adyacente;
};
