#ifndef TRENDERER_H
#define TRENDERER_H

#include <stdbool.h>

// Screen & Window control
void tr_clear(void);

// Cursor control
void tr_move_cursor(int x, int y);
void tr_show_cursor(bool visible);

// Effects
typedef enum TrEffect {
    TR_DEFAULT_EFFECT = 0,
    TR_BOLD = 1 << 0,
    TR_DIM = 1 << 1,
    TR_ITALIC = 1 << 2,
    TR_UNDERLINE = 1 << 3,
    TR_BLINK = 1 << 4,
    TR_INVERT = 1 << 5,
    TR_HIDDEN = 1 << 6,
    TR_STRIKETHROUGH = 1 << 7,
} TrEffect;
void tr_effects(TrEffect effects);
void tr_remove_effects(TrEffect effects);
void tr_reset_effects(void);
void tr_reset(void);

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
    TR_DEFAULT_COLOR = 9,
    TR_TRANSPARENT = 10
} TrColor;
void tr_fg_color(TrColor fg_color, bool bright);
void tr_bg_color(TrColor bg_color, bool bright);

// Style
typedef struct TrStyle {
    TrEffect effects;

    TrColor fg_color;
    bool fg_bright;

    TrColor bg_color;
    bool bg_bright;
} TrStyle;
void tr_style(const TrStyle *style);

// Sprite renderer
typedef struct TrPixel {
    char ch;
    TrStyle style;
} TrPixel;
void tr_draw_sprite(const TrPixel *sprite, int x, int y, int width, int height);

// Frame buffers
typedef struct TrFrameBuffers {
    int width, height;
    TrPixel *data;
} TrFrameBuffers;
void tr_init_buffers(TrFrameBuffers *buffers, int width, int height);
void tr_clear_buffers(TrFrameBuffers *buffers, TrColor bg_color, bool bg_bright);
void tr_draw_buffers(const TrFrameBuffers *curr_buffers, const TrFrameBuffers *prev_buffers);
void tr_free_buffers(TrFrameBuffers *buffers);

// Helper functions
void tr_log_effects(TrEffect effects);
void tr_log_color(TrColor color, bool bright);
#endif // TRENDERER_H

#ifdef TRENDERER_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>

// Screen & Window control
void tr_clear(void) {
    fputs("\x1b[2J\x1b[H", stdout);
}

// Cursor control
void tr_move_cursor(int x, int y) {
    printf("\x1b[%d;%dH", y + 1, x + 1);
}
void tr_show_cursor(bool visible) {
    if (visible)
        fputs("\x1b[?25h", stdout);
    else
        fputs("\x1b[?25l", stdout);
}

// Effects
void tr_effects(TrEffect effects) {
    if (effects & TR_BOLD)
        fputs("\x1b[1m", stdout);

    if (effects & TR_DIM)
        fputs("\x1b[2m", stdout);

    if (effects & TR_ITALIC)
        fputs("\x1b[3m", stdout);

    if (effects & TR_UNDERLINE)
        fputs("\x1b[4m", stdout);

    if (effects & TR_BLINK)
        fputs("\x1b[5m", stdout);

    if (effects & TR_INVERT)
        fputs("\x1b[7m", stdout);

    if (effects & TR_HIDDEN)
        fputs("\x1b[8m", stdout);

    if (effects & TR_STRIKETHROUGH)
        fputs("\x1b[9m", stdout);
}
void tr_remove_effects(TrEffect effects) {
    if (effects & TR_BOLD || effects & TR_DIM)
        fputs("\x1b[22m", stdout);

    if (effects & TR_ITALIC)
        fputs("\x1b[23m", stdout);

    if (effects & TR_UNDERLINE)
        fputs("\x1b[24m", stdout);

    if (effects & TR_BLINK)
        fputs("\x1b[25m", stdout);

    if (effects & TR_INVERT)
        fputs("\x1b[27m", stdout);

    if (effects & TR_HIDDEN)
        fputs("\x1b[28m", stdout);

    if (effects & TR_STRIKETHROUGH)
        fputs("\x1b[29m", stdout);
}
void tr_reset_effects(void) {
    fputs("\x1b[22;23;24;25;27;28;29m", stdout);
}
void tr_reset(void) {
    fputs("\x1b[0m", stdout);
}

// Colors
void tr_fg_color(TrColor fg_color, bool bright) {
    if (fg_color == TR_TRANSPARENT)
        return;
    if (fg_color == TR_DEFAULT_COLOR)
        bright = false;
    printf("\x1b[%dm", bright ? (90 + (int)fg_color) : (30 + (int)fg_color));
}
void tr_bg_color(TrColor bg_color, bool bright) {
    if (bg_color == TR_TRANSPARENT)
        return;
    if (bg_color == TR_DEFAULT_COLOR)
        bright = false;
    printf("\x1b[%dm", bright ? (100 + (int)bg_color) : (40 + (int)bg_color));
}

// Style
void tr_style(const TrStyle *style) {
    tr_effects(style->effects);
    tr_fg_color(style->fg_color, style->fg_bright);
    tr_bg_color(style->bg_color, style->bg_bright);
}

// Sprite renderer
void tr_draw_sprite(const TrPixel *sprite, int int x, int y, int width, int height) {
    TrStyle style = {
        .effects = TR_DEFAULT_EFFECT,
        .fg_color = TR_DEFAULT_COLOR,
        .fg_bright = false,
        .bg_color = TR_DEFAULT_COLOR,
        .bg_bright = false,
    };

    for (int iy = 0; iy < height; iy += 1) {
        tr_move_cursor(x, y + iy);

        for (int ix = 0; ix < width; ix += 1) {
            int i = ix + iy * width;

            if (style.effects != sprite[i].style.effects) {
                tr_effects(sprite[i].style.effects & ~style.effects);
                tr_remove_effects(style.effects & ~sprite[i].style.effects);
                style.effects = sprite[i].style.effects;
            }

            if (style.fg_color != sprite[i].style.fg_color || style.fg_bright != sprite[i].style.fg_bright) {
                style.fg_color = sprite[i].style.fg_color;
                style.fg_bright = sprite[i].style.fg_bright;
                tr_fg_color(style.fg_color, style.fg_bright);
            }

            if (style.bg_color != sprite[i].style.bg_color || style.bg_bright != sprite[i].style.bg_bright) {
                style.bg_color = sprite[i].style.bg_color;
                style.bg_bright = sprite[i].style.bg_bright;
                tr_bg_color(style.bg_color, style.bg_bright);
            }

            putchar(sprite[i].ch);
        }
        style.bg_color = TR_DEFAULT_COLOR;
        style.bg_bright = false;
        tr_bg_color(style.bg_color, style.bg_bright);
    }
}

// Frame buffers
void tr_init_buffers(TrFrameBuffers *buffers, int width, int height) {
    buffers->width = width;
    buffers->height = height;
    buffers->data = (TrPixel *)malloc(width * height * sizeof(TrPixel));

	for (int i = 0; i < width * height; i += 1) {
		buffers->data[i].ch = NULL;
		buffers->data[i].effects = TR_DEFAULT_EFFECT;
		buffers->data[i].fg_color = TR_DEFAULT_COLOR;
		buffers->data[i].fg_bright = false;
		buffers->data[i].bg_color = TR_DEFAULT_COLOR;
		buffers->data[i].bg_bright = false;
	}
}
void tr_clear_buffers(TrFrameBuffers *buffers, TrColor bg_color, bool bg_bright) {
    for (int i = 0; i < buffers->width * buffers->height; i += 1) {
        buffers->data[i].bg_color = bg_color;
        buffers->data[i].bg_bright = bg_bright;
    }
}
void tr_draw_buffers(const TrFrameBuffers *curr_buffers, const TrFrameBuffers *prev_buffers) {
    TrStyle style = {
        .effects = TR_DEFAULT_EFFECT,
        .fg_color = TR_DEFAULT_COLOR,
        .fg_bright = false,
        .bg_color = TR_DEFAULT_COLOR,
        .bg_bright = false,
    };

    for (int iy = 0; iy < height; iy += 1) {
        for (int ix = 0; ix < width; ix += 1) {
            int i = ix + iy * width;

            if (style.effects != buffers->data[i].style.effects) {
                tr_effects(buffers->data[i].style.effects & ~style.effects);
                tr_remove_effects(style.effects & ~buffers->data[i].style.effects);
                style.effects = buffers->data[i].style.effects;
            }

            if (style.fg_color != buffers->data[i].style.fg_color || style.fg_bright != buffers->data[i].style.fg_bright) {
                style.fg_color = buffers->data[i].style.fg_color;
                style.fg_bright = buffers->data[i].style.fg_bright;
                tr_fg_color(style.fg_color, style.fg_bright);
            }

            if (style.bg_color != buffers->data[i].style.bg_color || style.bg_bright != buTR_BLUEffers->data[i].style.bg_bright) {
                style.bg_color = buffers->data[i].style.bg_color;
                style.bg_bright = buffers->data[i].style.bg_bright;
                tr_bg_color(style.bg_color, style.bg_bright);
            }

            putchar(sprite[i].ch);
        }
        style.bg_color = TR_DEFAULT_COLOR;
        style.bg_bright = false;
        tr_bg_color(style.bg_color, style.bg_bright);
    }
}
void tr_free_buffers(TrFrameBuffers *buffers) {
    free(buffers->data);
    buffers->data = NULL;
}
// Helper functions
void tr_log_effects(TrEffect effects) {
    if (effects == TR_DEFAULT_EFFECT) {
        fputs("DEFAULT_EFFECT", stdout);
        return;
    }
    if (effects & TR_BOLD)
        fputs("BOLD ", stdout);

    if (effects & TR_DIM)
        fputs("DIM ", stdout);

    if (effects & TR_ITALIC)
        fputs("ITALIC ", stdout);

    if (effects & TR_UNDERLINE)
        fputs("UNDERLINE ", stdout);

    if (effects & TR_BLINK)
        fputs("BLINK ", stdout);

    if (effects & TR_INVERT)
        fputs("INVERT ", stdout);

    if (effects & TR_HIDDEN)
        fputs("HIDDEN ", stdout);

    if (effects & TR_STRIKETHROUGH)
        fputs("STRIKETHROUGH ", stdout);
}
void tr_log_color(TrColor color, bool bright) {
    if (bright && color != TR_DEFAULT_COLOR)
        fputs("Bright ", stdout);

    if (color == TR_BLACK)
        fputs("BLACK", stdout);
    else if (color == TR_RED)
        fputs("RED", stdout);
    else if (color == TR_GREEN)
        fputs("GREEN", stdout);
    else if (color == TR_YELLOW)
        fputs("YELLOW", stdout);
    else if (color == TR_BLUE)
        fputs("BLUE", stdout);
    else if (color == TR_MAGENTA)
        fputs("MAGENTA", stdout);
    else if (color == TR_CYAN)
        fputs("CYAN", stdout);
    else if (color == TR_WHITE)
        fputs("WHITE", stdout);
    else if (color == TR_DEFAULT_COLOR)
        fputs("DEFAULT_COLOR", stdout);
}
#endif // TRENDERER_IMPLEMENTATION
