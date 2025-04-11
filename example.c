#include "trenderer.h"

#define W 10
#define H 10

int main(void) {
    TrPixel sprite[W * H];

    FOREACH_PIXEL(TrPixel *pixel, sprite, W * H) {
        pixel->ch = '$';

        pixel->fg_color = TR_BLACK;
        pixel->fg_bright = true;

        pixel->bg_color = TR_GREEN;
        pixel->bg_bright = false;

        pixel->effect = TR_BOLD | TR_BLINK;
    }
    tr_clear();
    tr_sprite_draw(sprite, 15, 2, W, H);

    return 0;
}
