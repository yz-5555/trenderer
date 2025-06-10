#define TRENDERER_IMPLEMENTATION
#include "../../trenderer.h"

#include <stdio.h>

int main(void) {
    tr_effects(TR_BOLD);
    tr_fg_color_16(TR_BLUE_16);
    tr_bg_color_16(TR_YELLOW_16);
    printf("Hello, ");
    tr_remove_effects(TR_BOLD);

    tr_effects(TR_ITALIC | TR_UNDERLINE);
    tr_fg_color_256(TR_CYAN_256);
    tr_bg_color_256(TR_MAGENTA_256);
    printf("World! ");
    tr_remove_effects(TR_UNDERLINE);

    tr_effects(TR_STRIKETHROUGH | TR_DIM | TR_ITALIC);
    tr_fg_color(TR_ORANGE);
    tr_bg_color(TR_PINK);
    printf("This is TRENDERER.");
    tr_reset();

    printf("\n");

    return 0;
}
