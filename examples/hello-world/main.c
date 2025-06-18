#define TRENDERER_IMPLEMENTATION
#include "trenderer.h"

#include <stdio.h>

int main(void) {
    tr_effects(TR_BOLD);
    tr_fg_color(TR_BLUE_16, TR_COLORS_16);
    tr_bg_color(TR_YELLOW_16, TR_COLORS_16);
    printf("Hello, ");
    tr_remove_effects(TR_BOLD);

    tr_effects(TR_ITALIC | TR_UNDERLINE);
    tr_fg_color(TR_CYAN_256, TR_COLORS_256);
    tr_bg_color(TR_MAGENTA_16, TR_COLORS_16);
    printf("World! ");
    tr_remove_effects(TR_UNDERLINE);

    tr_effects(TR_STRIKETHROUGH | TR_DIM | TR_ITALIC);
    tr_fg_color(TR_ORANGE, TR_COLORS_TRUE);
    tr_bg_color(TR_PINK, TR_COLORS_TRUE);
    printf("This is TRENDERER.");
    tr_reset();

    printf("\n");

    printf("ANSI 16 COLORS\n");
    for (int i = 0; i < 2; i += 1) {
        for (int j = 30; j < 38; j += 1) {
            tr_bg_color(j + i * 60, TR_COLORS_16);
            printf("%d ", j + i * 60);
        }
    }
    tr_bg_reset();

    printf("\n");

    printf("ANSI 256 COLORS\n");
    for (int y = 0; y < 8; y += 1) {
        for (int x = 0; x < 32; x += 1) {
            tr_bg_color(x + 32 * y, TR_COLORS_256);
            printf("%d ", x + 32 * y);
        }
        tr_bg_reset();
        printf("\n");
    }

    return 0;
}
