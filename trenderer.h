#ifndef TRENDERER_H
#define TRENDERER_H

#include <stdbool.h>
#include <stdint.h>

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
typedef enum TrColorsMode {
    TR_COLORS_16,
    TR_COLORS_256,
    TR_COLORS_TRUE,
} TrColorsMode;
void tr_fg_color(uint32_t fg_color, TrColorsMode fg_mode);
void tr_bg_color(uint32_t bg_color, TrColorsMode bg_mode);
void tr_fg_reset(void);
void tr_bg_reset(void);

// Colors - Helper functions
static inline uint32_t tr_gray_256(uint8_t scale) {
    return (scale > 23) ? 232 : (232 + scale);
}
static inline uint32_t tr_rgb_256(uint8_t r, uint8_t g, uint8_t b) {
    return (r < 6 && g < 6 && b < 6) ? (16 + 36 * r + 6 * g + b) : 16;
}
static inline uint32_t tr_rgb(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}
static inline uint8_t tr_rgb_r(uint32_t rgb) {
    return (rgb >> 16) & 0xFF;
}
static inline uint8_t tr_rgb_g(uint32_t rgb) {
    return (rgb >> 8) & 0xFF;
}
static inline uint8_t tr_rgb_b(uint32_t rgb) {
    return rgb & 0xFF;
}

// Colors - ANSI 16 colors
#define TR_BLACK_16 30
#define TR_RED_16 31
#define TR_GREEN_16 32
#define TR_YELLOW_16 33
#define TR_BLUE_16 34
#define TR_MAGENTA_16 35
#define TR_CYAN_16 36
#define TR_WHITE_16 37

#define TR_BRIGHT_BLACK_16 40
#define TR_BRIGHT_RED_16 41
#define TR_BRIGHT_GREEN_16 42
#define TR_BRIGHT_YELLOW_16 43
#define TR_BRIGHT_BLUE_16 44
#define TR_BRIGHT_MAGENTA_16 45
#define TR_BRIGHT_CYAN_16 46
#define TR_BRIGHT_WHITE_16 47

#define TR_DEFAULT_COLOR_16 39

// Colors - ANSI 256 colors
#define TR_BLACK_256 0
#define TR_RED_256 1
#define TR_GREEN_256 2
#define TR_YELLOW_256 3
#define TR_BLUE_256 4
#define TR_MAGENTA_256 5
#define TR_CYAN_256 6
#define TR_WHITE_256 7

#define TR_BRIGHT_BLACK_256 8
#define TR_BRIGHT_RED_256 9
#define TR_BRIGHT_GREEN_256 10
#define TR_BRIGHT_YELLOW_256 11
#define TR_BRIGHT_BLUE_256 12
#define TR_BRIGHT_MAGENTA_256 13
#define TR_BRIGHT_CYAN_256 14
#define TR_BRIGHT_WHITE_256 15

// Colors - True colors
#define TR_BLACK tr_rgb(0, 0, 0)
#define TR_RED tr_rgb(255, 0, 0)
#define TR_GREEN tr_rgb(0, 255, 0)
#define TR_YELLOW tr_rgb(255, 255, 0)
#define TR_BLUE tr_rgb(0, 0, 255)
#define TR_MAGENTA tr_rgb(255, 0, 255)
#define TR_CYAN tr_rgb(0, 255, 255)
#define TR_WHITE tr_rgb(255, 255, 255)

#define TR_GRAY tr_rgb(128, 128, 128)
#define TR_ORANGE tr_rgb(255, 165, 0)
#define TR_PINK tr_rgb(255, 105, 180)
#define TR_SKYBLUE tr_rgb(135, 206, 235)

// Styles
typedef struct TrStyle {
    TrEffect effects;
    uint32_t fg_color;
    TrColorsMode fg_mode;
    uint32_t bg_color;
    TrColorsMode bg_mode;
} TrStyle;
void tr_style(const TrStyle *style);

// Basic renderer
typedef struct TrPixel {
    char ch;
    TrStyle style;
} TrPixel;
void tr_draw_sprite(const TrPixel *sprite, int width, int height, int x, int y);
void tr_draw_text(const char *text, const TrStyle *style, int x, int y);

// Frame buffers
void tr_fb_clear(TrPixel *fb, int fb_width, int fb_height, uint32_t bg_color, TrColorsMode bg_mode);
void tr_fb_render(TrPixel *curr_fb, TrPixel *prev_fb, int fb_width, int fb_height);
void tr_fb_draw_sprite(TrPixel *fb, int fb_width, int fb_height, const TrPixel *sprite, int sprite_width, int sprite_height, int sprite_x, int sprite_y);
void tr_fb_draw_text(TrPixel *fb, int fb_width, int fb_height, const char *text, const TrStyle *text_style, int text_x, int text_y);

// Helper functions
void tr_log_effects(TrEffect effects);
void tr_log_color(uint32_t color, TrColorsMode colors_mode);

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
    fputs(visible ? "\x1b[?25h" : "\x1b[?25l", stdout);
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
void tr_fg_color(uint32_t fg_color, TrColorsMode fg_mode) {
    switch (fg_mode) {
    case TR_COLORS_16:
        printf("\x1b[%dm", fg_color);
        break;
    case TR_COLORS_256:
        printf("\x1b[38;5;%dm", fg_color);
        break;
    case TR_COLORS_TRUE:
        printf("\x1b[38;2;%d;%d;%dm", tr_rgb_r(fg_color), tr_rgb_g(fg_color), tr_rgb_b(fg_color));
        break;
    }
}
void tr_bg_color(uint32_t bg_color, TrColorsMode bg_mode) {
    switch (bg_mode) {
    case TR_COLORS_16:
        printf("\x1b[%dm", 10 + bg_color);
        break;
    case TR_COLORS_256:
        printf("\x1b[48;5;%dm", bg_color);
        break;
    case TR_COLORS_TRUE:
        printf("\x1b[48;2;%d;%d;%dm", tr_rgb_r(bg_color), tr_rgb_g(bg_color), tr_rgb_b(bg_color));
        break;
    }
}
void tr_fg_reset(void) {
    fputs("\x1b[39m", stdout);
}
void tr_bg_reset(void) {
    fputs("\x1b[49m", stdout);
}

// Styles
void tr_style(const TrStyle *style) {
    tr_effects(style->effects);
    tr_fg_color(style->fg_color, style->fg_mode);
    tr_bg_color(style->bg_color, style->bg_mode);
}

// Basic renderer
void tr_draw_sprite(const TrPixel *sprite, int width, int height, int x, int y) {
    TrStyle style = {
        .effects = TR_DEFAULT_EFFECT,
        .fg_color = TR_DEFAULT_COLOR_16,
        .fg_mode = TR_COLORS_16,
        .bg_color = TR_DEFAULT_COLOR_16,
        .bg_mode = TR_COLORS_16,
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

            if (style.fg_color != sprite[i].style.fg_color || style.fg_mode != sprite[i].style.fg_mode) {
                style.fg_color = sprite[i].style.fg_color;
                style.fg_mode = sprite[i].style.fg_mode;
                tr_fg_color(style.fg_color, style.fg_mode);
            }

            if (style.bg_color != sprite[i].style.bg_color || style.bg_mode != sprite[i].style.bg_mode) {
                style.bg_color = sprite[i].style.bg_color;
                style.bg_mode = sprite[i].style.bg_mode;
                tr_bg_color(style.bg_color, style.bg_mode);
            }

            putchar(sprite[i].ch);
        }
        style.bg_color = TR_DEFAULT_COLOR_16;
        style.bg_mode = TR_COLORS_16;
        tr_bg_reset();
    }
}
void tr_draw_text(const char *text, const TrStyle *style, int x, int y) {
    tr_move_cursor(x, y);
    tr_style(style);
    fputs(text, stdout);
}

// Frame buffers
void tr_fb_clear(TrPixel *fb, int fb_width, int fb_height, uint32_t bg_color, TrColorsMode bg_mode) {
}
void tr_fb_render(TrPixel *curr_fb, TrPixel *prev_fb, int fb_width, int fb_height) {
}
void tr_fb_draw_sprite(TrPixel *fb, int fb_width, int fb_height, const TrPixel *sprite, int sprite_width, int sprite_height, int sprite_x, int sprite_y) {
}
void tr_fb_draw_text(TrPixel *fb, int fb_width, int fb_height, const char *text, const TrStyle *text_style, int text_x, int text_y) {
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
void tr_log_color(uint32_t color, TrColorsMode colors_mode) {
}
#endif // TRENDERER_IMPLEMENTATION
