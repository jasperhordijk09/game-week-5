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

int main() {
    setup();
    
    // while(1){
    //     printf("getkey()) %d\n" , getkey());
    //     usleep(10000);
    // }
    // Your code here using getkey()


    int x = 25;
    srand(time(NULL));
    for (int i = 1; i < x; i++){
        
        printf("#");
    }
    for (int j = 0; j == 9; j++){
        print(" ");
        //if ()

    }

    printf("\n");

    cleanup();
    return 0;
}