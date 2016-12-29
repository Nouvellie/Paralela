#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define length(x) (sizeof(x)-sizeof(x[0]))
int equals(char s0[], char s1[]){

	for(int i=0;i<length(s1)-1;i++){

		if(s0[i]!=s1[i]){
			return 0;
		}
	}
	return 1;
}


void lectura_node(int x1[],float x2[], float x3[]){
	FILE *fichero;
   char nombre[10] = "mesh.node";
   int i, size;

   fichero = fopen( nombre, "r" );
   printf( "Fichero: Node " );
   if( fichero )
      printf( "existe (ABIERTO)\n" );
   else
   {
      printf( "Error (NO ABIERTO)\n" );
      return 1;
   }

   fscanf( fichero, "%d",&size );
   printf( "%d\n", size);
   float x4;
   for( i=0; i< size; i++ )
   {
      fscanf( fichero, "%d %f %f %f\n", &x1[i], &x2[i], &x3[i], &x4 );
      printf( "%d %f %f %f\n", x1[i], x2[i], x3[i], x4 );
   }

   if( !fclose(fichero) )
      printf( "Fichero cerrado\n" );
   else
   {
      printf( "Error: fichero NO CERRADO\n" );
      return 1;
   }


}

void lectura_ele(int x1[],int x2[], int x3[], int x4[]){
	FILE *fichero;
   char nombre[10] = "mesh.ele";
   int i, size;

   fichero = fopen( nombre, "r" );
   printf( "Fichero: Elements ");
   if( fichero )
      printf( "existe (ABIERTO)\n" );
   else
   {
      printf( "Error (NO ABIERTO)\n" );
      return 1;
   }

   fscanf( fichero, "%d",&size );
   printf( "%d\n", size);
   for( i=0; i< size; i++ )
   {
      fscanf( fichero, "%d %d %d %d\n", &x1[i], &x2[i], &x3[i], &x4[i] );
      printf( "%d %d %d %d\n", x1[i], x2[i], x3[i], x4[i] );
   }

   if( !fclose(fichero) )
      printf( "Fichero cerrado\n" );
   else
   {
      printf( "Error: fichero NO CERRADO\n" );
      return 1;
   }



}

//PARAMETROS PARA AGREGAR UN NODO SON:
//ERROR AL GRABAR MUCHOS NODOS, YA QUE ME BORRA EL PRIMERO NUMERO DEL NODO Y SE QUEDA CON LOS ULTIMOS 3 DATOS
void agregar_vertice_node(p puntos){
   inicio_agregar_vertice_node();
   termino_agregar_vertice_node(puntos);
}

void inicio_agregar_vertice_node(){
   FILE *fp;
   int size_node=tamano_node();
   size_node++;
   fp = fopen ( "mesh.node", "r+" );
   rewind(fp);
   fprintf(fp, "%d\n",size_node);
   fclose ( fp );
   free(fp);
}
void termino_agregar_vertice_node(p puntos){
   FILE *fp;
   int size_node=tamano_node();
   float z=0;
   fp = fopen ( "mesh.node", "a" );

   fprintf(fp, "\n%d %f %f %ff",size_node,puntos.coordenadas[0],puntos.coordenadas[1], z);
   fclose ( fp );

}



//Sacamos al triangulo biseccionado del archivo
void eliminar_triangulo_ele(int numero_triangulo,t malla[]){

   FILE *fp;
   int size_ele=tamano_ele();

      fp = fopen ( "mesh.ele", "w" );
         fprintf(fp, "%d\n",size_ele-1);

      for(int i=0;i < size_ele;i++){
          if(malla[i].numero_triangulo != numero_triangulo){
               if(i != size_ele-1){
               fprintf(fp, "%d %d %d %d\n",malla[i].numero_triangulo, malla[i].vertices[0].numero,malla[i].vertices[1].numero, malla[i].vertices[2].numero);
            }else{
               fprintf(fp, "%d %d %d %d",malla[i].numero_triangulo, malla[i].vertices[0].numero,malla[i].vertices[1].numero, malla[i].vertices[2].numero);
            }
          }
      }

   fclose ( fp );

}


//PARAMETROS PARA AGREGAR UN TRIANGULO SON: NUMERO DE CADA VERTICE Y ESTE DEFINIDO EN NODE PREVIAMENTE

//Agregamos triangulo al archivo ele
void agregar_triangulo_ele(t t1){
   inicio_agregar_ele();
   termino_agregar_ele(t1);
}

void inicio_agregar_ele(){
   FILE *fp;
   int size_ele=tamano_ele();
   size_ele++;

   fp = fopen ( "mesh.ele", "r+" );
   rewind(fp);
   fprintf(fp, "%d\n",size_ele);
   fclose ( fp );
}

void termino_agregar_ele(t t1){
   FILE *fp;
   int size_ele=tamano_ele();
   fp = fopen ( "mesh.ele", "a" );
   fprintf(fp, "\n%d %d %d %d",size_ele,t1.vertices[0].numero,t1.vertices[1].numero,t1.vertices[2].numero,0);
   fclose ( fp );
}

int tamano_node(){

    FILE *fp;
	int res;

	fp = fopen("mesh.node", "r");
	rewind(fp);
	fscanf(fp,"%d *\n", &res);
    fclose(fp);

    return res;
}

int tamano_ele(){
	FILE *fp;
	int res;

	fp = fopen("mesh.ele", "r");
	rewind(fp);
	fscanf(fp,"%d *\n", &res);
    fclose(fp);

    return res;
}
