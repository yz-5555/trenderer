#define TRENDERER_IMPLEMENTATION
#include "../../trenderer.h"

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

    return 0;
}
