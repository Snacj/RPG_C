#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tiles.h"

int MAP[MAP_ROWS][MAP_COLS];

int readMap(const char* path) {
      FILE *file = fopen(path, "r");
    if (!file) {
        perror("File open failed");
        return -1;
    }

    char line[LINE_LENGTH];
    int row = 0;

    while (fgets(line, sizeof(line), file) && row < MAP_ROWS) {
        int col = 0;
        char *token = strtok(line, ",\n");
        while (token && col < MAP_COLS) {
            MAP[row][col] = atoi(token);
            token = strtok(NULL, ",\n");
            col++;
        }
        row++;
    }

    fclose(file);
    return 0;
}
