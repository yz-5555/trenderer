#define TRENDERER_IMPLEMENTATION
#include "trenderer.h"

#include <stdio.h>

int main(void) {
    tr_add_effects(TR_BOLD);
    tr_set_fg(TR_BLUE_16, TR_COLORS_16);
    tr_set_bg(TR_YELLOW_16, TR_COLORS_16);
    printf("Hello, ");
    tr_remove_effects(TR_BOLD);

    tr_add_effects(TR_ITALIC | TR_UNDERLINE);
    tr_set_fg(TR_CYAN_256, TR_COLORS_256);
    tr_set_bg(TR_MAGENTA_16, TR_COLORS_16);
    printf("World! ");
    tr_remove_effects(TR_UNDERLINE);

    tr_add_effects(TR_STRIKETHROUGH | TR_DIM | TR_ITALIC);
    tr_set_fg(TR_ORANGE, TR_COLORS_TRUE);
    tr_set_bg(TR_PINK, TR_COLORS_TRUE);
    printf("This is TRENDERER.");
    tr_reset_all();

    printf("\n");

    printf("ANSI 16 COLORS\n");
    for (int i = 0; i < 2; i += 1) {
        for (int j = 30; j < 38; j += 1) {
            tr_set_bg(j + i * 60, TR_COLORS_16);
            printf("%d ", j + i * 60);
        }
    }
    tr_reset_bg();

    printf("\n");

    printf("ANSI 256 COLORS\n");
    for (int y = 0; y < 8; y += 1) {
        for (int x = 0; x < 32; x += 1) {
            tr_set_bg(x + 32 * y, TR_COLORS_256);
            printf("%d ", x + 32 * y);
        }
        tr_reset_bg();
        printf("\n");
    }
    printf("haha!\n");
    TrPixelArray v;
    tr_pa_init(&v, 8, 8);
    for (int i = 0; i < v.width * v.height; i += 1) {
        printf("Pixel[%d]: %d | %d | %d | %d | %d | %d\n", i, (int)v.letter[i], (int)v.effects[i], v.fg_color[i], v.bg_color[i], (int)v.fg_mode[i], (int)v.bg_mode[i]);
    }

    return 0;
}
