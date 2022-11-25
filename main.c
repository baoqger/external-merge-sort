/*
 * Divide the entire input file into different groups based on the available memory
 * resource restrictions. 
 * 
 * Read each group of the input file into the memory buffer, sort the records in the memory buffer, 
 * save the sorted records in a temporary sub file. This process is called one run. 
 *
 * At the end of this sort phase, # temporary sorted sub files will be created.
 * */

/*
 * main.c 
 *
 * Created on: Nov 23, 2022
 * Author: Chris Bao
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "external_sort.h"
#include "external_merge.h"

int main() {
    FILE *fp;
    char filename[100];

    // make sure the input file exist
    if ((fp = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "Can't open input file. Please run randomNumber.sh script first.\n ");
        return 1;
    }

    // sort phase
    separationSort(fp);  
    fclose(fp);
    
    // merge phase
    exMerge();

    printf("Success\n");
    return 0;
}
