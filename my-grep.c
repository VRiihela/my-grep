#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void readFile(FILE *file, char *searchTerm)    {
    char *line = NULL;
    size_t len = 0;
    char *result = NULL;

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
            fprintf(stdout, "%s", line);
        }
    }
    free(line);
    return;
}

int main(int argc, char* argv[]) {
    FILE *fp;
    if (argc == 1)    {
        fprintf(stderr, "my-grep: searchterm [file ...]\n");
        exit(1);
    };

    if (argc == 2) {
        readFile(stdin, argv[1]);
        exit(0);
    };

    for (int i = 2; i < argc; i++)    {
        fp = fopen(argv[i], "r");
        if (fp == NULL)   {
            fprintf(stderr, "my-grep: cannot open file\n");
            exit(1);
        }
        readFile(fp, argv[1]);
        fclose(fp);
    }


return 0;
}