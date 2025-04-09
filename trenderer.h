#ifndef TRENDERER_H
#define TRENDERER_H

#include <stdbool.h>
#include <stdio.h>

// Screen & Window
static inline void tr_clear(void) {
    printf("\x1b[2J");
}

// Cursor
static inline void tr_move(int x, int y) {
    printf("\x1b[%d;%dH", y, x);
}
static inline void tr_cursor_visible(bool visible) {
    if (visible)
        printf("\x1b[?25h");
    else
        printf("\x1b[?25l");
}

// Effects
typedef enum TrEffect {
    TR_EFFECT_NONE = 0,
    TR_BOLD = 1 << 0,
    TR_DIM = 1 << 1,
    TR_UNDERLINE = 1 << 2,
    TR_BLINK = 1 << 3,
    TR_INVERT = 1 << 4,
    TR_HIDDEN = 1 << 5,
    TR_STRIKETHROUGH = 1 << 6,
} TrEffect;
static inline void tr_effect(TrEffect e) {
    if (e == TR_EFFECT_NONE) {
        printf("\x1b[0m");
        return;
    }
    if (e & TR_BOLD)
        printf("\x1b[1m");

    if (e & TR_DIM)
        printf("\x1b[2m");

    if (e & TR_UNDERLINE)
        printf("\x1b[4m");

    if (e & TR_BLINK)
        printf("\x1b[5m");

    if (e & TR_INVERT)
        printf("\x1b[7m");

    if (e & TR_HIDDEN)
        printf("\x1b[8m");

    if (e & TR_STRIKETHROUGH)
        printf("\x1b[9m");
}
static inline void tr_reset(void) {
    printf("\x1b[0m");
}

// Colors
typedef enum TrColor {
    TR_BLACK = 0,
    TR_RED = 1,
    TR_GREEN = 2,
    TR_YELLOW = 3,
    TR_BLUE = 4,
    TR_MAGENTA = 5,
    TR_CYAN = 6,
    TR_WHITE = 7,
} TrColor;
static inline void tr_fg_color(TrColor c, bool bright) {
    printf("\x1b[%dm", bright ? (90 + (int)c) : (30 + (int)c));
}
static inline void tr_bg_color(TrColor c, bool bright) {
    printf("\x1b[%dm", bright ? (100 + (int)c) : (40 + (int)c));
}

// Abstraction
typedef struct TrChar {
    char ch;
    TrEffect effect;
    TrColor fg_color;
    bool fg_bright;
    TrColor bg_color;
    bool bg_bright;
} TrChar;
static inline void tr_char_draw(TrChar c) {
    tr_effect(c.effect);
    tr_fg_color(c.fg_color, c.fg_bright);
    tr_bg_color(c.bg_color, c.bg_bright);
}
static inline void tr_sprite_draw(TrChar *sprite, int width, int height) {
    TrEffect curr_effect = TR_EFFECT_NONE;

    TrColor curr_fg_color = TR_WHITE;
    bool curr_fg_bright = false;

    TrColor curr_bg_color = TR_BLACK;
    bool curr_bg_bright = false;

    for (int y = 0; y < height; y += 1) {
        for (int x = 0; x < width; x += 1) {
            if (curr_effect != sprite[x * y].effect) {
                curr_effect = sprite[x * y].effect;

                tr_effect(curr_effect);
            }

            if (curr_fg_color != sprite[x * y].fg_color || curr_fg_bright != sprite[x * y].fg_bright) {
                curr_fg_color = sprite[x * y].fg_color;
                curr_fg_bright = sprite[x * y].fg_bright;

                tr_fg_color(curr_fg_color, curr_fg_bright);
            }

            if (curr_bg_color != sprite[x * y].bg_color || curr_bg_bright != sprite[x * y].bg_bright) {
                curr_bg_color = sprite[x * y].bg_color;
                curr_bg_bright = sprite[x * y].bg_bright;

                tr_bg_color(curr_bg_color, curr_bg_bright);
            }

            printf("%c", sprite[x * y].ch);
        }
        tr_reset();
        printf("\n");
    }
}
#endif
