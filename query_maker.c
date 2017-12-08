//
// Created by jorge on 03-12-17.
//

//Librerias
#include <stdlib.h>
#include <stdio.h>
#include "similitud.h"
#include <time.h>

//Macros
#define DEBUG 0
#define BUFFER_SIZE 256
#define ITERS 1
#define N_QUERY 197 // Largo query
#define N_DIC 77455 // Largo diccionario
#define N_WORD 64   // Largo palabras

//Variables globales
int long cuentaeditdist = 0;

char    QUERY_PATH[128];
char    PIVOTS_PATH[128];
int     N_PIVOTS = 1;
char    DICTIONARY_PATH[128];
char    INDEX_PATH[128];
int     RANGE;
char    RESULT_PATH[128];


// ./query_maker query.txt pivotes.txt N_PIVOTES diccionario.txt indice.txt RANGO resultado.txt
int main(int argc, char *(argv[])) {

    int i, j, k;                                        //Iteradores
    FILE *dic, *pivots, *index, *q, *results;                      //Archivos
    char word[BUFFER_SIZE], query[BUFFER_SIZE];          //Buffer lectura archivos
    char pivot[BUFFER_SIZE], buffer[N_WORD];                             //Buffer lectura archivos
    int D_ip, D_qp;                                     //Variables formula candidatos
    double time_search = 0;                                //Tiempo demora promedio
    struct timespec ts1, ts2;                              //Variables toma de tiempos
    long int n_candidates = 0, n_solutions = 0;         //N cadidatos y soluciones


    if (argc != 8) {
        printf("Error en el numero de parametros\n");
        return -1;
    }

    strcpy(QUERY_PATH, argv[1]);
    strcpy(PIVOTS_PATH, argv[2]);
    N_PIVOTS = atoi(argv[3]);
    strcpy(DICTIONARY_PATH, argv[4]);
    strcpy(INDEX_PATH, argv[5]);
    RANGE = atoi(argv[6]);
    strcpy(RESULT_PATH, argv[7]);


    //Abrir archivos
    if ((dic = fopen(DICTIONARY_PATH, "r")) == NULL) {
        printf("Error load [DIC]\n");
        return -1;
    }
    if ((pivots = fopen(PIVOTS_PATH, "r")) == NULL) {
        printf("Error load [PIVOT]\n");
        return -1;
    }
    if ((index = fopen(INDEX_PATH, "r")) == NULL) {
        printf("Error load [INDEX]\n");
        return -1;
    }
    if ((q = fopen(QUERY_PATH, "r")) == NULL) {
        printf("Error load [QUERY]\n");
        return -1;
    }
    if ((results = fopen(RESULT_PATH, "w")) == NULL) {
        printf("error resultados\n");
        return -1;
    }
    printf("Open files OK...\n");

    //TODO DECLARAR ESTA VARIABLE ANTES DE CALCULAR LAS DISTANCIAS
    int dist_query_pivot[N_QUERY][N_PIVOTS];

    //CARGAR INDICE EN MEMORIA
    int **dist_word_pivot = malloc(N_DIC * sizeof(int *));
    for(i = 0; i < N_DIC; i++)
        dist_word_pivot[i] = malloc(N_PIVOTS * sizeof(int));

    for(i = 0; i< N_DIC; i++) {
        for (j = 0; j < N_PIVOTS; j++) {
            fscanf(index, "%d", &dist_word_pivot[i][j]);
        }
    }

    //CARGAR QUERY EN MEMORIA
    char **querys = malloc(N_QUERY * sizeof(char *));
    for(i = 0; i < N_QUERY; i++){
        querys[i] = malloc(N_WORD * sizeof(char));
        fscanf(q, "%s", querys[i]);
    }

    //CARGAR DICCIONARIO EN MEMORIA
    char **words = malloc(N_DIC * sizeof(char *));
    for ( i = 0; i < N_DIC ; i++ ) {
        words[i] = malloc(N_WORD * sizeof(char));
        fscanf(dic, "%s", words[i]);
    }



    printf("---------------------------------------------------------------------\n");
    printf("PIVOTES:%d\tRANGO:%d\n", N_PIVOTS, RANGE);
    printf("Analizar query...\n");

    /* INICIO TOMA DE TIEMPO*/
    clock_gettime(CLOCK_REALTIME, &ts1);

    //Precalcular distacias pivote-query
    i = 0;
    rewind(q);
    while (fscanf(q, "%s", query) > 0) {
        j = 0;
        rewind(pivots);
        while (fscanf(pivots, "%s", pivot) > 0) {
            dist_query_pivot[i][j] = edit(query, pivot, 0, 0);
            j++;
        }
        i++;
    }
    #if DEBUG
    printf("Precalculo distancia pivote-query OK..\n");
    #endif

    rewind(q);
    //Ciclo lectura querys
    k = 0;
    while (fscanf(q, "%s", query) > 0) {
        #if DEBUG
        printf("\nQUERY = %s, range = %d\n", query, RANGE);
        #else
        //printf("Q = %d...\n", k);
        #endif
        rewind(dic);
        rewind(index);
        i = 0;
        //Ciclo lectura palabras diccionario
        while (fscanf(dic, "%s", word) > 0) {
            //Ciclo lectura pivotes
            for(j=0; j< N_PIVOTS; j++) {
                //fscanf(index, "%d", &D_ip);
                D_ip = dist_word_pivot[i][j];
                D_qp = dist_query_pivot[k][j];

                if (abs(D_ip - D_qp) > RANGE) {
                    #if DEBUG
                    printf("fuera rango |\t");
                    #endif
                    break;
                }
                #if DEBUG
                printf("candidato   |\t");
                #endif
            }

            if (j == N_PIVOTS) {
                #if DEBUG
                printf("POSIBLE CANDIDATO!!!! |");
                #endif
                n_candidates++;
                if (edit(query, word, 0, 0) <= RANGE) {
                    #if DEBUG
                    printf("!!!SOLUCION!!!");
                    #endif
                    n_solutions++;
                    fprintf(results, "w:%s | q:%s\n", word, query);
                }
            }
            i++;
            #if DEBUG
            printf("/// %s", word);
            printf("\n");
            #endif
        }
        k++;
        #if DEBUG
        printf("----------------------------------------------------------------------------------------------\n");
        #endif
    }
    clock_gettime(CLOCK_REALTIME, &ts2);    //FIN TOMA DE TIEMPO
    time_search += (float) (1.0 * (1.0 * ts2.tv_nsec - ts1.tv_nsec * 1.0) * 1e-9 + 1.0 * ts2.tv_sec - 1.0 * ts1.tv_sec);

    time_search = time_search / ITERS;

    printf("Iteraciones:%d\nTiempo Promedio:=%.4g segundos\nCandidatos:%ld\nSoluciones:%ld\nEvaluaciones:%ld\n", ITERS,
           time_search, n_candidates, n_solutions, cuentaeditdist);
    printf("---------------------------------------------------------------------\n");

    fprintf(results, "Tiempo promedio:\t%.16g\n", time_search);
    fprintf(results, "Numero pivotes:\t%d\n", N_PIVOTS);
    fprintf(results, "Evaluaciones\t%ld\n", cuentaeditdist);
    fprintf(results, "Candidatos:\t%ld\n", n_candidates);
    fprintf(results, "Soluciones:\t%ld\n", n_solutions);

    fclose(results);
    fclose(index);
    fclose(dic);
    fclose(q);
    fclose(pivots);

    return 0;
}
