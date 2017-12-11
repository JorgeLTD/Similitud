#!/bin/bash

#consulta y diccionario no cambian en las pruebas
CONSULTA=querys/dic10.txt
DICCIONARIO=diccionarios/dic90.txt


# 4 PIVOTES!!!!!!!!!!!!!!!!!!!!!!!

PIVOTES=pivotes/pivote4.txt
N_PIVOTES=4
INDICE=indices/90_4.txt

RANGO=4
RESULTADO=resultados/pivot_4_rango_4.txt
./cmake-build-debug/query_maker ${CONSULTA} ${PIVOTES} ${N_PIVOTES} ${DICCIONARIO} ${INDICE} ${RANGO} ${RESULTADO}

# 8 PIVOTES!!!!!!!!!!!!!!!!

PIVOTES=pivotes/pivote8.txt
N_PIVOTES=8
INDICE=indices/90_8.txt

RANGO=1
RESULTADO=resultados/pivot_8_rango_1.txt
./cmake-build-debug/query_maker ${CONSULTA} ${PIVOTES} ${N_PIVOTES} ${DICCIONARIO} ${INDICE} ${RANGO} ${RESULTADO}

RANGO=2
RESULTADO=resultados/pivot_8_rango_2.txt
./cmake-build-debug/query_maker ${CONSULTA} ${PIVOTES} ${N_PIVOTES} ${DICCIONARIO} ${INDICE} ${RANGO} ${RESULTADO}

RANGO=3
RESULTADO=resultados/pivot_8_rango_3.txt
./cmake-build-debug/query_maker ${CONSULTA} ${PIVOTES} ${N_PIVOTES} ${DICCIONARIO} ${INDICE} ${RANGO} ${RESULTADO}

RANGO=4
RESULTADO=resultados/pivot_8_rango_4.txt
./cmake-build-debug/query_maker ${CONSULTA} ${PIVOTES} ${N_PIVOTES} ${DICCIONARIO} ${INDICE} ${RANGO} ${RESULTADO}

# 16 PIVOTES!!!!!!!!!!!!!!!!

PIVOTES=pivotes/pivote16.txt
N_PIVOTES=16
INDICE=indices/90_16.txt

RANGO=1
RESULTADO=resultados/pivot_16_rango_1.txt
./cmake-build-debug/query_maker ${CONSULTA} ${PIVOTES} ${N_PIVOTES} ${DICCIONARIO} ${INDICE} ${RANGO} ${RESULTADO}

RANGO=2
RESULTADO=resultados/pivot_16_rango_2.txt
./cmake-build-debug/query_maker ${CONSULTA} ${PIVOTES} ${N_PIVOTES} ${DICCIONARIO} ${INDICE} ${RANGO} ${RESULTADO}

RANGO=3
RESULTADO=resultados/pivot_16_rango_3.txt
./cmake-build-debug/query_maker ${CONSULTA} ${PIVOTES} ${N_PIVOTES} ${DICCIONARIO} ${INDICE} ${RANGO} ${RESULTADO}

RANGO=4
RESULTADO=resultados/pivot_16_rango_4.txt
./cmake-build-debug/query_maker ${CONSULTA} ${PIVOTES} ${N_PIVOTES} ${DICCIONARIO} ${INDICE} ${RANGO} ${RESULTADO}

# 32 PIVOTES!!!!!!!!!!!!!!!!

PIVOTES=pivotes/pivote32.txt
N_PIVOTES=32
INDICE=indices/90_32.txt

RANGO=1
RESULTADO=resultados/pivot_32_rango_1.txt
./cmake-build-debug/query_maker ${CONSULTA} ${PIVOTES} ${N_PIVOTES} ${DICCIONARIO} ${INDICE} ${RANGO} ${RESULTADO}

RANGO=2
RESULTADO=resultados/pivot_32_rango_2.txt
./cmake-build-debug/query_maker ${CONSULTA} ${PIVOTES} ${N_PIVOTES} ${DICCIONARIO} ${INDICE} ${RANGO} ${RESULTADO}

RANGO=3
RESULTADO=resultados/pivot_32_rango_3.txt
./cmake-build-debug/query_maker ${CONSULTA} ${PIVOTES} ${N_PIVOTES} ${DICCIONARIO} ${INDICE} ${RANGO} ${RESULTADO}

RANGO=4
RESULTADO=resultados/pivot_32_rango_4.txt
./cmake-build-debug/query_maker ${CONSULTA} ${PIVOTES} ${N_PIVOTES} ${DICCIONARIO} ${INDICE} ${RANGO} ${RESULTADO}
