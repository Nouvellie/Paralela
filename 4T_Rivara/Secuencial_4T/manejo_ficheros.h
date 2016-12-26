#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define length(x) (sizeof(x)-sizeof(x[0]))

int filas_fichero(char fichero[]){
	FILE *archivo;

	char caracteres[50];
	int contador=-1;
	archivo = fopen(fichero,"r");
 	
 	if (archivo == NULL)
 		exit(1);
 	
 	while (feof(archivo) == 0){
 		fgets(caracteres,50,archivo);
 		contador=contador+1;
 	}
 	 fclose(archivo);
 	 return contador;
}

int equals(char s0[], char s1[]){	
	
	for(int i=0;i<length(s1)-1;i++){

		if(s0[i]!=s1[i]){
			return 0;
		}
	}
	return 1;
}

void asignar_string(char s0[], char s1[]){
	for(int i=0;i<50;i++){
		s0[i]=s1[i];
	}
}

void split_convert(char s[],int vector[]){
	for(int i=0;i<50;i++){
		if(s[i]!=' '){
			vector[i]=s[i];
		}else{
			vector[i]=0;
		}
	}

}

void string_entero(int enteros[100],char (*string)[100]){
	//Linea por linea , viendo los caracteres que tiene
	char *token;
	int matriz_enteros=0;
	int j=0;
	for(int i=0;i<100;i++){
   		const char s[2] = " ";
   
	   /* get the first token */
	   token = strtok(string[i], s);
	   
	   /* walk through other tokens */
	   while( token != NULL ) 
	   {
	   		//printf( "%d\n", atoi(token) );
	   		enteros[j]=atoi(token);
	   		//printf("%d %d\n",enteros[j],j);
	      	token = strtok(NULL, s);
	      	j++;
	    
	   }
	}
}

