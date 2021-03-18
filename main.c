#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    NONE = 0,
    UP = 1,
    DOWN = 2,
    LEFT = 4,
    RIGHT = 8
}Direction;
typedef struct {
    int x, y;
}Vertex;

typedef struct {
    int numberOfVertices;
    Direction shiftDirection;
    Vertex* vertexList;
}Polygon;

int main() {
    char command[] = "add 123 1 23 43 23 43";//triangle
    char *token = strtok(command, " ");
    if (strcmp(token, "add"))
        printf("Illegal command %s\n", token);
    int x = 0, y = 0, count = 0;
    while (token = strtok(NULL, " ")) {
        count++;
        if (count % 2)//count is odd, x coordinate
            x = atoi(token);
        else {//count is even, y coordinate
            y = atoi(token);
            Vertex v = {x, y};

            //other actions that you may wish to do...
        }
    }
}

