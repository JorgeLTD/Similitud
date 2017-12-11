cmake_minimum_required(VERSION 3.9)
project(similitud C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -Wall")

set(PREPROC_FILES preproc.c similitud.h)
add_executable(preproc ${PREPROC_FILES})

set(QUERY_MAKER_FILES query_maker.c similitud.h)
add_executable(query_maker ${QUERY_MAKER_FILES})