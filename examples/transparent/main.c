#define TR_PIXEL_ARRAY_LENGTH 9
#define TR_FRAMEBUFFER_LENGTH 200
#include "trenderer.h"

#include <conio.h>

void fill_box(TrPixelArray *box) {
    for (int i = 0; i < box->width * box->height; i += 1) {
        box->letter[i] = 'o';
        box->effects[i] = TR_BOLD | TR_ITALIC | TR_UNDERLINE | TR_STRIKETHROUGH | TR_BLINK;
        box->fg[i].code = TR_BLACK_16;
        box->fg[i].mode = TR_COLOR_16;
        box->bg[i].code = TR_TRANSPARENT;
        box->bg[i].mode = TR_COLOR_TRUE;
    }
}

int main(void) {
    TrPixelArray box;
    tr_parr_init(&box, 3, 3);
    fill_box(&box);

    bool alive = true;
    int pos_x = 0;
    int pos_y = 0;

    TrRenderContext ctx;
    tr_ctx_init(&ctx, 20, 10);

    tr_clear();
    tr_cursor_visible(false);
    while (alive) {
        char key = 0;
        if (_kbhit())
            key = _getch();

        switch (key) {
        case 'w':
            pos_y -= 1;
            break;
        case 'a':
            pos_x -= 1;
            break;
        case 's':
            pos_y += 1;
            break;
        case 'd':
            pos_x += 1;
            break;
        case 27:
            alive = false;
            break;
        }

        tr_ctx_clear(&ctx, TR_DEFAULT_COLOR_16, TR_COLOR_16);
        {
            tr_ctx_draw_rect(&ctx, 0, 0, 10, 5, TR_RED_16, TR_COLOR_16);
            tr_ctx_draw_rect(&ctx, 10, 0, 10, 5, TR_ORANGE, TR_COLOR_TRUE);
            tr_ctx_draw_rect(&ctx, 0, 5, 10, 5, TR_BRIGHT_CYAN_256, TR_COLOR_256);
            tr_ctx_draw_rect(&ctx, 10, 5, 10, 5, TR_WHITE_16, TR_COLOR_16);

            tr_ctx_draw_sprite(&ctx, tr_atos(&box), pos_x, pos_y);
        }
        tr_ctx_render(&ctx);
    }
}
