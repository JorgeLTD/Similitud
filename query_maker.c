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
#define N_QUERY 9000 //maximo query
#define N_DIC 80000 //maximo diccionario

//Variables globales
int long cuentaeditdist = 0;

char QUERY_PATH[128] = "querys/q.txt";
char PIVOTS_PATH[128] = "pivotes/pivote1.txt";
int N_PIVOTS = 1;
char DICTIONARY_PATH[128] = "diccionarios/dic90.txt";
char INDEX_PATH[128] = "indices/index1.txt";
int RANGE = 1;
char RESULT_PATH[128] = "resultados/1.txt";


// ./query_maker query.txt pivotes.txt N_PIVOTES diccionario.txt indice.txt RANGO resultado.txt
int main(int argc, char *(argv[])) {

    int i, j, k;                                        //Iteradores
    FILE *dic, *pivots, *index, *q, *results;                      //Archivos
    char word[BUFFER_SIZE], query[BUFFER_SIZE];          //Buffer lectura archivos
    char pivot[BUFFER_SIZE];                             //Buffer lectura archivos
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

    //VARIABLES DEPENDIENTES DE LA ENTRADA
    int dist_query_pivot[N_QUERY][N_PIVOTS];
    printf("declariom variable\n");

    //int dist_word_pivot[N_DIC][N_PIVOTS];
    //////////////////////////////////////////////////////////7
    /*int **dist_word_pivot;

    dist_word_pivot = (int **) malloc(sizeof(int)*N_DIC)
    */
    int *dist_word_pivot;
    dist_word_pivot = (int *) malloc(sizeof(int)*N_DIC*N_PIVOTS);
    int **array = malloc(N_DIC * sizeof *array + (N_DIC * (N_PIVOTS * sizeof **array)));

    dist_word_pivot[0] = 0;

    //Analizar consulta
    printf("---------------------------------------------------------------------\n");
    printf("PIVOTES:%d\tRANGO:%d\n", N_PIVOTS, RANGE);
    printf("Analizar query...\n");

    clock_gettime(CLOCK_REALTIME, &ts1);    //INICIO TOMA DE TIEMPO
    //Precalcular distacias pivote-query
    i = 0;
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

        //Ciclo lectura palabras diccionario
        while (fscanf(dic, "%s", word) > 0) {
            //Ciclo lectura pivotes
            for(j=0; j< N_PIVOTS; j++) {
                fscanf(index, "%d", &D_ip);
                D_qp = dist_query_pivot[k][j];

                if (abs(D_ip - D_qp) > RANGE) {
                    #if DEBUG
                    printf("fuera rango |\t");
                    #endif

                    //consumir contenido restante linea y salir, -1 por que ya se consumio un valor
                    while (j < N_PIVOTS - 1) {
                        fscanf(index, "%d", &D_ip);
                        j++;
                    }
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
