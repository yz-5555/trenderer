#define TR_MAX_CELL_ARRAY_LENGTH 9
#define TR_MAX_FRAMEBUFFER_LENGTH 200

#define TR_IMPLEMENTATION
#include "trenderer.h"

#include <conio.h>
#define ESC 27

#define MY_CHK(x)          \
    do {                   \
        if ((x) != TR_OK)  \
            alive = false; \
    } while (0)

void fill_box(TrCellArray *box) {
    for (int i = 0; i < box->width * box->height; i += 1) {
        box->letter[i] = 'o';
        box->effects[i] = TR_BOLD | TR_ITALIC | TR_UNDERLINE | TR_STRIKETHROUGH;
        box->fg[i] = (TrColor){TR_BLACK_16, TR_COLOR_16};
        box->bg[i] = (TrColor){TR_TRANSPARENT, TR_COLOR_TRUE};
    }
}
void process_input(int *pos_x, int *pos_y, bool *alive) {
    int key = _kbhit() ? _getch() : 0;

    switch (key) {
    case 'w':
        *pos_y -= 1;
        break;
    case 'a':
        *pos_x -= 1;
        break;
    case 's':
        *pos_y += 1;
        break;
    case 'd':
        *pos_x += 1;
        break;
    case ESC:
        *alive = false;
        break;
    }
}

int main(void) {
    int pos_x = 0;
    int pos_y = 0;
    bool alive = true;

    TrCellArray box;
    tr_carr_init(&box, 3, 3);
    fill_box(&box);

    TrRenderContext ctx;
    tr_ctx_init(&ctx, 0, 0, 20, 10);

    tr_open_alt();
    tr_hide_cursor();
    while (alive) {
        process_input(&pos_x, &pos_y, &alive);

        tr_ctx_clear(&ctx, TR_DEFAULT_COLOR_16, TR_COLOR_16);

        MY_CHK(tr_ctx_draw_rect(&ctx, 0, 0, 10, 5, TR_RED_16, TR_COLOR_16));
        MY_CHK(tr_ctx_draw_rect(&ctx, 10, 0, 10, 5, TR_ORANGE, TR_COLOR_TRUE));
        MY_CHK(tr_ctx_draw_rect(&ctx, 0, 5, 10, 5, TR_BRIGHT_CYAN_256, TR_COLOR_256));
        MY_CHK(tr_ctx_draw_rect(&ctx, 10, 5, 10, 5, TR_WHITE_16, TR_COLOR_16));

        MY_CHK(tr_ctx_draw_sprite(&ctx, tr_atos(&box), pos_x, pos_y));

        MY_CHK(tr_ctx_render(&ctx));
    }
    tr_close_alt();

    return 0;
}
