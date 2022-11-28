#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include "external_merge.h"
#include "constant.h"

extern int fileNum;
extern int ways;

void exMerge() {
    printf("Merge phase start.\n");
    int pass = 1;
    while (fileNum > 1) {
        exMergeSort(pass, fileNum);
        int remainer = fileNum % ways;
        fileNum = fileNum / ways;
        if (remainer > 0) {
            fileNum++;
        } 
        pass++;
    }

    // generate the outpute file
    if (fileNum == 1) {
        char syscom[50];
        sprintf(syscom, "cp ./tmp/pass%d/1.txt ./output.txt", pass - 1);
        system(syscom);
    }
    printf("Merge phase done.\n");
}


/*
 * External merge sort takes the files array and merge two(or multiple) sorted files into a new file. This
 * is called a run. 
 * The exMergeSort will process the files until all the sorted tmp files are merged into a single file. 
 * */
void exMergeSort(int pass, int nums) {
    int inputFileNum = 0; 
    int run = 1;
    for (; inputFileNum < nums;) {
        
        // create the dir for current pass
        if (inputFileNum == 0) {
            int status;
            char dirName[20];
            sprintf(dirName, "./tmp/pass%d", pass);
            if ((status = mkdir(dirName, S_IRWXU | S_IRWXU | S_IROTH | S_IXOTH)) == -1) {
                fprintf(stderr, "Failed to create tmp directory %s.\n", dirName);
                exit(EXIT_FAILURE);
            }
        }
        // open new file to merge in each run
        FILE *fm; 
        char mergedFileName[20];
        sprintf(mergedFileName, "./tmp/pass%d/%d.txt", pass, run);
        if ((fm = fopen(mergedFileName, "w+")) == NULL) {
            fprintf(stderr, "%s\n", strerror(errno));
            fprintf(stderr, "merged file %s: can't create or open.\n", mergedFileName);
        }
        
        // Rewind the sorted files in previous pass, each run merge way_numbers numbers of files
        // Merge the sorted files with multi ways in N runs. 
        // In the first N - 1 runs, each run merge ways numbers of files
        // In the last run, merge the remaining files. 
        int way_numbers = run * ways <= nums ? ways : nums - inputFileNum;
        FILE *fiarr[way_numbers];
        for (int i = 0; i < way_numbers; i++) {
           char inputFileName[20];
           inputFileNum++; // start from 0 to nums
           sprintf(inputFileName, "./tmp/pass%d/%d.txt", pass - 1, inputFileNum);
           if ((fiarr[i] = fopen(inputFileName, "r")) == NULL) {
                fprintf(stderr, "%s\n", strerror(errno));
                fprintf(stderr, "input file %s: can't create or open.\n", inputFileName);
           }
           rewind(fiarr[i]);
        }
        

        // get and compare records until files runs out of records
        char *records[way_numbers]; 
        for (int i = 0; i < way_numbers; i++) {
            records[i] = getRecord(fiarr[i]);
        }
        // loop until only one file is not run-out
        while(validateRecords(records, way_numbers )) {
            int index = getMinRecordIndex(records, way_numbers);
            fprintf(fm, "%s", records[index]); // print record to new merged file
            free(records[index]); // free the memory allocated by getline in getRecord function
            records[index] = getRecord(fiarr[index]); // Get new record from the file
        }
       
        // put the rest record in the last remaining file into new file 
        int lastIndex = getLastRemainRecordIndex(records, way_numbers);
        while(records[lastIndex]) {
            fprintf(fm, "%s", records[lastIndex]);
            free(records[lastIndex]);
            records[lastIndex] = getRecord(fiarr[lastIndex]);
        }
        // close files
        fclose(fm);
        for (int i = 0; i < way_numbers; i++) {
            fclose(fiarr[i]);
        }
        run++;
    }

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
    return NULL;
}

/*
 * Validate whether at least two records are non-zero
 * */
bool validateRecords(char **records, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (records[i] != NULL) {
            count++;
        }
    }
    return count >= 2;
}


/*
 * Get the min valid record's index
 * */

int getMinRecordIndex(char **records, int size) {
    int index = 0;
    unsigned int min = (int)INFINITY;
    for (int i = 0; i < size; i++) {
        if (records[i] == NULL) { // pass invalid run-out record files
            continue;
        } 
        if (strtoul(records[i], NULL, 10) < min) {
            min = strtoul(records[i], NULL, 10);
            index = i;
        }
    }
    return index;
}

/*
 * Get the last remainer of the records
 * */
int getLastRemainRecordIndex(char **records, int size) {
    for (int i = 0; i < size; i++) {
        if (records[i] != NULL) {
            return i;
        }
    }
}



