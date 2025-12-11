#define TR_IMPLEMENTATION
#include "trenderer.h"

#include <conio.h>
#define ESC 27

#include <stdio.h>

#define STR_LEN 7
#define R 0
#define G 1
#define B 2

#define MY_CHK(x)          \
    do {                   \
        if ((x) != TR_OK)  \
            alive = false; \
    } while (0)

void increase_color(uint8_t *rgb, int target) {
    if (rgb[target] == 255)
        rgb[target] = 0;
    else
        rgb[target] += 1;
}
void decrease_color(uint8_t *rgb, int target) {
    if (rgb[target] == 0)
        rgb[target] = 255;
    else
        rgb[target] -= 1;
}
void increase_target(int *target) {
    *target += 1;
    if (*target > 2)
        *target = 0;
}
void decrease_target(int *target) {
    *target -= 1;
    if (*target < 0)
        *target = 2;
}
TrResult draw_color(TrRenderContext *ctx, uint8_t *rgb, int idx, int target) {
    char ch = '\0';
    int pos = 0;
    switch (idx) {
    case R:
        ch = 'R';
        pos = 0;
        break;
    case G:
        ch = 'G';
        pos = STR_LEN;
        break;
    case B:
        ch = 'B';
        pos = STR_LEN * 2;
        break;
    }

    char str[STR_LEN];
    sprintf(str, "%c: %3d", ch, rgb[idx]);

    TrStyle style = {
        .fg = TR_DEFAULT_COLOR_16,
        .bg = TR_DEFAULT_COLOR_16,
        .effects = idx == target ? TR_UNDERLINE : TR_DEFAULT_EFFECT
    };

    return tr_ctx_draw_text(ctx, str, strlen(str), style, pos, 0);
}
void process_input(uint8_t *rgb, int *target, bool *alive) {
    int key = _kbhit() ? _getch() : 0;

    switch (key) {
    case 'w':
        increase_color(rgb, *target);
        break;
    case 'a':
        decrease_target(target);
        break;
    case 's':
        decrease_color(rgb, *target);
        break;
    case 'd':
        increase_target(target);
        break;
    case ESC:
        *alive = false;
        break;
    }
}
int main(void) {
    uint8_t rgb[3] = {0, 0, 0};
    int target = 0;
    bool alive = true;

    TrRenderContext ctx;
    tr_ctx_init(&ctx, 0, 0, 21, 5);

    tr_open_alt();
    tr_hide_cursor();
    while (alive) {
        process_input(rgb, &target, &alive);

        tr_ctx_clear(&ctx, TR_DEFAULT_COLOR_16);

        MY_CHK(draw_color(&ctx, rgb, R, target));
        MY_CHK(draw_color(&ctx, rgb, G, target));
        MY_CHK(draw_color(&ctx, rgb, B, target));

        MY_CHK(tr_ctx_draw_rect(&ctx, 0, 1, 21, 4, tr_rgb(rgb[R], rgb[G], rgb[B])));

        MY_CHK(tr_ctx_render(&ctx));
    }
    tr_close_alt();

    return 0;
}
