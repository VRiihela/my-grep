#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void readFile(FILE *file, char ***lines, size_t *linesCount)    {
    char *line = NULL;
    size_t len = 0;
    *lines = NULL;
    *linesCount = 0;
    char *result = NULL;
    char *searchTerm = "will";

    // loop for read lines from input file
    while (getline(&line, &len, file) != -1) {
        result = strstr(line, searchTerm);
        if (result != NULL) {
            size_t lineLen = strlen(line);
            // ensure the line ends with line change '\n'
            if(lineLen == 0 || line[lineLen - 1] != '\n')   {
                line = realloc(line, lineLen + 2); // realloc line if newline is missing
                if(line == NULL)    {
                    fprintf(stderr, "realloc failed\n");
                    exit(1);
                }
                line[lineLen] = '\n';
                line[lineLen + 1] = '\0';
                lineLen++;
            }
            // enlarge array
            char **tmp = realloc(*lines,(*linesCount +1) * sizeof(char *));
            if(tmp == NULL) {
                fprintf(stderr, "realloc failed\n");
                exit(1);
            }
            *lines = tmp;

            (*lines)[*linesCount] = malloc(lineLen + 1); // memory allocation for new line
            if((*lines)[*linesCount] == NULL)    {
                fprintf(stderr, "malloc failed\n");
                exit(1);
            }
            strcpy((*lines)[*linesCount], line); // copy line to array
            (*linesCount)++; // count lines
            fprintf(stdout, "%s", line);
        }
    }

    free(line);
    return;
}

int main(int argc, char* argv[]) {
    FILE *fp;
    char **lines = NULL;
    size_t linesCount = 0;

    if (argc == 1)    {
        fprintf(stderr, "my-grep: searchterm [file ...]\n");
        exit(1);
    };
    if (argc == 2) {
        readFile(stdin, &lines, &linesCount);
        exit(0);
    };

    for (int i = 2; i < argc; i++)    {
        
        // fprintf(stdout, "%s\n", argv[i]);
        fp = fopen(argv[i], "r");
        if (fp == NULL)   {
            fprintf(stderr, "my-grep: cannot open file\n");
            exit(1);
        }
        readFile(fp, &lines, &linesCount);
    }


return 0;
}