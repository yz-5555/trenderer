#define TRENDERER_IMPLEMENTATION
#include "trenderer.h"

#include <conio.h>
#include <stdio.h>

#define STR_LEN 7
#define R 0
#define G 1
#define B 2

void increase_color(uint8_t *rgb, int target) {
    rgb[target] += 1;
    if (rgb[target] > 255)
        rgb[target] = 0;
}
void decrease_color(uint8_t *rgb, int target) {
    rgb[target] -= 1;
    if (rgb[target] == 0)
        rgb[target] = 255;
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
void draw_color(TrRenderContext *ctx, uint8_t *rgb, int idx, int target) {
    char ch = '\0';
    int pos = 0;
    switch (idx) {
    case R:
        ch = 'R';
        pos = 0;
        break;
    case G:
        ch = 'G';
        pos = 7;
        break;
    case B:
        ch = 'B';
        pos = 14;
        break;
    }

    char str[STR_LEN];
    sprintf(str, "%c: %d", ch, rgb[idx]);

    TrStyle style = {
        .fg = tr_default_color(),
        .bg = tr_default_color()};

    if (idx == target)
        style.effects = TR_UNDERLINE;
    else
        style.effects = TR_DEFAULT_EFFECT;

    tr_ctx_draw_text(ctx, str, STR_LEN, style, pos, 0);
}
int main(void) {
    bool alive = true;
    uint8_t rgb[3] = {0, 0, 0};
    int target = 0;

    TrRenderContext ctx;
    tr_ctx_init(&ctx, 21, 5);

    tr_clear();
    tr_cursor_visible(false);
    while (alive) {
        int key = 0;
        if (_kbhit())
            key = _getch();

        switch (key) {
        case 'w':
            increase_color(rgb, target);
            break;
        case 'a':
            decrease_target(&target);
            break;
        case 's':
            decrease_color(rgb, target);
            break;
        case 'd':
            increase_target(&target);
            break;
        case 27: // esc
            alive = false;
            break;
        }

        tr_ctx_clear(&ctx, TR_DEFAULT_COLOR_16, TR_COLOR_16);

        draw_color(&ctx, rgb, R, target);
        draw_color(&ctx, rgb, G, target);
        draw_color(&ctx, rgb, B, target);

        tr_ctx_render(&ctx);
    }

    return 0;
}
