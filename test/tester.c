#include <stdio.h>
#include <stdlib.h>


int main() {
    char fileName[20]; 
    sprintf(fileName, "./output.txt");

    FILE *fd;
    if ((fd = fopen(fileName, "r")) == NULL) {
        fprintf(stderr, "Failed to open the output file: %s.\n", fileName);
        return 1;
    }
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;


    unsigned int prev = 0; 
    unsigned int cur; 
    while((nread = getline(&line, &len, fd)) != -1) {
        cur = strtoul(line, NULL, 10);
        if (cur < prev) {
            printf("Output file is not sorted.\n");
            return -1;
        }
        prev = cur;
    } 

    free(line);
    fclose(fd);
    printf("Output file is sorted.\n");
    return 0;
}
