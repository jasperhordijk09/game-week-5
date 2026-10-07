#include <stdlib.h>
#include <fcntl.h>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#endif
#include <unistd.h>
#include <stdio.h>

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
    
    // Your code here using getkey()

    cleanup();
    return 0;
}
