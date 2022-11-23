#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

/*
 * Goes through a given file and separates that file into sorted 1MB files using (internal) mergeSort algorithm
 * */
void separationSort(FILE *input) {
    unsigned int *buffer = malloc(sizeof(unsigned int)*(MEMORY_LIMIT/RECORD_SIZE));
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    int count = 0;
    while((nread = getline(&line, &len, input)) != -1) {
        if (count < MEMORY_LIMIT/RECORD_SIZE) {
            buffer[count++] = (unsigned int)strtoul(line, NULL, 10); 
        } else {
            count = 0;
            return;
        }
    }
}

/*
 * Sort the records in the memory buffer with mergeSort algorithm 
 * */


