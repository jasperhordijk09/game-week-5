#include <stdlib.h>
#include <fcntl.h>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#endif
#include <unistd.h>
#include <stdio.h>
#include <time.h>
int pos = 30; //positie van de v (player)
int x = 25; //positie van het gat
int lines = 0;
void setup() {
#ifndef _WIN32
    int flags = fcntl(STDIN_FILENO, F_GETFL);
    flags |= O_NONBLOCK; // set non-blocking input
    fcntl(STDIN_FILENO, F_SETFL, flags);

    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON; // turn off canonical mode (do not wait for enter)
    t.c_lflag &= ~ECHO; // do not echo input
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
#endif
}

void cleanup() {
#ifndef _WIN32
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ECHO; // echo input
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
#endif
}

int getkey() {
    int c = 0;
#ifdef _WIN32
    if (kbhit()) c = getch();
#else
    c = getchar();
#endif
    return c;
}
int volgendegat(){
    return (rand() % 2);
}
void positie(){
    int key = getkey();
    if (key == 'a'){
        pos--;
    }
    if (key == 'd'){
        pos++;
    }
}
void gatpositie(){
    int random = volgendegat();
    if (((random == 0) && !(x == 1)) || x == 49) {
        x--;
    }else if (random == 1 || x == 1) {
        x++;
    }

}
int dood(){
    if ((pos < x) || (pos > x+9)){
        return 1;
    }else{
        return 0;
    }
}
int main() {
    setup();
    srand(time(NULL));
    while(1){
        if (dood()) break;
        positie();
        gatpositie();
        for (int i = 0; i < x; i++){
            printf("#");
        }
        for (int j = 0; j < 10; j++){
            if (j == pos - x){
                printf("v");
            } else printf(" ");
        }
        for (int k = 0; k < 50 - x; k++){
            printf("#");
        }
        printf("\n");
        usleep(200000);
        lines++;
    }
    cleanup();
    printf("you were at %i\n", pos);
    printf("and the gap was from %i\n", x);
    printf("died after %i lines\n", lines);
    return 0;
}