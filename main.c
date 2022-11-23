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
#include "sort.h"

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

    // merge phase
}
