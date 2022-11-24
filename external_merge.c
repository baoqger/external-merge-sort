#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "external_merge.h"
#include "constant.h"

extern int fileNum;

/*
 * External merge sort takes the files array and merge two(or multiple) sorted files into a new file. This
 * is called a run. 
 * The exMergeSort will process the files until all the sorted tmp files are merged into a single file. 
 * */
void exMergeSort() {
    int i; 
    int inputFileNum = 1; 
    printf("Merge phase starts.\n");

    for (i = 0; i < fileNum - 1; i += MULTI_WAY_NUMBER) {
        
        // open new file to merge into
        FILE *fm; 
        char mergedFileName[20];
        sprintf(mergedFileName, "./tmp/%d.txt", fileNum);
        if ((fm = fopen(mergedFileName, "w+")) == NULL) {
            fprintf(stderr, "%s\n", strerror(errno));
            fprintf(stderr, "merged file %s: can't create or open.\n", mergedFileName);
        }

        // Rewind first and second files that will be merged
        FILE *fi1;
        char inputFileName1[20];
        sprintf(inputFileName1, "./tmp/%d.txt", inputFileNum);
        if ((fi1 = fopen(inputFileName1, "r")) == NULL) {
            fprintf(stderr, "%s\n", strerror(errno));
            fprintf(stderr, "merged file %s: can't create or open.\n", inputFileName1);
        }
        inputFileNum++;
        
        FILE *fi2;
        char inputFileName2[20];
        sprintf(inputFileName2, "./tmp/%d.txt", inputFileNum);
        if ((fi2 = fopen(inputFileName2, "r")) == NULL) {
            fprintf(stderr, "%s\n", strerror(errno));
            fprintf(stderr, "merged file %s: can't create or open.\n", inputFileName2);
        }
        inputFileNum++;
        rewind(fi1);
        rewind(fi2);

        // get and compare records until fi1 and fi2 runs out o records
        char *record1 = getRecord(fi1);
        char *record2 = getRecord(fi2);

        while(record1 && record2) {
            if(strtoul(record1, NULL, 10) < strtoul(record2, NULL, 10)) {
                fprintf(fm, "%s", record1); // Print record1 to new file
                free(record1);
                record1 = getRecord(fi1); // Get new record from fi1 file
            } else {
                fprintf(fm, "%s", record2); // print record2 to new file
                free(record2);
                record2 = getRecord(fi2);
            }
        }

        // if there are more records in fi1, put the rest into the new file
        while(record1) {
            fprintf(fm, "%s", record1);
            free(record1);
            record1 = getRecord(fi1);
        }

        // If there are more records in fi2, put the rest into the new file
        while(record2) {
            fprintf(fm, "%s", record2);
            free(record2);
            record2 = getRecord(fi2);
        }

        fclose(fm); fclose(fi1); fclose(fi2);

        fileNum++;
    }

    printf("Merge phase finish.\n");
}

/*
 * Returns a copy of the record
 *
 * */
char* getRecord(FILE *ifp) {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    while ((nread = getline(&line, &len, ifp)) != -1) {
        return line;       
    }
    return 0;
}
