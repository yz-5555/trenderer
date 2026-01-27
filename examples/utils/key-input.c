#include "key-input.h"

#if defined(_WIN32) || defined(_WIN64)

#include <conio.h>

int get_key(void) {
    if (_kbhit())
        return _getch();

    return 0;
}

#else

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

struct termios tio;

void begin(void) {

    tcgetattr(STDIN_FILENO, &tio);
    struct termios new_tio = tio;
    new_tio.c_cflag &= (~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}
void end(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &tio);
}
int get_key(void) {
    begin();

    int ch = getchar();

    end();

    return ch;
}
#endif
