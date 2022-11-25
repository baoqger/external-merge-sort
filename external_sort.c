#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "external_sort.h"
#include "internal_sort.h"

int fileNum = 1;

/*
 * Goes through a given file and separates that file into sorted 1MB files using (internal) mergeSort algorithm
 * */
void separationSort(FILE *input) {
    FILE *fp;
    unsigned int *buffer = malloc(sizeof(unsigned int)*(MEMORY_LIMIT/RECORD_SIZE));
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    int count = 0;
    while((nread = getline(&line, &len, input)) != -1) {
        if (count < MEMORY_LIMIT/RECORD_SIZE) {
            buffer[count++] = (unsigned int)strtoul(line, NULL, 10); 
        } else {
            mergeSort(buffer, count); // sort records
            
            // output sorted to file
            if (fileNum == 1) { // create the dir
                int status;
                // create tmp directory
                if ((status = mkdir("./tmp", S_IRWXU | S_IRWXU | S_IROTH | S_IXOTH)) == -1) {
                    fprintf(stderr, "Failed to create tmp directory.\n");
                    exit(EXIT_FAILURE);
                }
                printf("Created tmp directory.\n");
                // create pass0 directory for sort phase
                if ((status = mkdir("./tmp/pass0", S_IRWXU | S_IRWXU | S_IROTH | S_IXOTH)) == -1) {
                    fprintf(stderr, "Failed to create pass0 directory.\n");
                    exit(EXIT_FAILURE);
                }
                printf("Created pass0 directory.\n");
 
            }

            char fileName[20];
            sprintf(fileName, "./tmp/pass0/%d.txt", fileNum);
            if ((fp = fopen(fileName, "w+")) == NULL) {
                fprintf(stderr, "Failed to create file: %s.\n", fileName);
                exit(EXIT_FAILURE);
            }

            outputToFile(buffer, count, fp);

            // Reset memory buffer(zero-out the entire array)
            memset(buffer, 0, sizeof(unsigned int)*(MEMORY_LIMIT/RECORD_SIZE));
            count = 0;
            fileNum++;
            buffer[count++] = (unsigned int)strtoul(line, NULL, 10); // add the current record into new buffer's as first element
            
        }
    }

    // sort the last and final file
    mergeSort(buffer, count);
    char fileName[20];
    sprintf(fileName, "./tmp/pass0/%d.txt", fileNum);
    if ((fp = fopen(fileName, "w+")) == NULL) {
        fprintf(stderr, "Failed to create file: %s.\n", fileName);
        exit(EXIT_FAILURE);
    }
    outputToFile(buffer, count, fp);
    
    free(buffer);
    free(line);
    printf("Sort phase done. %d tmp sorted files are produced.\n", fileNum - 1);
}


/*
 * Output sorted record to given file(of)
 * */

void outputToFile(unsigned int *buffer, int size, FILE *of) {
    int i;
    for (i = 0; i < size; i++) {
        fprintf(of, "%u\n", buffer[i]);
    }
    fclose(of);
}





