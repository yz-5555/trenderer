#define TR_IMPLEMENTATION
#include "trenderer.h"

#include <Windows.h>
#include <conio.h>

int main(void) {
    SetConsoleOutputCP(CP_UTF8);

    tr_open_alt();
    tr_draw_text(
        "안녕하세요",
        (TrStyle){.effects = TR_ITALIC | TR_BOLD, .fg = TR_RED, .bg = TR_WHITE},
        5, 10
    );
    _getch();
    tr_close_alt();

    return 0;
}
