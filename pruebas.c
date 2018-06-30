#include <stdlib.h>
#include <stdio.h>



char nombres[3][20];
int puntuaciones[3];

int bufferToInt(char buffer,int longitud){

}

void guardaHighScores(){
	FILE *archivo;
	archivo=fopen("h","w");
	fprintf(archivo,"%s,",nombres[0]);
    fprintf(archivo,"%s,",nombres[1]);
    fprintf(archivo,"%s,",nombres[2]);
    fprintf(archivo,"%i,",puntuaciones[0]);
    fprintf(archivo,"%i,",puntuaciones[1]);
    fprintf(archivo,"%i,",puntuaciones[2]);
	fclose(archivo);
}

void abreHighScores(){
	FILE* archivo;
	archivo=fopen("h","r");
	char caracter;
    char buffer[20];
    
    int contador=0;

    int pos=0;
    do{
        caracter=fgetc(archivo);
        if(caracter!=EOF){
            if(caracter!=','){
                buffer[pos]=caracter;
                pos++;
            }else{
                if(contador<3){
                    for(size_t i = 0; i < 20; i++){
                        nombres[3][i]=buffer[i];
                    }
                }
                pos=0;
                contador++;
            }
        }
    }while(caracter!=EOF);
}



void main(){
    //guardaHighScores();
    abreHighScores();
    printf("%s",nombres[0]);
}
