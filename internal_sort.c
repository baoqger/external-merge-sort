/*
 * Sort records in the memory buffer with internal mergeSort algorithm 
 * */
#include <stdlib.h>
#include <stdio.h>
#include "internal_sort.h"

void mergeSort(unsigned int *arr, int n) {
    unsigned int *tmpArray;

    tmpArray = malloc(n * sizeof(unsigned int));

    if (tmpArray != NULL) {
        mSort(arr, tmpArray, 0, n - 1); 
        free(tmpArray);
    } else {
        fprintf(stderr, "No space for tmp array!");
        exit(0);
    } 
                
}


void mSort(unsigned int *arr, unsigned int *tmp, int left, int right) {
    int center;

    if (left < right) {
        center = (left + right) / 2;
        mSort(arr, tmp, left, center);
        mSort(arr, tmp, center + 1, right);
        merge(arr, tmp, left, center + 1, right);
    }
}

void merge(unsigned int *arr, unsigned int *tmp, int lpos, int rpos, int rightend) {
    int i, leftend, numElements, tmppos;

    leftend = rpos - 1;
    tmppos = lpos;
    numElements = rightend - lpos + 1;

    //main loop
    while(lpos <= leftend && rpos <= rightend) {
        if (arr[lpos] <= arr[rpos]) {
            tmp[tmppos++] = arr[lpos++];
        } else {
            tmp[tmppos++] = arr[rpos++];
        }
    }

    while (lpos <= leftend) // copy rest of first half
        tmp[tmppos++] = arr[lpos++];
    while (rpos <= rightend) // copy rest of second half
        tmp[tmppos++] = arr[rpos++];

    // copy tmp array back
    for (i = 0; i < numElements; i++, rightend--) {
        arr[rightend] = tmp[rightend];
    }
}




