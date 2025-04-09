#include "trenderer.h"
#include <stdio.h>

#define W 10
#define H 10

int main(void) {
    TrChar sprite[W * H];
    for (int y = 0; y < H; y += 1) {
        for (int x = 0; x < W; x += 1) {
            sprite[x * y].bg_color = TR_GREEN;
            sprite[x * y].bg_bright = false;

            sprite[x * y].fg_color = TR_BLACK;
            sprite[x * y].fg_bright = true;

            sprite[x * y].effect = TR_BOLD | TR_UNDERLINE;

            sprite[x * y].ch = '$';
        }
    }

    tr_sprite_draw(sprite, W, H);
    return 0;
}
