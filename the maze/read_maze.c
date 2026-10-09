#include <stdlib.h>
#include <stdio.h>
#define NORTH 1
#define EAST 2
#define SOUTH 4
#define WEST 8
#define FILENAME "maze_11x11.bin"

int width;
int height;
unsigned char *maze;

void printMaze() {
    printf("Maze %d x %d\n", width, height);
    for (int i = 0; i < width; i++) {
        printf("+---");
    }
    puts("+");
    for (int j = height - 1; j >= 0; j--) {
        putchar('|');
        for (int i = 0; i < width; i++) {
            printf("   ");
            if (maze[i + j * width] & EAST) putchar(' ');
            else putchar('|');
        }
        printf("\n+");
        for (int i = 0; i < width; i++) {
            if (maze[i + j * width] & SOUTH) printf("   ");
            else printf("---");
            putchar('+');
        }
        putchar('\n');
    }
}

int readMaze() {
    FILE *f = fopen(FILENAME, "r");
    if (f == NULL) {
        printf("Cannot open %s\n", FILENAME);
        return 1;
    }
    width = getc(f);
    height = getc(f);
    maze = malloc(width * height);
    size_t n = fread(maze, 1, width * height, f);
    fclose(f);
    if (n != width * height) {
        puts("Read error");
        return 1;
    }
    return 0;
}

unsigned char checkCell(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        printf("Illegal coordinates: (%d, %d)\n", x, y);
        return 0;
    }
    if (x == width - 1 && y == height -1) {
        puts("Finish reached");
        return 255;
    }
    return maze[x + width * y];
}

int main() {
    if (readMaze()) return 1;
    printMaze();

    // Your code here, using checkCell(x, y)

    return 0;
}