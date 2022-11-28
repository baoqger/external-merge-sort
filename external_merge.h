#ifndef EXTERNAL_SORT_H
#define EXTERNAL_SORT_H 

#include <stdio.h>
#include <stdbool.h>

void exMerge();
void exMergeSort(int, int);
char* getRecord(FILE*);
bool validateRecords(char**, int);
int getMinRecordIndex(char**, int);
int getLastRemainRecordIndex(char**, int);
void multiWayMerge(int, FILE**, FILE*);
#endif 
