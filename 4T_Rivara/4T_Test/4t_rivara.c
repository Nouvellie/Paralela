#include <stdio.h>
#include <math.h> 
#include <estructuras.h>
#include <metodos.h>
#include <manejo_ficheros.h>

typedef struct triangulo t;
typedef struct punto p;
//Calculamos los angulos, segun los lados del triangulo

int main(){
	//system("clear");
	int size_ele=tamano_ele();
	t malla[size_ele];

	int triangulos_refinar[size_ele];

	llenado_malla(&malla);
	//eliminar_triangulo_ele(3,malla);
	//llenado_malla(malla);
	//refinamiento(18, &malla);

	//criterio_refinamiento(triangulos_refinar,5,malla);


	//printf("%d %f %f %f", malla[0].numero_triangulo, malla[0].angulos[0].grados, malla[0].angulos[1].grados, malla[0].angulos[2].grados);


	/*for(int i=0;i<size_ele;i++){
		printf("%d",triangulos_refinar[i]);
	}*/
	return 0;
}
