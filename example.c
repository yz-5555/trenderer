#define TRENDERER_IMPLEMENTATION
#include "trenderer.h"
#include <stdio.h>

int main(void) {
    int width = 15;
    int height = 5;

    tr_style_begin(TR_TEXTBRIGHT, TR_RED, TR_DEFAULT);
    printf("Hello!");
    tr_style_end();
    printf("\x1b[5;3;1;4;9mHello, World!\x1b[0m");
    return 0;
}
