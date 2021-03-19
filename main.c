#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBER_OF_VERTICES 100
#define MAX_NUMBER_OF_POLYGONS 1000

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

Polygon list[MAX_NUMBER_OF_POLYGONS];

void add_n_gon(){
//    add x1y1x2y2 . . . xnyn: adds an n-gon with vertices located at coordinates (x1, y1),
//    (x2, y2), . . . , (xn, yn) to the list of all polygons. The newly added polygon must have
//    its shiftDirection set to NONE.
    char token[MAX_NUMBER_OF_POLYGONS];
    Vertex* vList = (Vertex*)malloc(sizeof(Vertex) * MAX_NUMBER_OF_VERTICES);
    Polygon* poly = (Polygon*)malloc(sizeof(Polygon));
    int x, y, z, w, k = 0;
    int count = 0;
    char* temp;

    while (token[++z]) {
        if (token[z] == ' ')
            continue;
        w = z;
        while (token[++z])
            if (token[z] == ' ')
                break;
        temp = malloc(z - w + 1);
        while (k < z - w){
            temp[k] = token[w + k];
            k++;
        }
        temp[k] = '\0';
        count++;
        if(count%2)
            x = atoi(temp);
        else {
            y = atoi(temp);
            Vertex vertex_temp;
            vertex_temp.x = x;
            vertex_temp.y = y;
            Vertex v = vertex_temp;
            if (vList) vList[count/2-1] = v;
        }
        if (!token[z]) break;
    }

    if(count % 2 )
        printf("Error: there are odd number of coordinates passed to add command");
    else if(count < 3) //number of vertices is less than 3
        printf("Error: a polygon needs at least three vertices");
    else if(list >= MAX_NUMBER_OF_POLYGONS)
        printf("ERROR: too many polygons have been added to the list");
    else{
        poly->numberOfVertices = count / 2;
        poly->shiftDirection = NONE;
        poly->vertexList = vList;
    }

}
summary(){
//    summary: prints the program’s list of polygons. For each polygon, print
//    the number of vertices and the x-y coordinates of the polygon’s centroid. To avoid
//    the complications of calculating the centroid, you can assume that the x-coordinate
//    (y-coordinate) of a polygon is equal to the average of x-coordinates (y-coordinates) of
//    the polgyon’s vertices.
    int i, j;
    for (i = 0; i < MAX_NUMBER_OF_POLYGONS; i++) {
        int av_x,av_y = 0;
        int vs = list[i].numberOfVertices;

        printf("total polygons: %d: \n", i + 1);
        printf("total vertices: %d\n", vs);
        for (j = 0; j < list[i].numberOfVertices; j++)
            printf("vertex at: %d: (%d, %d)\n", j + 1, (list[i].vertexList[j].x), (list[i].vertexList[j].y));

        for (j = 0; j < list[i].numberOfVertices; j++) {
            av_x += list[i].vertexList[j].x;
            av_y += list[i].vertexList[j].y;
        }
        printf("centroid as average of x and y coordinates: (%d, %d)\n", av_x / vs, av_y / vs);
    }
}

void turn_n_gon(){
//    turn k x: updates the shiftDirection of polygon stored at index k of the program’s list
//    of polygons.
    char token1[MAX_NUMBER_OF_POLYGONS],token2[MAX_NUMBER_OF_POLYGONS];
    int i = atoi(token1) - 1;;
    char* direction = token2;

    if (!strcmp(direction, "right")) {
        printf("direction changed to 'right'\n", i++);
        list[i].shiftDirection = RIGHT;
    }else if (!strcmp(direction, "left")) {
        printf("direction changed to 'left'\n", i++);
        list[i].shiftDirection = LEFT;
    }else if (!strcmp(direction, "up")) {
        printf("direction going 'up'\n", i++);
        list[i].shiftDirection = UP;
    }else if (!strcmp(direction, "down")) {
        printf("direction going 'down'\n", i++);
        list[i].shiftDirection = DOWN;
    }else if ((!strcmp(direction, "right-up"))) {
        printf("direction going 'up right'\n", i++);
        list[i].shiftDirection = UP | RIGHT;
    }else if ((!strcmp(direction, "left-up"))) {
        printf("direction going 'up left'\n", i++);
        list[i].shiftDirection = LEFT | UP;
    }else if ((!strcmp(direction, "right-down"))) {
        printf("direction going 'right down'\n", i++);
        list[i].shiftDirection = RIGHT | DOWN;
    }else if ((!strcmp(direction, "left-down"))) {
        printf("direction going 'left down'\n", i++);
        list[i].shiftDirection = LEFT | DOWN;
    }else printf("no action done");
}

void shift_n_gon(){
//    shift k s: updates the x-y coordinates of vertices of polygon stored at index k of the
//    program’s list of polygons.
    char token1[MAX_NUMBER_OF_POLYGONS];
    char token2[MAX_NUMBER_OF_POLYGONS];

    int x, changeDir;
    int i = atoi(token1) - 1;
    int change = atoi(token2) - 1;
    changeDir = list[i].shiftDirection;

    switch (changeDir) {
        case UP:
            printf("polygon %d moved %d up\n", i + 1, change);
            for (x = 0; x < list[i].numberOfVertices; x++) {
                list[i].vertexList[x].y += change;
                list[i].shiftDirection = NONE;
            }break;
        case DOWN:
            printf("polygon %d moved %d  %d down\n", i + 1, change);
            for (x = 0; x < list[i].numberOfVertices; x++) {
                list[i].vertexList[x].y -= change;
                list[i].shiftDirection = NONE;
            }break;
        case LEFT:
            printf("polygon %d moved %d  %d left\n", i + 1, change);
            for (x = 0; x < list[i].numberOfVertices; x++) {
                list[i].vertexList[x].x -= change;
                list[i].shiftDirection = NONE;
            }break;
        case RIGHT:
            printf("polygon %d moved %d right\n", i + 1, change);
            for (x = 0; x < list[i].numberOfVertices; x++) {
                list[i].vertexList[x].x += change;
                list[i].shiftDirection = NONE;
            }break;
        case UP | RIGHT:
            printf("polygon %d moved %d right up\n", i + 1, change);
            for (x = 0; x < list[i].numberOfVertices; x++) {
                list[i].vertexList[x].x += change;
                list[i].vertexList[x].y += change;
                list[i].shiftDirection = NONE;
            }break;
        case UP | LEFT:
            printf("polygon %d moved %d left up\n", i + 1, change);
            for (x = 0; x < list[i].numberOfVertices; x++) {
                list[i].vertexList[x].x -= change;
                list[i].vertexList[x].y += change;
                list[i].shiftDirection = NONE;
            }break;
        case DOWN | RIGHT:
            printf("polygon %d moved %d right down\n", i + 1, change);
            for (x = 0; x < list[i].numberOfVertices; x++) {
                list[i].vertexList[x].x += change;
                list[i].vertexList[x].y -= change;
                list[i].shiftDirection = NONE;
            }break;
        case DOWN | LEFT:
            printf("polygon %d moved %d left down\n", i + 1, change);
            for (x = 0; x < list[i].numberOfVertices; x++) {
                list[i].vertexList[x].x -= change;
                list[i].vertexList[x].y -= change;
                list[i].shiftDirection = NONE;
            }break;
        default:
            printf("no movement\n");
            break;
    }
}
char getCommandWord(char command[], int maxLength) {
    char lastCharacter;
    int i;
    for (i = 0; (lastCharacter = getchar()) == ' '; i++);
    if (lastCharacter == '\n') {
        command[0] = '\0';
        return lastCharacter;
    }
    command[0] = lastCharacter;
    for (i = 1; i < maxLength - 1 && (command[i] = getchar()) != ' ' && command[i] != '\n'; i++);
    lastCharacter = command[i];
    command[i] = '\0';
    return lastCharacter;
}

int main() {
    char command[MAX_NUMBER_OF_VERTICES];
    char lastChar;

    while(1){ //infinite while loop
        printf("Enter one of the following commands: 'add' , 'summary' , 'turn k x',or 'shift k s' \n");
        lastChar = getCommandWord(command, MAX_NUMBER_OF_VERTICES);

        if (strcmp(command, "quit") == 0){ //if command === "quit"
            printf("Exiting...");
            break;
        }else if (!strcmp(command, "add")){
            if (lastChar == '\n')
                printf("too few arguments for 'add' command\n");
            else add_n_gon();
        }else if (!strcmp(command, "summary")){
            if (lastChar != '\n')//cp\n
                printf("too many arguments for 'summary' command.\n");
            else summary();
        } else if (!strcmp(command, "turn")){
            if (lastChar == '\n'){ //show x\n
                printf("Too few arguments for turn command.\n");
                while (getCommandWord(command, MAX_NUMBER_OF_VERTICES) != '\n');//skip the invalid show command...
            } else turn_n_gon();
        }else if (!strcmp(command, "shift")){
            if (lastChar == '\n'){ //show x\n
                printf("Too few arguments for show command.\n");
                while (getCommandWord(command, MAX_NUMBER_OF_VERTICES) != '\n');//skip the invalid show command...
            } else shift_n_gon();
        }else {
            printf("\n invalid command! Your command must start either with quit, add, summary, turn, or shift.\n");
            while (lastChar != '\n')//skip the remainder of my invalid command...
                lastChar = getCommandWord(command, MAX_NUMBER_OF_VERTICES);
        }

    }

}
