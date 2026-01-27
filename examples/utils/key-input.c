#include "key-input.h"

#if defined(_WIN32) || defined(_WIN64)

#include <conio.h>

void ki_init(void) {}
void ki_reset(void) {}
int ki_get(void) {
    return _kbhit() ? _getch() : 0;
}

#else

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

struct termios oldt;

void ki_init(void) {
    tcgetattr(STDIN_FILENO, &oldt);

    struct termios newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    newt.c_cc[VMIN] = 0;
    newt.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}
void ki_reset(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
int ki_get(void) {
    unsigned char ch;
    // read() returns the number of bytes read
    if (read(STDIN_FILENO, &ch, 1) == 1) {
        return (int)ch;
    }
    return 0;
}
#endif
