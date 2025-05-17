#include "../trenderer.h"
#include <stdio.h>

int main(void) {
    tr_effect(TR_BOLD | TR_STRIKETHROUGH);
    tr_fg_color(TR_RED, true);
    tr_bg_color(TR_BLUE, false);
    printf("Hello,");
    tr_reset();

    tr_effect(TR_UNDERLINE);
    tr_fg_color(TR_CYAN, false);
    tr_bg_color(TR_MAGENTA, false);
    printf("World!");
    tr_reset();

    return 0;
}
