#ifndef TRENDERER_H
#define TRENDERER_H

#include <stdbool.h>
#include <stdio.h>

// Screen & Window
static inline void tr_clear(void) {
    puts("\x1b[2J\x1b[H");
}

// Cursor
static inline void tr_move_cursor(int x, int y) {
    printf("\x1b[%d;%dH", y + 1, x + 1);
}
static inline void tr_show_cursor(bool visible) {
    if (visible)
        puts("\x1b[?25h");
    else
        puts("\x1b[?25l");
}

// Effects
typedef enum TrEffect {
    TR_EFFECT_DEFAULT = 0,
    TR_BOLD = 1 << 0,
    TR_DIM = 1 << 1,
    TR_ITALIC = 1 << 2,
    TR_UNDERLINE = 1 << 3,
    TR_BLINK = 1 << 4,
    TR_INVERT = 1 << 5,
    TR_HIDDEN = 1 << 6,
    TR_STRIKETHROUGH = 1 << 7,
} TrEffect;
static inline void tr_effects(TrEffect e) {
    if (e & TR_BOLD)
        puts("\x1b[1m");

    if (e & TR_DIM)
        puts("\x1b[2m");

    if (e & TR_ITALIC)
        puts("\x1b[3m");

    if (e & TR_UNDERLINE)
        puts("\x1b[4m");

    if (e & TR_BLINK)
        puts("\x1b[5m");

    if (e & TR_INVERT)
        puts("\x1b[7m");

    if (e & TR_HIDDEN)
        puts("\x1b[8m");

    if (e & TR_STRIKETHROUGH)
        puts("\x1b[9m");
}
static inline void tr_remove_effects(TrEffect effect) {
    if (effect & TR_BOLD || effect & TR_DIM)
        puts("\x1b[22m");

    if (effect & TR_ITALIC)
        puts("\x1b[23m");

    if (effect & TR_UNDERLINE)
        puts("\x1b[24m");

    if (effect & TR_BLINK)
        puts("\x1b[25m");

    if (effect & TR_INVERT)
        puts("\x1b[27m");

    if (effect & TR_HIDDEN)
        puts("\x1b[28m");

    if (effect & TR_STRIKETHROUGH)
        puts("\x1b[29m");
}
static inline void tr_reset_effects(void) {
    puts("\x1b[22;23;24;25;27;28;29m");
}
static inline void tr_reset(void) {
    puts("\x1b[0m");
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
    TR_COLOR_DEFAULT = 9
} TrColor;
static inline void tr_fg_color(TrColor c, bool bright) {
    if (c == TR_COLOR_DEFAULT)
        bright = false;
    printf("\x1b[%dm", bright ? (90 + (int)c) : (30 + (int)c));
}
static inline void tr_bg_color(TrColor c, bool bright) {
    if (c == TR_COLOR_DEFAULT)
        bright = false;
    printf("\x1b[%dm", bright ? (100 + (int)c) : (40 + (int)c));
}

typedef struct TrStyle {
    TrEffect effects;

    TrColor fg_color;
    bool fg_bright;

    TrColor bg_color;
    bool bg_bright;
} TrStyle;

// State renderer
typedef struct TrState {
    TrStyle style;

    TrEffect effects_to_add;
    TrEffect effects_to_remove;

    bool fg_changed;
    bool bg_changed;
} TrState;
static inline void tr_state_init(TrState *state) {
    state->style = {
        .effects = TR_EFFECT_DEFAULT,
        .fg_color = TR_COLOR_DEFAULT,
        .fg_bright = false,
        .bg_color = TR_COLOR_DEFAULT,
        .bg_bright = false,
    };
    state->effects_to_add = TR_EFFECT_DEFAULT;
    state->effects_to_remove = TR_EFFECT_DEFAULT;
    state->fg_changed = false;
    state->bg_changed = false;
}
static inline void tr_state_add_effect(TrState *state, TrEffect effect) {
    state->effects_to_add = (TrEffect)(state->effects_to_add | effect);
}
static inline void tr_state_remove_effect(TrState *state, TrEffect effect) {
    state->effects_to_remove = (TrEffect)(state->effects_to_remove | effect);
}
static inline void tr_state_fg_color(TrState *state, TrColor color, bool bright) {
    if (state->style.fg_color != color) {
        state->style.fg_color = color;
        state->fg_changed = true;
    }
    if (state->style.fg_bright != bright) {
        state->style.fg_bright = bright;
        state->fg_changed = true;
    }
}
static inline void tr_state_bg_color(TrState *state, TrColor color, bool bright) {
    if (state->style.bg_color != color) {
        state->style.bg_color = color;
        state->bg_changed = true;
    }
    if (state->style.bg_bright != bright) {
        state->style.bg_bright = bright;
        state->bg_changed = true;
    }
}
static inline void tr_state_apply(TrState *state) {
    if (state->effects_to_add != TR_EFFECT_DEFAULT) {
        state->style.effects = (TrEffect)(state->style.effects | state->effects_to_add);
        tr_effects(state->effects_to_add);
    }
    if (state->effects_to_remove != TR_EFFECT_DEFAULT) {
        state->style.effects = (TrEffect)(state->style.effects & ~state->effects_to_remove);
        tr_remove_effects(state->effects_to_remove);
    }
    if (state->fg_changed)
        tr_fg_color(state->style.fg_color, state->style.fg_bright);
    if (state->bg_changed)
        tr_bg_color(state->style.bg_color, state->style.bg_bright);

    state->effects_to_add = TR_EFFECT_DEFAULT;
    state->effects_to_remove = TR_EFFECT_DEFAULT;
    state->fg_changed = false;
    state->bg_changed = false;
}

// Sprite renderer
typedef struct TrPixel {
    char ch;
    TrStyle style;
} TrPixel;
static inline void tr_draw_sprite(const TrPixel *sprite, int x, int y, int width, int height) {
    TrState state;
    tr_state_init(&state);

    for (int iy = 0; iy < height; iy += 1) {
        tr_move_cursor(x, y + iy);
        tr_state_apply(&state);

        for (int ix = 0; ix < width; ix += 1) {
            int i = ix + iy * width;

            if (state.style.effects != sprite[i].style.effects) {
                curr.effect = sprite[i].style.effect;
            }

            if (curr_fg_color != sprite[i].style.fg_color || curr_fg_bright != sprite[i].style.fg_bright) {
                curr_fg_color = sprite[i].style.fg_color;
                curr_fg_bright = sprite[i].style.fg_bright;
                changed = true;
            }

            if (curr_bg_color != sprite[i].style.bg_color || curr_bg_bright != sprite[i].style.bg_bright) {
                curr_bg_color = sprite[i].style.bg_color;
                curr_bg_bright = sprite[i].style.bg_bright;
                changed = true;
            }

            if (changed) {
                tr_reset();
                tr_effects(curr_effect);
                tr_fg_color(curr_fg_color, curr_fg_bright);
                tr_bg_color(curr_bg_color, curr_bg_bright);
            }
            putchar(sprite[i].ch);
        }
        tr_reset();
    }
}
#endif
