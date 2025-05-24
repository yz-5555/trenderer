#define TRENDERER_IMPLEMENTATION
#include "../../trenderer.h"

#include <stdio.h>

int main(void) {
    tr_effects(TR_BOLD);
    tr_fg_color(TR_RED, true);
    tr_bg_color(TR_BLUE, false);
    printf("Hello,");
    tr_reset();

    tr_effects(TR_ITALIC | TR_UNDERLINE);
    tr_fg_color(TR_CYAN, false);
    tr_bg_color(TR_MAGENTA, false);
    printf("World!");
    tr_reset();

    printf("\n");

    TrState state;
    tr_state_init(&state);

    tr_state_add_effects(&state, TR_BOLD | TR_ITALIC | TR_STRIKETHROUGH);
    tr_state_fg_color(&state, TR_RED, true);
    tr_state_bg_color(&state, TR_BLUE, false);
    tr_state_apply(&state);
    printf("Hello,");

    tr_state_add_effects(&state, TR_UNDERLINE);
    tr_state_remove_effects(&state, TR_BOLD | TR_STRIKETHROUGH);
    tr_state_fg_color(&state, TR_CYAN, false);
    tr_state_bg_color(&state, TR_MAGENTA, false);
    tr_state_apply(&state);
    printf("World!");

    tr_reset();

    return 0;
}
