//
// Created by jorge on 03-12-17.
//

//Librerias
#include <stdio.h>
#include <stdlib.h>
#include "similitud.h"

//Macros
#define BUFF_SIZE 256


//Variables globales
long int cuentaeditdist = 0;

int main(int argc, char *argv[]){

    FILE *dic, *pivot, *index;
    char buffer_1[BUFF_SIZE], buffer_2[BUFF_SIZE];

    //Cargar archivos
    if( ( dic = fopen("diccionarios/dic90.txt", "r") )  == NULL){
        printf("Error load [DIC]\n");
        return -1;
    }
    if( ( pivot = fopen("pivotes/pivote1.txt", "r") ) == NULL){
        printf("Error load [PIVOT]\n");
        return -1;
    }
    if( (index = fopen("indices/90_1.txt", "w") ) == NULL){
        printf("Error load [INDEX]\n");
        return -1;
    }
    printf("Load OK...\n");


    //Crear indice
    while( fscanf(dic, "%s", buffer_1)  > 0 ){
        while( fscanf(pivot, "%s", buffer_2) > 0 ){
            fprintf(index, "%d ", edit(buffer_1, buffer_2, 0, 0));
        }
        fprintf(index, "\n");
        rewind(pivot);
    }
    printf("Index done!\n");

    fclose(index);
    fclose(dic);
    fclose(pivot);

    return 0;
}